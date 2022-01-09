#ifndef _KNN
    
    #define _KNN
    
    typedef struct{
        int Pregnancies, Glucose, BloodPressure, SkinThickness, Insulin, Age;
        float BMI, DiabetesPedigreeFunction;
    }attribut;
    
    typedef struct{
        attribut att;
        int outcome;
    }ligne;

    typedef struct {
        float distance;
        int outcome;
        int line;
    }distanceAndOutcome;

    typedef struct{
        int Pregnancies, Glucose, BloodPressure, SkinThickness, Insulin, Age;
        float BMI, DiabetesPedigreeFunction;
    }Attributes_means;


    void retrieveData(FILE* file, ligne *dataset, int numRows);
    void GetDistance(ligne *dataset, distanceAndOutcome *distAndOutcome, ligne test_set, int numRows);
    void SortByDistance(distanceAndOutcome *distAndOutcome, int numRows);
    float KNN(ligne *dataset, ligne test_set, int k, int numRows);
    void Test_Algo_from_file (ligne* test_set, ligne* dataset, int k , int numRows);
    void test_Algo_one_value(ligne* dataset, int numRows, int k);
    
#endif
