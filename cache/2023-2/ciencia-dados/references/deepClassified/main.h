#ifndef _H_CLASSIFIED_
#define _H_CLASSIFIED_

#define INPUT_SIZE 30  // Number of features
#define HIDDEN_SIZE 5  // Number of neurons in the hidden layer
#define OUTPUT_SIZE 1  // Number of output neurons

// Binary classifier model structure
typedef struct {
    double weights_input_hidden[INPUT_SIZE][HIDDEN_SIZE];
    double biases_hidden[HIDDEN_SIZE];
    double weights_hidden_output[HIDDEN_SIZE][OUTPUT_SIZE];
    double bias_output;
} NeuralNetwork;

// Structure to read the instance
typedef struct {
    double features[INPUT_SIZE];
    int target;
} Instance;

void readCSV(const char *filename, Instance **instances, int *numInstances);

double sigmoid(double x);
double binary_cross_entropy(double y_true, double y_pred, NeuralNetwork* model);

void stable_softmax(double *values, int num_values);
void clip_gradients(double *gradient, double threshold);
double decayed_learning_rate(double initial_lr, int epoch, int decay_epoch);

void initialize_neural_network(NeuralNetwork* model);
void forward_pass(NeuralNetwork* model, double* input, double* output);
void train_neural_network(NeuralNetwork* model, Instance* instances, int numInstances, double learning_rate, int epochs, FILE *outputFile);

#endif // _H_CLASSIFIED_
