#ifndef _H_INSTANCE_READER_
#define _H_INSTANCE_READER_

#define NUM_FEATURES 30

// Structure to read the instance
typedef struct {
    int target;
    float features[NUM_FEATURES];
} Instance;

void readCSV(const char *filename, Instance **instances, int *numInstances);

// Summarization
float calculateMean(float array[], int size);
float calculateMode(float array[], int size);
int compareFloat(const void* a, const void* b);
float calculateMedian(float array[], int size);
float calculateStdDev(float array[], int size, float mean);
float calculateVariance(float array[], int size, float mean);

void analyzeData(const Instance *instances, int numInstances);

#endif // _H_INSTANCE_READER_
