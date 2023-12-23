#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "main.h"

#define MAX_LINE_LENGTH 1024

void readCSV(const char *filename, Instance **instances, int *numInstances) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];

    // Conta o número de instâncias no arquivo
    *numInstances = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        (*numInstances)++;
    }

    // Volta para o início do arquivo
    fseek(file, 0, SEEK_SET);

    // Aloca memória para armazenar as instâncias
    *instances = (Instance *)malloc(*numInstances * sizeof(Instance));
    if (*instances == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    // Lê as instâncias do arquivo
    for (int i = 0; i < *numInstances; i++) {
        fgets(line, sizeof(line), file);

        // Utilize sscanf para extrair os valores da linha formatada
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

// Função de ativação sigmoide
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Função de perda de entropia cruzada binária
double binary_cross_entropy(double y_true, double y_pred) {
    return -((y_true * log(y_pred)) + ((1 - y_true) * log(1 - y_pred)));
}

// Inicializar o classificador binário
void initialize_classifier(BinaryClassifier* model) {
    model->weight = ((double)rand() / RAND_MAX) * 2.0 - 1.0;  // Inicialização aleatória entre -1 e 1
    model->bias = 0.0;
}

// Realizar o forward pass
double forward_pass(BinaryClassifier* model, double x) {
    return sigmoid(model->weight * x + model->bias);
}

// Treinar o classificador binário usando gradiente descendente
void train_classifier(BinaryClassifier* model, double x, double y_true, double learning_rate, int epochs) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        // Forward pass
        double y_pred = forward_pass(model, x);

        // Calcular a perda
        double loss = binary_cross_entropy(y_true, y_pred);

        // Calcular gradientes
        double gradient_w = (y_pred - y_true) * x;
        double gradient_b = y_pred - y_true;

        // Atualizar parâmetros usando gradiente descendente
        model->weight -= learning_rate * gradient_w;
        model->bias -= learning_rate * gradient_b;

        // Exibir a perda a cada 100 épocas
        if (epoch % 100 == 0) {
            printf("Época %d, Perda: %.4f\n", epoch, loss);
        }
    }
}

int main() {
    // Configurar uma semente aleatória para reprodução
    srand(42);

    const char *filename = "../data/input.csv";
    int numInstances;
    Instance *instances;

    readCSV(filename, &instances, &numInstances);

    // Criar um modelo de classificador binário
    BinaryClassifier model;
    initialize_classifier(&model);

    // Dados de treinamento de exemplo
    double x_train = 1.0;
    double y_true_train = 0.0;  // Rótulo esperado (0 para exemplo de negativo)

    // Hiperparâmetros
    double learning_rate = 0.01;
    int epochs = 1000;

    // Treinar o modelo
    train_classifier(&model, x_train, y_true_train, learning_rate, epochs);

    // Testar o modelo treinado
    double y_pred = forward_pass(&model, x_train);
    printf("Resultado do Teste: %.4f\n", y_pred);

    free(instances);

    return 0;
}
