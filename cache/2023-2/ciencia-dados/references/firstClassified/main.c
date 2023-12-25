/**
 * ____________________________________________
 *      --- Simple binary classifier ---
 * Using a neural network with a single neuron
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

/**
 * ---------------------------------------------
 * Sigmoid Activation Function
 * ---------------------------------------------
 * Narayan, S. (1997).
 * 
 * The generalized sigmoid activation function:
 * Competitive supervised learning.
 * 
 * Information sciences, 99(1-2), 69-82.
 * ---------------------------------------------
*/
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

/**
 * ---------------------------------------------
 * Binary Cross Entropy Loss Function
 * ---------------------------------------------
 * Ruby, U., & Yendapalli, V. (2020).
 * 
 * Binary cross entropy with deep learning
 * technique for image classification.
 * 
 * Int. J. Adv. Trends Comput. Sci. Eng, 9(10).
 * ---------------------------------------------
*/
double binary_cross_entropy(double y_true, double y_pred) {
    return -((y_true * log(y_pred)) + ((1 - y_true) * log(1 - y_pred)));
}

// Initialize the binary classifier
void initialize_classifier(BinaryClassifier* model) {
    model->weight = ((double)rand() / RAND_MAX) * 2.0 - 1.0;  // Random initialization between -1 and 1
    model->bias = 0.0;
}

// Perform the forward pass
double forward_pass(BinaryClassifier* model, double x) {
    return sigmoid(model->weight * x + model->bias);
}

/**
 * -------------------------------------------------------
 * Binary classifier using gradient descent
 * -------------------------------------------------------
 * Pendharkar, P. C. (2007).
 * 
 * A comparison of gradient ascent, gradient descent
 * and genetic‐algorithm‐based artificial neural networks
 * for the binary classification problem.
 * 
 * Expert Systems, 24(2), 65-86.
 * -------------------------------------------------------
*/
void train_classifier(BinaryClassifier* model, double x, double y_true, double learning_rate, int epochs, FILE *outputFile) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        // Forward pass
        double y_pred = forward_pass(model, x);

        // Calculate the loss
        double loss = binary_cross_entropy(y_true, y_pred);

        // Calculate gradients
        double gradient_w = (y_pred - y_true) * x;
        double gradient_b = y_pred - y_true;

        // Update parameters using gradient descent
        model->weight -= learning_rate * gradient_w;
        model->bias -= learning_rate * gradient_b;

        // Salvar época e perda no arquivo CSV
        fprintf(outputFile, "%d,%.4f\n", epoch, loss);

        // Display loss every 100 epochs
        if (epoch % 100 == 0) {
            printf("Epoch %d, Loss: %.4f\n", epoch, loss);
        }
    }
}

int main() {
    
    const char *filename = "../data/input.csv";
    int numInstances;
    Instance *instances;

    readCSV(filename, &instances, &numInstances);

    // Create a binary classifier model
    BinaryClassifier model;
    initialize_classifier(&model);

    // Example training data
    double x_train = 1.0;
    double y_true_train = 0.0;

    // Hyperparameters
    double learning_rate = 0.01;
    int epochs = 1000;

    // Open csv file for write results
    FILE *outputFile = fopen("../data/epochs_losses.csv", "w");
    if (outputFile == NULL) {
        perror("\n\tError opening output file.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(outputFile, "Epoch,Loss\n");

    // Train model
    train_classifier(&model, x_train, y_true_train, learning_rate, epochs, outputFile);

    // Test the trained model
    double y_pred = forward_pass(&model, x_train);
    printf("\nResult: %.4f\n", y_pred);

    fclose(outputFile);

    free(instances);

    return 0;
}
