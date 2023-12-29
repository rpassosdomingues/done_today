/**
 * ____________________________________________
 * --- SVM apply regression in time series ---
 * --------------------------------------------
 * Author: Rafael Passos Domingues
 * ____________________________________________
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libsvm/svm.h>

#include "main.h"

// Function to read data from CSV file
void readData(const char *filename, TimeSeries **data, int *numEntries) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("\n\tFile not found.\n\n");
        exit(EXIT_FAILURE);
    }

    // Counts the number of lines in the file
    *numEntries = 0;
    char buffer[256];
    // Skip the header line
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        fprintf(stderr, "\n\tError reading header from file.\n\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        (*numEntries)++;
    }

    // Back to start of the file
    fseek(file, 0, SEEK_SET);

    // Skip the header line again
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        fprintf(stderr, "\n\tError reading header from file.\n\n");
        exit(EXIT_FAILURE);
    }

    // Allocating memory space to store the data
    *data = (TimeSeries *)malloc(*numEntries * sizeof(TimeSeries));
    if (*data == NULL) {
        perror("\n\tMemory allocation error.\n\n");
        exit(EXIT_FAILURE);
    }

    // Read Data from file to fill struct
    for (int i = 0; i < *numEntries; i++) {
        if (fscanf(file, "%19[^,],%lf\n", (*data)[i].date, &(*data)[i].price) != 2) {
            fprintf(stderr, "\n\tError reading data from file.\n\n");
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
}

// Function to extract features (von Neumann entropy and FFT)
void extractFeatures(const TimeSeries *data, int numEntries, double *vonNeumannEntropy, double *fftResult) {
    // Implement von Neumann entropy calculation and FFT here
    // Replace the following lines with your implementation

    // Dummy values for demonstration purposes
    for (int i = 0; i < numEntries; i++) {
        vonNeumannEntropy[i] = i * 0.1;
        fftResult[i] = i * 0.2;
    }
}

// Function to train and evaluate SVM model
void trainAndEvaluateSVM(const TimeSeries *data, int numEntries) {
    // Extract features
    double vonNeumannEntropy[numEntries];
    double fftResult[numEntries];
    extractFeatures(data, numEntries, vonNeumannEntropy, fftResult);

    // Prepare data for LIBSVM
    struct svm_problem prob;
    prob.l = numEntries;
    prob.y = (double *)malloc(numEntries * sizeof(double));
    prob.x = (struct svm_node **)malloc(numEntries * sizeof(struct svm_node *));
    for (int i = 0; i < numEntries; i++) {
        prob.x[i] = (struct svm_node *)malloc(3 * sizeof(struct svm_node));
        prob.x[i][0].index = 1;
        prob.x[i][0].value = vonNeumannEntropy[i];
        prob.x[i][1].index = 2;
        prob.x[i][1].value = fftResult[i];
        prob.x[i][2].index = -1; // Indicates the end of data
        prob.y[i] = data[i].price;
    }

    // Set SVM parameters
    struct svm_parameter param;
    //svm_parameter_init(&param);
    param.svm_type = EPSILON_SVR;
    param.kernel_type = RBF;
    param.eps = 0.001;
    param.C = 1.0;

    // Train SVM model
    struct svm_model *model = svm_train(&prob, &param);

    // Evaluate SVM model (dummy prediction for demonstration purposes)
    double predictValue = svm_predict(model, prob.x[0]);
    printf("SVM Prediction: %f\n", predictValue);

    // Free allocated memory
    for (int i = 0; i < numEntries; i++) {
        free(prob.x[i]);
    }
    free(prob.x);
    free(prob.y);
    svm_free_and_destroy_model(&model);
}

int main() {
    
    const char *filename = "../data/input.csv";
    TimeSeries *data;
    int numEntries;

    readData(filename, &data, &numEntries);

    // Train and evaluate SVM model
    trainAndEvaluateSVM(data, numEntries);

    // Free allocated memory
    free(data);

    return 0;
}