#ifndef _MAIN_H_
#define _MAIN_H_

typedef struct {
    char date[20];
    double price;
    double subjectiveFeature1;
    double subjectiveFeature2;
    double subjectiveFeature3;
    double subjectiveFeature4;
    // Add features as needed
    double constant1;
    double constant2;
    double constant3;
    double constant4;
} TimeSeries;

typedef struct {
    char date[20];
    double predictedPrice;
} Forecast;

void readData(const char *filename, TimeSeries **data, int *numEntries);

double vonNeumannEntropy(const double *data, int size);

void performFFT(const double *data, int size, double *result);
void extractFeatures(const TimeSeries *data, int numEntries, double *vonNeumannEntropyArray, double *fftResult);
void trainAndEvaluateSVM(const TimeSeries *data, int numEntries, struct svm_model **model);

Forecast* forecast(const TimeSeries *data, int numEntries, int windowSize, int numSteps, const struct svm_model *model);

#endif // _MAIN_H_