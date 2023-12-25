/**
 * ____________________________________________
 *      --- Deep binary classifier ---
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
#define LAMBDA 0.01 // Overfitting prevention
#define GRADIENT_CLIP_THRESHOLD 0.01
#define DECAY_EPOCH 100

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
        sscanf(line, "%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
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
 * --------------------------------------------------------
 * Sigmoid Activation Function
 * --------------------------------------------------------
 * Dubey, S. R., Singh, S. K., & Chaudhuri, B. B. (2022).
 * 
 * Activation functions in deep learning:
 * A comprehensive survey and benchmark. Neurocomputing.
 * --------------------------------------------------------
 * 
*/
double sigmoid(double x) {
    if (x >= 0) {
        return 1.0 / (1.0 + exp(-x));
    } else {
        double exp_x = exp(x);
        return exp_x / (1.0 + exp_x);
    }
}

/**
 * -----------------------------------------------------------
 * Binary Cross Entropy Loss Function with L2 Regularization
 * -----------------------------------------------------------
 * Ref [1].
 * Bolinder, O. (2022).
 * Optimizing L2-regularization for Binary Classification Tasks.
 * 
 * ---
 * 
 * Ref [2].
 * Bejani, M. M., & Ghatee, M. (2021).
 * A systematic review on overfitting control in shallow and
 * deep neural networks. Artificial Intelligence Review, 1-48.
 * -----------------------------------------------------------
*/
double binary_cross_entropy(double y_true, double y_pred, NeuralNetwork *model) {
    double loss = -((y_true * log(y_pred)) + ((1 - y_true) * log(1 - y_pred)));

    double l2_regularization_output = 0.0;
    for (int j = 0; j < HIDDEN_SIZE; ++j) {
        l2_regularization_output += model->weights_hidden_output[j][0] * model->weights_hidden_output[j][0];
    }

    double l2_regularization_hidden = 0.0;
    for (int i = 0; i < INPUT_SIZE; ++i) {
        for (int j = 0; j < HIDDEN_SIZE; ++j) {
            l2_regularization_hidden += model->weights_input_hidden[i][j] * model->weights_input_hidden[i][j];
        }
    }

    loss += 0.5 * LAMBDA * (l2_regularization_output + l2_regularization_hidden);

    return loss;
}

/**
 * Rimer, M., & Martinez, T. (2004, July).
 * 
 * Softprop: softmax neural network backpropagation learning.
 * 
 * In 2004 IEEE International Joint Conference on Neural Networks
 * (IEEE Cat. No. 04CH37541) (Vol. 2, pp. 979-983). IEEE.
*/
void stable_softmax(double *values, int num_values) {
    double max_val = values[0];
    for (int i = 1; i < num_values; ++i) {
        if (values[i] > max_val) {
            max_val = values[i];
        }
    }

    double exp_sum = 0.0;
    for (int i = 0; i < num_values; ++i) {
        exp_sum += exp(values[i] - max_val);
    }

    for (int i = 0; i < num_values; ++i) {
        values[i] = exp(values[i] - max_val) / exp_sum;
    }
}

/**
 * Liu, M., Zhuang, Z., Lei, Y., & Liao, C. (2022).
 * 
 * A communication-efficient distributed gradient clipping algorithm
 * for training deep neural networks.
 * 
 * Advances in Neural Information Processing Systems, 35, 26204-26217.
*/
void clip_gradients(double *gradient, double threshold) {
    if (*gradient > threshold) {
        *gradient = threshold;
    } else if (*gradient < -threshold) {
        *gradient = -threshold;
    }
}

/**
 * --------------------------------------------------------------------------------
 * Exponential decay sine wave learning rate for fast deep neural network training.
 * --------------------------------------------------------------------------------
 * An, W., Wang, H., Zhang, Y., & Dai, Q. (2017, December).
 * In 2017 IEEE Visual Communications and Image Processing (VCIP) (pp. 1-4). IEEE.
 * --------------------------------------------------------------------------------
*/
double decayed_learning_rate(double initial_lr, int epoch, int decay_epoch) {
    return initial_lr / (1.0 + decay_epoch * epoch);
}

// Initialize the neural network
void initialize_neural_network(NeuralNetwork* model) {
    // Initialize weights and biases with small random values
    for (int i = 0; i < INPUT_SIZE; ++i) {
        for (int j = 0; j < HIDDEN_SIZE; ++j) {
            model->weights_input_hidden[i][j] = ((double)rand() / RAND_MAX) * 0.1;
        }
    }

    for (int i = 0; i < HIDDEN_SIZE; ++i) {
        model->biases_hidden[i] = 0.0;
        for (int j = 0; j < OUTPUT_SIZE; ++j) {
            model->weights_hidden_output[i][j] = ((double)rand() / RAND_MAX) * 0.1;
        }
    }

    model->bias_output = 0.0;
}

// Perform the forward pass through the neural network
void forward_pass(NeuralNetwork* model, double* input, double* output) {
    // Hidden layer
    double hidden[HIDDEN_SIZE];
    for (int j = 0; j < HIDDEN_SIZE; ++j) {
        hidden[j] = 0.0;
        for (int i = 0; i < INPUT_SIZE; ++i) {
            hidden[j] += input[i] * model->weights_input_hidden[i][j];
        }
        hidden[j] = sigmoid(hidden[j] + model->biases_hidden[j]);
    }

    // Output layer
    *output = 0.0;
    for (int j = 0; j < HIDDEN_SIZE; ++j) {
        *output += hidden[j] * model->weights_hidden_output[j][0];
    }
    *output = sigmoid(*output + model->bias_output);
}

/**
 * -----------------------------------------------------------------------
 * Train the neural network using gradient descent with L2 regularization
 * -----------------------------------------------------------------------
 * Murugan, P., & Durairaj, S. (2017).
 * 
 * Regularization and optimization strategies
 * in deep convolutional neural network.
 * 
 * arXiv preprint arXiv:1712.04711.
 * -----------------------------------------------------------------------
*/
void train_neural_network(NeuralNetwork *model, Instance *instances, int numInstances, double learning_rate, int epochs, FILE *outputFile) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        double total_loss = 0.0;

        for (int i = 0; i < numInstances; ++i) {
            double output;
            forward_pass(model, instances[i].features, &output);

            double loss = binary_cross_entropy((double)instances[i].target, output, model);

            double delta_output = output - (double)instances[i].target;

            // Update weights and biases with gradient clipping
            for (int j = 0; j < HIDDEN_SIZE; ++j) {
                double gradient_output = delta_output * sigmoid(output) * (1 - sigmoid(output)) * model->weights_hidden_output[j][0] + LAMBDA * model->weights_hidden_output[j][0];
                clip_gradients(&gradient_output, GRADIENT_CLIP_THRESHOLD);
                model->weights_hidden_output[j][0] -= learning_rate * gradient_output;
            }
            double gradient_output_bias = delta_output * sigmoid(output) * (1 - sigmoid(output)) * model->bias_output;
            clip_gradients(&gradient_output_bias, GRADIENT_CLIP_THRESHOLD);
            model->bias_output -= learning_rate * gradient_output_bias;

            for (int j = 0; j < HIDDEN_SIZE; ++j) {
                for (int k = 0; k < INPUT_SIZE; ++k) {
                    double gradient_hidden = delta_output * sigmoid(output) * (1 - sigmoid(output)) * model->weights_input_hidden[k][j] * sigmoid(instances[i].features[k]) * (1 - sigmoid(instances[i].features[k])) + LAMBDA * model->weights_input_hidden[k][j];
                    clip_gradients(&gradient_hidden, GRADIENT_CLIP_THRESHOLD);
                    model->weights_input_hidden[k][j] -= learning_rate * gradient_hidden;
                }
                double gradient_hidden_bias = delta_output * sigmoid(output) * (1 - sigmoid(output)) * model->biases_hidden[j];
                clip_gradients(&gradient_hidden_bias, GRADIENT_CLIP_THRESHOLD);
                model->biases_hidden[j] -= learning_rate * gradient_hidden_bias;
            }

            total_loss += loss;
        }

        total_loss /= numInstances;

        fprintf(outputFile, "%d,%.4f\n", epoch, total_loss);

        if (epoch % 100 == 0) {
            printf("Epoch %d, Loss: %.4f\n", epoch, total_loss);
        }

        learning_rate = decayed_learning_rate(learning_rate, epoch, DECAY_EPOCH);
    }
}

int main() {
    const char *filename = "../data/input.csv";
    int numInstances;
    Instance *instances;

    readCSV(filename, &instances, &numInstances);

    NeuralNetwork model;
    initialize_neural_network(&model);

    double learning_rate = 0.01;
    int epochs = 1000;

    FILE *outputFile = fopen("../data/epochs_losses.csv", "w");
    if (outputFile == NULL) {
        perror("\n\tError opening output file.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(outputFile, "Epoch,Loss\n");

    train_neural_network(&model, instances, numInstances, learning_rate, epochs, outputFile);

    double input[INPUT_SIZE];
    for (int i = 0; i < INPUT_SIZE; ++i) {
        input[i] = instances[0].features[i];
    }

    double output;
    forward_pass(&model, input, &output);
    printf("\nResult: %.4f\n", output);

    fclose(outputFile);
    free(instances);

    return 0;
}
