#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "knn.h"

void retrieveData(FILE* file, ligne *dataset){
    int numRows = 765 ;
    int j = 0;
    char * line = NULL;
    char * read = NULL;
    size_t len = 0;
    bool first = true;

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
            if (first == false){
                table[i] = atof(token);
                i++;
            }
            token = strtok(NULL, ",");
        }
        if (first == false){
            dataset[j].att.Pregnancies = (int)table[0] ;
            dataset[j].att.Glucose = (int)table[1];
            dataset[j].att.BloodPressure = (int)table[2];
            dataset[j].att.SkinThickness = (int)table[3];
            dataset[j].att.Insulin = (int)table[4];
            dataset[j].att.BMI = table[5];
            dataset[j].att.DiabetesPedigreeFunction = table[6];
            dataset[j].att.Age = table[7];
            dataset[j].outcome = (int)table[8];
            //printf("%d, %d, %d, %d, %d, %f, %f, %d, Outcome == %d \n",dataset[j].att.Pregnancies, dataset[j].att.Glucose, dataset[j].att.BloodPressure, dataset[j].att.SkinThickness, dataset[j].att.Insulin, dataset[j].att.BMI, dataset[j].att.DiabetesPedigreeFunction, dataset[j].att.Age, dataset[j].outcome);
            j++;
        }
        first = false;
    }

    Attributes_means means;
    means = CalculateMeans(dataset, numRows);
    printf("Means\n");
        //printf("%f, %f, %f, %f, %f, %f, %f, %f \n",means.Pregnancies, means.Glucose, means.BloodPressure, means.SkinThickness, means.Insulin, means.BMI, means.DiabetesPedigreeFunction, means.Age);
    dataset[j].att.Pregnancies = dataset[j].att.Pregnancies == 0? means.Pregnancies:dataset[j].att.Pregnancies;
    dataset[j].att.Glucose = dataset[j].att.Glucose== 0? means.Glucose:dataset[j].att.Glucose;
    dataset[j].att.BloodPressure = dataset[j].att.BloodPressure== 0? means.BloodPressure:dataset[j].att.BloodPressure;
    dataset[j].att.SkinThickness = dataset[j].att.SkinThickness== 0? means.SkinThickness:dataset[j].att.SkinThickness;
    dataset[j].att.Insulin = dataset[j].att.Insulin== 0? means.Insulin:dataset[j].att.Insulin;
    dataset[j].att.BMI =dataset[j].att.BMI== 0? means.BMI:dataset[j].att.BMI;
    dataset[j].att.DiabetesPedigreeFunction = dataset[j].att.DiabetesPedigreeFunction== 0? means.DiabetesPedigreeFunction:dataset[j].att.DiabetesPedigreeFunction;
    dataset[j].att.Age = dataset[j].att.Age? means.Age:dataset[j].att.Age;
    fclose(file);
}


void GetDistance(ligne *dataset, distanceAndOutcome *distAndOutcome, ligne test_set){
    int i = 0, numRows = 765;
    for (i = 0; i < numRows ; i++){
        distAndOutcome[i].distance = sqrt(
            pow(test_set.att.Age - dataset[i].att.Age,2) + 
            pow(test_set.att.BloodPressure - dataset[i].att.BloodPressure,2) +
            pow(test_set.att.BMI-dataset[i].att.BMI,2) +
            pow(test_set.att.DiabetesPedigreeFunction-dataset[i].att.DiabetesPedigreeFunction,2) +
            pow(test_set.att.Glucose-dataset[i].att.Glucose,2) +
            pow(test_set.att.Insulin-dataset[i].att.Insulin,2) +
            pow(test_set.att.Pregnancies-dataset[i].att.Pregnancies,2) +
            pow(test_set.att.SkinThickness-dataset[i].att.SkinThickness,2)
        );
        distAndOutcome[i].outcome = (int) dataset[i].outcome;
        distAndOutcome[i].line = i + 2;
    }
}


void SortByDistance(distanceAndOutcome *distAndOutcome){
    int numRows = 765;
    int i = 0, j;
    distanceAndOutcome temp;


    for (i = 0; i < numRows; i++)
    {
        for (j = i + 1; j < (numRows); j++)
        {
            if (distAndOutcome[i].distance > distAndOutcome[j].distance)
            {
                temp = distAndOutcome[i];
                distAndOutcome[i] = distAndOutcome[j];
                distAndOutcome[j] = temp;
            }
            
        }
    }
} 


float KNN(ligne *dataset, ligne test_set, int k, int numRows){
    int x,j;
    float pourcentage;
    distanceAndOutcome *distAndOutcome = malloc(numRows * sizeof (*distAndOutcome));
    
    GetDistance(dataset, distAndOutcome, test_set);
    SortByDistance(distAndOutcome);
    
    
    int allOutcome = 0;
    for (x = 0; x < k; x++){
        //printf("distance : %f, outcome: %d, line: %d \n",distAndOutcome[x].distance,distAndOutcome[x].outcome, distAndOutcome[x].line);
        if (distAndOutcome[x].outcome == 0 || distAndOutcome[x].outcome == 1){
            allOutcome += distAndOutcome[x].outcome;
        }
    }
    printf("%d \n",allOutcome);
    printf("K === %d : \n allOutcome == %d \n Pourcentage d'etre 1 est === %f \n",k, allOutcome, (float) allOutcome/k);
    return (float) allOutcome/k;
}


void NormalizeDataset(ligne *dataset, int numRows){
    int i,j = 0;
    int max = getMaxOfAge(dataset, numRows), min = getMinOfAge(dataset, numRows);
    for (i = 0; i < numRows ; i++){
        if (dataset[i].att.Age == max){
            dataset[i].att.Age = 1;
        }
        else if (dataset[i].att.Age == min){
            dataset[i].att.Age = 0;
        }
        else {
            dataset[i].att.Age = (dataset[i].att.Age - min)/max;
        }
        //printf("%f \n", dataset[j].att.Age);
        j++;
    }

}

int getMaxOfAge(ligne *dataset, int numRows){
    int max;
    int i;
    max = dataset[0].att.Age;
    for (i = 1; i < numRows ; i++){
        if (max < dataset[i].att.Age){
            max = dataset[i].att.Age;
        }
    }
    return max;
}

int getMinOfAge(ligne *dataset, int numRows){
    int min;
    int i;
    min = dataset[0].att.Age;
    for (i = 1; i < numRows ; i++){
        if (min > dataset[i].att.Age){
            min = dataset[i].att.Age;
        }
    }
    return min;
}


Attributes_means CalculateMeans(ligne *dataset, int numRows){
    int i;
    Attributes_means means;
    for (i = 0; i < numRows ; i++){ 
        means.Pregnancies += dataset[i].att.Pregnancies;
        means.Glucose += dataset[i].att.Glucose;
        means.BloodPressure += dataset[i].att.BloodPressure;
        means.SkinThickness += dataset[i].att.SkinThickness;
        means.Insulin += dataset[i].att.Insulin;
        means.BMI += dataset[i].att.BMI;
        means.DiabetesPedigreeFunction += dataset[i].att.DiabetesPedigreeFunction;
        means.Age += dataset[i].att.Age;
    }
    means.Pregnancies = means.Pregnancies / numRows;
    means.Glucose = means.Glucose / numRows;
    means.BloodPressure = means.BloodPressure / numRows;
    means.SkinThickness = means.SkinThickness / numRows;
    means.Insulin = means.Insulin / numRows;
    means.BMI = means.BMI / numRows;
    means.DiabetesPedigreeFunction = means.DiabetesPedigreeFunction / numRows;
    means.Age = means.Age / numRows;
    
    return means;
}