#ifndef _H_INSTANCE_READER_
#define _H_INSTANCE_READER_

#define NUM_FEATURES 30

// Structure to read the instance
typedef struct {
    int target;
    float features[NUM_FEATURES];
} Instance;

void readCSV(const char *filename, Instance **instances, int *numInstances);

#endif // _H_INSTANCE_READER_
