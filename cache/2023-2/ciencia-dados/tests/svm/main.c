/**
 * ____________________________________________________________
 *             --- Time series forecasting ---
 * ------------------------------------------------------------
 * using a combination of methods including feature extraction,
 * training a support vector machine (SVM) model,
 * and forecasting with a sliding window
 * ------------------------------------------------------------
 * Author: Rafael Passos Domingues
 * ____________________________________________________________
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
double vonNeumannEntropy(const double *data, int size) {
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
void extractFeatures(const TimeSeries *data, int numEntries, double *vonNeumannEntropyArray, double *fftResult) {
    for (int i = 0; i < numEntries; i++) {
        // Assuming vonNeumannEntropyArray, fftResult are arrays with appropriate sizes
        double vonNeumannData[numEntries]; // Use numEntries as the size
        double fftData[numEntries];        // Use numEntries as the size

        // Populate vonNeumannData and fftData arrays (replace with your logic)
        vonNeumannData[i] = data[i].price * 0.1; // Replace with actual calculation
        fftData[i] = data[i].price * 0.2;        // Replace with actual calculation

        // Calculate von Neumann entropy
        vonNeumannEntropyArray[i] = vonNeumannEntropy(vonNeumannData, numEntries);

        // Perform FFT
        performFFT(fftData, numEntries, fftResult);

        // Calculate subjective features (replace with your logic)
        data[i].subjectiveFeature1 = data[i].price * 0.3;
        data[i].subjectiveFeature2 = data[i].price * 0.4;
    }
}

// Function to train SVM model
struct svm_model* trainSVM(const TimeSeries *data, int numEntries) {
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

    return model;
}

// Function to train and evaluate SVM model
void trainAndEvaluateSVM(const TimeSeries *data, int numEntries, struct svm_model **model) {
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
    param.svm_type = EPSILON_SVR;
    param.kernel_type = RBF;
    param.eps = 0.001;
    param.C = 1.0;

    // Train SVM model
    *model = svm_train(&prob, &param);

    // Evaluate SVM model (dummy prediction for demonstration purposes)
    double predictValue = svm_predict(*model, prob.x[0]);
    printf("SVM Prediction: %f\n", predictValue);

    // Free allocated memory
    for (int i = 0; i < numEntries; i++) {
        free(prob.x[i]);
    }
    free(prob.x);
    free(prob.y);
}

Forecast* forecast(const TimeSeries *data, int numEntries, int windowSize, int numSteps, const struct svm_model *model) {
    // Extract features with the sliding window
    double vonNeumannEntropy[numEntries];
    double fftResult[numEntries];
    extractFeatures(data, numEntries, vonNeumannEntropy, fftResult);

    // Prepare data for LIBSVM
    Forecast *forecastData = (Forecast *)malloc(numSteps * sizeof(Forecast));
    if (forecastData == NULL) {
        perror("\n\tErro na alocação de memória.\n\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numSteps; i++) {
        // Extract features for the current step using the last window
        double currentVonNeumannEntropy, currentFFTResult;

        currentVonNeumannEntropy = vonNeumannEntropy[numEntries - windowSize + i];
        currentFFTResult = fftResult[numEntries - windowSize + i];

        // Prepare input vector for prediction
        struct svm_node x[3];
        x[0].index = 1;
        x[0].value = currentVonNeumannEntropy;
        x[1].index = 2;
        x[1].value = currentFFTResult;
        x[2].index = -1; // Indicates the end of the data

        // Predict using the SVM model
        double prediction = svm_predict(model, x);

        // Store the predicted value along with the date
        strcpy(forecastData[i].date, data[numEntries - windowSize + i].date);
        forecastData[i].predictedPrice = prediction;
    }

    return forecastData;
}

int main() {
    const char *filename = "../data/input.csv";
    TimeSeries *data;
    int numEntries;
    int windowSize = 10; // Fit an appropriate window size // to-do
    int numSteps = 100;

    readData(filename, &data, &numEntries);

    // Train SVM model
    struct svm_model *model = trainSVM(data, numEntries);
    trainAndEvaluateSVM(data, numEntries, &model);

    // Extract features for forecast
    double vonNeumannEntropy[numEntries];
    double fftResult[numEntries];

    extractFeatures(data, numEntries, vonNeumannEntropy, fftResult);

    // Forecast with Sliding Window
    Forecast *forecastData = forecast(data, numEntries, windowSize, numSteps, model);

    // Forecast values and write to output file
    FILE *outputFile = fopen("../data/output.csv", "w");
    if (outputFile == NULL) {
        perror("\n\tError opening output file.\n\n");
        exit(EXIT_FAILURE);
    }

    fprintf(outputFile, "Date,PredictedPrice,SubjectiveFeature1,SubjectiveFeature2\n");
    for (int i = 0; i < numSteps; i++) {
        fprintf(outputFile, "%s,%f,%f,%f\n", forecastData[i].date, forecastData[i].predictedPrice,
                data[numEntries - windowSize + i].subjectiveFeature1, data[numEntries - windowSize + i].subjectiveFeature2);
    }

    // Close the output file
    fclose(outputFile);

    // Free allocated memory
    free(data);
    free(forecastData);
    svm_free_and_destroy_model(&model);

    return 0;
}
