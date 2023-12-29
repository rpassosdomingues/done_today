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
#include <math.h>
#include <fftw3.h>
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

// Function to calculate von Neumann entropy
double calculateVonNeumannEntropy(const double *data, int size) {
    double sum = 0.0;

    for (int i = 0; i < size; i++) {
        double probability = data[i] / 100.0;  // Assuming data is in the range [0, 100]
        if (probability > 0.0) {
            sum += probability * log2(probability);
        }
    }

    return -sum;
}

// Function to perform FFT using FFTW library
void performFFT(const double *data, int size, double *result) {
    fftw_complex *in, *out;
    fftw_plan plan;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size);

    for (int i = 0; i < size; i++) {
        in[i][0] = data[i];
        in[i][1] = 0.0;
    }

    plan = fftw_plan_dft_1d(size, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);

    for (int i = 0; i < size; i++) {
        result[i] = out[i][0];
    }

    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);
}

// Function to extract features (von Neumann entropy and FFT)
void extractFeatures(const TimeSeries *data, int numEntries, double *vonNeumannEntropy, double *fftResult) {
    int dataSize = 100;  // Adjust this based on your data size or requirements

    for (int i = 0; i < numEntries; i++) {
        // Assuming the time series data is in the 'price' field
        double timeSeriesData = data[i].price;

        vonNeumannEntropy[i] = calculateVonNeumannEntropy(&timeSeriesData, 1);

        // Perform FFT directly on the result array
        performFFT(&timeSeriesData, dataSize, &fftResult[i * dataSize]);
    }
}

// Function to train and evaluate SVM model
void trainAndEvaluateSVM(const TimeSeries *data, int numEntries) {
    // Extract features
    double vonNeumannEntropy[numEntries];
    
    // Assuming the size of FFT result is variable based on the FFT size
    int fftSize = 100;  // Adjust this based on your data size or requirements
    double *fftResult = (double *)malloc(numEntries * fftSize * sizeof(double));

    extractFeatures(data, numEntries, vonNeumannEntropy, fftResult);

    // Prepare data for LIBSVM
    struct svm_problem prob;
    prob.l = numEntries;
    prob.y = (double *)malloc(numEntries * sizeof(double));
    prob.x = (struct svm_node **)malloc(numEntries * sizeof(struct svm_node *));
    for (int i = 0; i < numEntries; i++) {
        prob.x[i] = (struct svm_node *)malloc((2 + fftSize) * sizeof(struct svm_node));
        prob.x[i][0].index = 1;
        prob.x[i][0].value = vonNeumannEntropy[i];
        prob.x[i][1].index = 2;

        // Include FFT values in the SVM input
        for (int j = 0; j < fftSize; j++) {
            prob.x[i][j + 2].index = j + 3;
            prob.x[i][j + 2].value = fftResult[i * fftSize + j];
        }

        prob.x[i][fftSize + 2].index = -1; // Indicates the end of data
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
    free(fftResult);
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
