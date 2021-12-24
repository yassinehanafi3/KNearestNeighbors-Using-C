#ifndef _KNN
    
    #define _KNN
    
    typedef struct{
        int Age, Pregnancies, Glucose, BloodPressure, SkinThickness, Insulin;
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


    void retrieveData(FILE* file, ligne *dataset);
    void GetDistance(ligne *dataset, distanceAndOutcome *distAndOutcome, ligne test_set);
    void SortByDistance(distanceAndOutcome *distAndOutcome);
    float KNN(ligne *dataset, ligne test_set, int k, int numRows);
    
#endif
