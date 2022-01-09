#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "knn.h"

void retrieveData(FILE* file, ligne *dataset, int numRows){
    int j = 0;
    char * line = NULL;
    char * read = NULL;
    size_t len = 0;

    if(file == NULL) {
        printf("Error!");   
        exit(1);             
    }
    
    while (((read = getline(&line, &len, file)) != -1) && j < numRows) {
        float table[8];
        int i = 0;
        char *token;
        
        token = strtok(line,",");
        while( token != NULL ) {
            table[i] = atof(token);
            i++;
            token = strtok(NULL, ",");
        }
        dataset[j].att.Pregnancies = (int)table[0] ;
        dataset[j].att.Glucose = (int)table[1];
        dataset[j].att.BloodPressure = (int)table[2];
        dataset[j].att.SkinThickness = (int)table[3];
        dataset[j].att.Insulin = (int)table[4];
        dataset[j].att.BMI = table[5];
        dataset[j].att.DiabetesPedigreeFunction = table[6];
        dataset[j].att.Age = (int) table[7];
        dataset[j].outcome = (int)table[8];
        
        //printf("%d %d %d %d %d %f %f %d %d \n",dataset[j].att.Pregnancies, dataset[j].att.Glucose, dataset[j].att.BloodPressure, dataset[j].att.SkinThickness, dataset[j].att.Insulin, dataset[j].att.BMI, dataset[j].att.DiabetesPedigreeFunction, dataset[j].att.Age, dataset[j].outcome);
        j++;
    }
    fclose(file);
}


void GetDistance(ligne *dataset, distanceAndOutcome *distAndOutcome, ligne test_set, int numRows){
    int i = 0;

    for (i = 0; i < numRows ; i++){
        
        distAndOutcome[i].distance = sqrt(
            pow(test_set.att.Age - dataset[i].att.Age,2)+
            pow(test_set.att.BloodPressure - dataset[i].att.BloodPressure,2) +
            pow(test_set.att.BMI-dataset[i].att.BMI,2) +
            pow(test_set.att.DiabetesPedigreeFunction-dataset[i].att.DiabetesPedigreeFunction,2) +
            pow(test_set.att.Glucose-dataset[i].att.Glucose,2) +
            pow(test_set.att.Insulin-dataset[i].att.Insulin,2) +
            pow(test_set.att.Pregnancies-dataset[i].att.Pregnancies,2) +
            pow(test_set.att.SkinThickness-dataset[i].att.SkinThickness,2)
        );
        distAndOutcome[i].outcome = (int) dataset[i].outcome;
        distAndOutcome[i].line = i + 1;
    }
}


void SortByDistance(distanceAndOutcome *distAndOutcome, int numRows){
    int i = 0, j = 0;
    distanceAndOutcome temp;

    for (i = 0; i < numRows; i++) {

        for (j = i + 1; j < (numRows); j++) {

            if (distAndOutcome[i].distance > distAndOutcome[j].distance){

                temp = distAndOutcome[i];
                distAndOutcome[i] = distAndOutcome[j];
                distAndOutcome[j] = temp;

            }  
        }
    }
} 


float KNN(ligne *dataset, ligne test_set, int k, int numRows){
    int x;
    float pourcentage;
    float allOutcome = 0;

    distanceAndOutcome *distAndOutcome = malloc(numRows * sizeof (*distAndOutcome));
    
    GetDistance(dataset, distAndOutcome, test_set, numRows);
    SortByDistance(distAndOutcome, numRows);

    /*printf(" --------------------------------------------------------\n");
    printf(" Les %d plus proche voisin avec la distance et l'outcome \n",k);
    printf(" --------------------------------------------------------\n");*/
    for (x = 0; x < k; x++){
        //printf(" Distance : %f, Outcome: %d, Ligne: %d \n",distAndOutcome[x].distance,distAndOutcome[x].outcome, distAndOutcome[x].line);
        allOutcome += distAndOutcome[x].outcome;
    }
    pourcentage = allOutcome/k;
    return pourcentage;
}


void Test_Algo_from_file (ligne* test_set, ligne* dataset, int k , int numRows){
    int predicted_value[12], i = 0;
    float var;
    int j = 0;
    for (i=0; i < 12; i++){
        var = KNN(dataset, test_set[i], k, numRows);
        predicted_value[i] = var>0.5?1:0;
        j++;
    }
    printf("\n---------------------------\n");
    printf("| predicted  ||   wanted  |\n");
    printf("---------------------------\n");
    int right_answer = 0;
    for (i=0; i < 12; i++){
        if (predicted_value[i] == test_set[i].outcome){
            right_answer+=1;
        }
        printf("| %d          ||         %d |\n",predicted_value[i],test_set[i].outcome);
    }
    printf("---------------------------\n");
    printf("\n---------------------------\n");
    printf("Model Accuray est %.2f%% \n",(float)right_answer/12 *100);
    printf("---------------------------\n");

}

void test_Algo_one_value(ligne* dataset, int numRows, int k){
    ligne test_set;
    float predict;

    printf(" --------------------------------------\n");
    printf(" Donnez les valeurs pour tester svp : \n");
    printf(" --------------------------------------\n\n");
    printf(" Donnez la valeur du Pregnancies : ");scanf("%d",&test_set.att.Pregnancies);
    printf(" Donnez la valeur du Glucose : ");scanf("%d",&test_set.att.Glucose);
    printf(" Donnez la valeur du BloodPressure : ");scanf("%d",&test_set.att.BloodPressure);
    printf(" Donnez la valeur du SkinThickness : ");scanf("%d",&test_set.att.SkinThickness);
    printf(" Donnez la valeur du Insulin : ");scanf("%d",&test_set.att.Insulin);
    printf(" Donnez la valeur du BMI : ");scanf("%f",&test_set.att.BMI);
    printf(" Donnez la valeur du DiabetesPedigreeFunction : ");scanf("%f",&test_set.att.DiabetesPedigreeFunction);
    printf(" Donnez la valeur du Age : ");scanf("%d",&test_set.att.Age);

    predict = KNN(dataset, test_set, k, numRows);
    printf("\n");
    printf("\n");
    printf(" -----------------------\n");
    printf(" Le test est : ");
    if (predict > 0.5){
        printf("Positive \n");
    }else {
        printf(" Negative \n");
    }
    printf(" -----------------------\n");
}