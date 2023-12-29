#ifndef _H_TIMESERIES_
#define _H_TIMESERIES_

typedef struct {
    char date[20];
    double price;
} TimeSeries;

void readData(const char *filename, TimeSeries **data, int *numEntries);

double calculateVonNeumannEntropy(const double *data, int size);
void performFFT(const double *data, int size, double *result);
void extractFeatures(const TimeSeries *data, int numEntries, double *vonNeumannEntropy, double *fftResult);

void trainAndEvaluateSVM(const TimeSeries *data, int numEntries);

#endif // _H_TIMESERIES_
