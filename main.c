#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "knn.h"


int main() {
    int i, x, numRows = 765, k = 11;
	float predict;
    
    FILE *file;
    file = fopen("./dataset/diabetes.csv","r");
    
    ligne *dataset = malloc(numRows * sizeof (*dataset));
    retrieveData(file, dataset);
    NormalizeDataset(dataset, numRows);
    //printf("%f, %f, %f, %f, %f, %f, %f, %f \n",means.Pregnancies, means.Glucose, means.BloodPressure, means.SkinThickness, means.Insulin, means.BMI, means.DiabetesPedigreeFunction, means.Age);
    ligne test_set;
    printf("--------------------------------------\n");
    printf("Donnez les valeurs pour tester svp : \n");
    printf("--------------------------------------\n\n");
    printf("Donnez la valeur du Pregnancies : ");scanf("%d",&test_set.att.Pregnancies);
    printf("Donnez la valeur du Glucose : ");scanf("%d",&test_set.att.Glucose);
    printf("Donnez la valeur du BloodPressure : ");scanf("%d",&test_set.att.BloodPressure);
    printf("Donnez la valeur du SkinThickness : ");scanf("%d",&test_set.att.SkinThickness);
    printf("Donnez la valeur du Insulin : ");scanf("%d",&test_set.att.Insulin);
    printf("Donnez la valeur du BMI : ");scanf("%f",&test_set.att.BMI);
    printf("Donnez la valeur du DiabetesPedigreeFunction : ");scanf("%f",&test_set.att.DiabetesPedigreeFunction);
    printf("Donnez la valeur du Age : ");scanf("%f",&test_set.att.Age);

    
    // test_set 1   "10, 115, 0, 0, 0, 35.3, 0.134, 29, outcome = 0"
    // test_set 2   "7, 103, 66, 32, 0, 39.1, 0.344, 31, outcome = 1"
    // test_set 3   "7, 105, 0, 0, 0, 0, 0.305, 24, outcome = 0" 




    /*test_set.att.Pregnancies = 7;
    test_set.att.Glucose = 103;
    test_set.att.BloodPressure = 66;
    test_set.att.SkinThickness = 32;
    test_set.att.Insulin = 0;
    test_set.att.BMI = 39.1;
    test_set.att.DiabetesPedigreeFunction = 0.344;
    test_set.att.Age = 31;*/
    //test_set.outcome = 1;
    
    predict = KNN(dataset, test_set, k, numRows);
	printf("Outcome est %f",predict);

    printf("%f", getMaxOfAge(dataset, numRows));
    //printf("Hellow World!");
    
    fclose(file);
    return 0;
}
