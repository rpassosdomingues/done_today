#ifndef _H_TIMESERIES_
#define _H_TIMESERIES_

typedef struct {
    char date[20];
    double price;
    double subjectiveFeature1;
    double subjectiveFeature2;
    // Add more subjective features as needed
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

#endif //_H_TIMESERIES_
