/**
 * ____________________________________________
 *     --- Exploratory Data Analysis ---
 * --------------------------------------------
 * Author: Rafael Passos Domingues
 * ____________________________________________
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

        // Tokenize the line based on commas
        char *token = strtok(line, ",");
        
        // Read target
        sscanf(token, "%d", &(*instances)[i].target);

        // Read features
        for (int j = 0; j < 30; j++) {
            token = strtok(NULL, ",");
            sscanf(token, "%f", &(*instances)[i].features[j]);
        }
    }

    fclose(file);
}

// Function to calculate the mean of an array of floats
float calculateMean(float array[], int size) {
    if (size == 0) {
        // Handle the case where size is zero (to avoid division by zero)
        return 0.0;
    }

    float sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum / size;
}

// Function to calculate the mode of an array of floats
float calculateMode(float array[], int size) {
    // Sort the array first
    qsort(array, size, sizeof(float), compareFloat);

    int maxCount = 0, currentCount = 1;
    float mode = array[0];

    for (int i = 1; i < size; i++) {
        if (array[i] == array[i - 1]) {
            currentCount++;
        } else {
            if (currentCount > maxCount) {
                maxCount = currentCount;
                mode = array[i - 1];
            }
            currentCount = 1;
        }
    }

    // Check the last element
    if (currentCount > maxCount) {
        mode = array[size - 1];
    }

    return mode;
}

// Function to compare floats for qsort
int compareFloat(const void* a, const void* b) {
    return (*(float*)a - *(float*)b);
}

// Function to calculate the median of an array of floats
float calculateMedian(float array[], int size) {
    // Sort the array first
    qsort(array, size, sizeof(float), compareFloat);

    if (size % 2 == 0) {
        return (array[size / 2 - 1] + array[size / 2]) / 2.0;
    } else {
        return array[size / 2];
    }
}

// Function to calculate the standard deviation of an array of floats
float calculateStdDev(float array[], int size, float mean) {
    if (size == 0) {
        // Handle the case where size is zero (to avoid division by zero)
        return 0.0;
    }

    float sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += pow(array[i] - mean, 2);
    }
    return sqrt(sum / size);
}

// Function to calculate the variance of an array of floats
float calculateVariance(float array[], int size, float mean) {
    if (size == 0) {
        // Handle the case where size is zero (to avoid division by zero)
        return 0.0;
    }

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
    float allFeatureVariances[30] = {0};
    float allFeatureStdDevs[30] = {0};

    // Use dynamic memory allocation for featureValues
    float **featureValues = (float **)malloc(30 * sizeof(float *));
    for (int j = 0; j < 30; j++) {
        featureValues[j] = (float *)malloc(numInstances * sizeof(float));

        // Initialize arrays for calculating the average
        for (int i = 0; i < numInstances; i++) {
            featureValues[j][i] = instances[i].features[j];
            allFeatureMeans[j] += featureValues[j][i];
        }
        allFeatureMeans[j] /= numInstances;

        // Calculate variance and standard deviation
        for (int i = 0; i < numInstances; i++) {
            float diff = featureValues[j][i] - allFeatureMeans[j];
            allFeatureVariances[j] += pow(diff, 2);
            allFeatureStdDevs[j] += pow(diff, 2);
        }
    }

    // Counting target's 0 and 1
    for (int i = 0; i < numInstances; i++) {
        if (instances[i].target == 0) {
            targetCount0++;
        } else if (instances[i].target == 1) {
            targetCount1++;
        }
    }

    // Calculate final variance and standard deviation
    printf("\nDatabase Representativeness:\n\n");
    printf("Number of target 0: %d (Percentage: %.2f%%)\n", targetCount0, ((float)targetCount0 / numInstances) * 100);
    printf("Number of target 1: %d (Percentage: %.2f%%)\n\n", targetCount1, ((float)targetCount1 / numInstances) * 100);

    // Open a file for writing statistical summary
    FILE *outputFile = fopen("../data/output.csv", "w");
    if (outputFile == NULL) {
        perror("\n\tError opening output file.\n");
        exit(EXIT_FAILURE);
    }

    // Print statistical summary to the file
    //fprintf(outputFile, "\nStatistical Summary of All Features:\n\n");
    for (int j = 0; j < 30; j++) {
        allFeatureMeans[j] /= numInstances;
        // Calculate mode and median
        float mode = calculateMode(featureValues[j], numInstances);
        float median = calculateMedian(featureValues[j], numInstances);
        allFeatureVariances[j] /= numInstances;
        allFeatureStdDevs[j] = sqrt(allFeatureVariances[j]);

        //fprintf(outputFile, "Mean: %.4f, Mode: %.4f, Median: %.4f,
        //                     Variance: %.4f, Standard Deviation: %.4f\n")
        fprintf(outputFile, "%.4f,%.4f,%.4f,%.4f,%.4f\n",
               allFeatureMeans[j], mode, median,
               allFeatureVariances[j], allFeatureStdDevs[j]);
    }

    // Close the output file
    fclose(outputFile);

    // Free dynamically allocated memory
    for (int j = 0; j < 30; j++) {
        free(featureValues[j]);
    }
    free(featureValues);
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
