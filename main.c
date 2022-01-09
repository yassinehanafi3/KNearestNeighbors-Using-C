#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "knn.h"


int main() {

    int numRows = 756, k = 11, choixMenu;
    FILE *file, *file_test;

    file = fopen("./dataset/diabetes.csv","r");
    file_test = fopen("./dataset/test_set.csv","r");

    ligne *dataset = malloc(numRows * sizeof (*dataset));
    retrieveData(file, dataset, numRows);
    ligne* test_set = malloc(12 * sizeof (*test_set));
    retrieveData(file_test, test_set, 12);


    while(1){
        system("cls");
        printf("\n");
        printf("--------------------------------\n\n");
        printf("------------- Menu -------------\n\n");
        printf("--------------------------------\n\n");
        printf("1.Predire pour une valeur test\n");
        printf("2.Predire pour tout le fichier test_set et afficher l'accuracy\n");
        printf("3.Exit\n");
        printf("\nVotre choix?\n\n");
        scanf("%d", &choixMenu);

        switch(choixMenu) {
            case 1:test_Algo_one_value(dataset, numRows, k);system("pause");break;
            case 2:Test_Algo_from_file(test_set, dataset, k, numRows);system("pause");break;
            case 3:exit(0);break;
            default:printf("Donnez une valeur (1, 2, 3)!");break;
        }
    }

    fclose(file);
    fclose(file_test);
    return 0;
}
