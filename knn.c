#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "knn.h"

void retrieveData(FILE* file, ligne *dataset){
    int numRows = 767 ;
    
    char * line = NULL;
    char * read = NULL;
    size_t len = 0;
    //size_t read;
    bool first = true;
    if(file == NULL) {
        printf("Error!");   
        exit(1);             
    }
    int j = 0;
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
            dataset[j].att.Pregnancies = table[0];
            dataset[j].att.Glucose = table[1];
            dataset[j].att.BloodPressure = table[2];
            dataset[j].att.SkinThickness = table[3];
            dataset[j].att.Insulin = table[4];
            dataset[j].att.BMI = table[5];
            dataset[j].att.DiabetesPedigreeFunction = table[6];
            dataset[j].att.Age = table[7];
            dataset[j].outcome = (int)table[8];
            j++;
        }
        first = false;
        
    }
    fclose(file);
}


void GetDistance(ligne *dataset, distanceAndOutcome *distAndOutcome, ligne test_set){
    int i = 0, numRows = 767;

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
    int numRows = 767;
    int i = 0, j;
    distanceAndOutcome temp;
    
    for (i = 0; i < numRows; i++)
    {
        for (j = 0; j < (numRows-i); j++)
        {
            if (distAndOutcome[j].distance > distAndOutcome[j + 1].distance)
            {
                temp.distance = distAndOutcome[j].distance;
                temp.outcome = distAndOutcome[j].outcome;
                temp.line = distAndOutcome[j].line;
                distAndOutcome[j].distance = distAndOutcome[j + 1].distance;
                distAndOutcome[j].outcome = distAndOutcome[j + 1].outcome;
                distAndOutcome[j].line = distAndOutcome[j + 1].line;
                distAndOutcome[j + 1].distance = temp.distance;
                distAndOutcome[j + 1].outcome = temp.outcome;
                distAndOutcome[j + 1].line = temp.line;
            } 
        }
    }
} 


float KNN(ligne *dataset, ligne test_set, int k, int numRows){
    int x;
    float pourcentage;

    distanceAndOutcome *distAndOutcome = malloc(numRows * sizeof (*distAndOutcome));
    GetDistance(dataset, distAndOutcome, test_set);

    distanceAndOutcome *sortedDistance = malloc(numRows * sizeof (*sortedDistance));
    SortByDistance(distAndOutcome);
    

    int allOutcome = 0;
    for (x = 0; x < k; x++){
        //printf("distance : %f, outcome: %d, line: %d \n",distAndOutcome[x].distance,distAndOutcome[x].outcome, distAndOutcome[x].line);
        if (distAndOutcome[x].outcome ==0 || distAndOutcome[x].outcome ==1){
            allOutcome += distAndOutcome[x].outcome;
        }
    }
    pourcentage = (float) allOutcome/30;
    printf("K === %d : \n allOutcome == %d \n Pourcentage d'etre 1 est === %f \n",k, allOutcome, pourcentage);
    printf("Hellow World!");
    return pourcentage;
}