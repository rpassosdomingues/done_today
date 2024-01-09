/**
 * ____________________________________________
 *     --- Exploratory Data Analysis ---
 * --------------------------------------------
 * Author: Rafael Passos Domingues
 * ____________________________________________
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "main.h"

#define MAX_LINE_LENGTH 1024

void readCSV(const char *filename, Instance **instances, int *numInstances) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("\n\tFile not found.\n");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];

    // Counts the number of instances in the file
    *numInstances = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        (*numInstances)++;
    }

    // Go back to the beginning of the file
    fseek(file, 0, SEEK_SET);

    // Allocates memory to store instances
    *instances = (Instance *)malloc(*numInstances * sizeof(Instance));
    if (*instances == NULL) {
        perror("\n\tMemory Allocation Error.\n");
        exit(EXIT_FAILURE);
    }

    // Read file instances
    for (int i = 0; i < *numInstances; i++) {
        fgets(line, sizeof(line), file);

        // Use scanf to extract values from the formatted line
        sscanf(line, "%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
               &(*instances)[i].target,
               &(*instances)[i].features[0], &(*instances)[i].features[1], &(*instances)[i].features[2], &(*instances)[i].features[3],
               &(*instances)[i].features[4], &(*instances)[i].features[5], &(*instances)[i].features[6], &(*instances)[i].features[7],
               &(*instances)[i].features[8], &(*instances)[i].features[9], &(*instances)[i].features[10], &(*instances)[i].features[11],
               &(*instances)[i].features[12], &(*instances)[i].features[13], &(*instances)[i].features[14], &(*instances)[i].features[15],
               &(*instances)[i].features[16], &(*instances)[i].features[17], &(*instances)[i].features[18], &(*instances)[i].features[19],
               &(*instances)[i].features[20], &(*instances)[i].features[21], &(*instances)[i].features[22], &(*instances)[i].features[23],
               &(*instances)[i].features[24], &(*instances)[i].features[25], &(*instances)[i].features[26], &(*instances)[i].features[27],
               &(*instances)[i].features[28], &(*instances)[i].features[29]);
    }

    fclose(file);
}

// Function to calculate the average of an array of floats
float calculateMean(float array[], int size) {
    float sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum / size;
}

// Function to calculate the standard deviation of an array of floats
float calculateStdDev(float array[], int size, float mean) {
    float sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += pow(array[i] - mean, 2);
    }
    return sqrt(sum / size);
}

// Function to calculate the variance of an array of floats
float calculateVariance(float array[], int size, float mean) {
    float sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += pow(array[i] - mean, 2);
    }
    return sum / size;
}

// Summary Statistics
void analyzeData(const Instance *instances, int numInstances) {
    int targetCount0 = 0;
    int targetCount1 = 0;

    // Arrays to store the values of all features
    float allFeatureMeans[30] = {0};
    float allFeatureStdDevs[30] = {0};
    float allFeatureVariances[30] = {0};

    // Initialize arrays for calculating the average
    for (int j = 0; j < 30; j++) {
        float featureValues[numInstances];
        for (int i = 0; i < numInstances; i++) {
            featureValues[i] = instances[i].features[j];
            allFeatureMeans[j] += featureValues[i];
        }
        allFeatureMeans[j] /= numInstances;
    }

    // Counting target's 0 and 1 and calculating summary statistics
    for (int i = 0; i < numInstances; i++) {
        if (instances[i].target == 0) {
            targetCount0++;
        } else if (instances[i].target == 1) {
            targetCount1++;
        }

        for (int j = 0; j < 30; j++) {
            float diff = instances[i].features[j] - allFeatureMeans[j];
            allFeatureStdDevs[j] += pow(diff, 2);
            allFeatureVariances[j] += pow(diff, 2);
        }
    }

    // Calculate final standard deviation and print statistical summary
    printf("\nDatabase Representativeness:\n\n");
    printf("Number of target 0: %d (Percentage: %.2f%%)\n", targetCount0, ((float)targetCount0 / numInstances) * 100);
    printf("Number of target 1: %d (Percentage: %.2f%%)\n", targetCount1, ((float)targetCount1 / numInstances) * 100);

    printf("\nStatistical Summary of All Features:\n\n");
    for (int j = 0; j < 30; j++) {
        allFeatureMeans[j] /= numInstances;

        allFeatureStdDevs[j] = sqrt(allFeatureStdDevs[j] / numInstances);
        allFeatureVariances[j] = allFeatureVariances[j] / numInstances;

        printf("Feature %d - Mean: %.4f, Variance: %.4f, Standard Deviation: %.4f\n", j + 1, allFeatureMeans[j], allFeatureVariances[j], allFeatureStdDevs[j]);
    }
}

int main() {
    
    const char *filename = "../data/input.csv";
    int numInstances;
    Instance *instances;

    readCSV(filename, &instances, &numInstances);

    analyzeData(instances, numInstances);

    free(instances);

    return 0;
}
