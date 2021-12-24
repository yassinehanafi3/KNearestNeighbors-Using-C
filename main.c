#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "knn.h"


int main() {
    int i, x, numRows = 767, k = 30;
	float predict;
    
    FILE *file;
    file = fopen("./dataset/diabetes.csv","r");
    
    ligne *dataset = malloc(numRows * sizeof (*dataset));
    retrieveData(file, dataset);

    ligne test_set;
    /*printf("--------------------------------------\n");
    printf("Donnez les valeurs pour tester svp : \n");
    printf("--------------------------------------\n\n");
    printf("Donnez la valeur du Pregnancies : ");scanf("%d",&test_set.att.Pregnancies);
    printf("Donnez la valeur du Glucose : ");scanf("%d",&test_set.att.Glucose);
    printf("Donnez la valeur du BloodPressure : ");scanf("%d",&test_set.att.BloodPressure);
    printf("Donnez la valeur du SkinThickness : ");scanf("%d",&test_set.att.SkinThickness);
    printf("Donnez la valeur du Insulin : ");scanf("%d",&test_set.att.Insulin);
    printf("Donnez la valeur du BMI : ");scanf("%f",&test_set.att.BMI);
    printf("Donnez la valeur du DiabetesPedigreeFunction : ");scanf("%f",&test_set.att.DiabetesPedigreeFunction);
    printf("Donnez la valeur du Age : ");scanf("%d",&test_set.att.Age);*/

    
    // test_set   "10, 115, 0, 0, 0, 35.3, 0.134, 29, outcome = 0"
    test_set.att.Pregnancies = 10;
    test_set.att.Glucose = 115;
    test_set.att.BloodPressure = 0;
    test_set.att.SkinThickness = 0;
    test_set.att.Insulin = 0;
    test_set.att.BMI = 35.3;
    test_set.att.DiabetesPedigreeFunction = 0.134;
    test_set.att.Age = 29;
    test_set.outcome = 0;
    
    predict = KNN(dataset,test_set, k, numRows);
	printf("Outcome est %f",predict);
    printf("Hellow World!");
    
    fclose(file);
    return 0;
}
