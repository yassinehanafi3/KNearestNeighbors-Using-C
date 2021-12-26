#ifndef _KNN
    
    #define _KNN
    
    typedef struct{
        int Pregnancies, Glucose, BloodPressure, SkinThickness, Insulin;
        float BMI, DiabetesPedigreeFunction, Age;
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
        float Pregnancies, Glucose, BloodPressure, SkinThickness, Insulin, BMI, DiabetesPedigreeFunction, Age;
    }Attributes_means;


    void retrieveData(FILE* file, ligne *dataset);
    Attributes_means CalculateMeans(ligne *dataset, int numRows);
    void NormalizeDataset(ligne *dataset, int numRows);
    void GetDistance(ligne *dataset, distanceAndOutcome *distAndOutcome, ligne test_set);
    void SortByDistance(distanceAndOutcome *distAndOutcome);
    float KNN(ligne *dataset, ligne test_set, int k, int numRows);
    int getMaxOfAge(ligne *dataset, int numRows);
    int getMinOfAge(ligne *dataset, int numRows);
    
#endif
