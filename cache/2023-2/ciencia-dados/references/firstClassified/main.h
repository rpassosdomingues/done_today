#ifndef _H_CLASSIFIED_
#define _H_CLASSIFIED_

#define NUM_FEATURES 30

// Estrutura do modelo do classificador binário
typedef struct {
    double weight;
    double bias;
} BinaryClassifier;

// Estrutura para ler a instância
typedef struct {
    int target;
    float features[NUM_FEATURES];
} Instance;

void readCSV(const char *filename, Instance **instances, int *numInstances);

double sigmoid(double x);
double binary_cross_entropy(double y_true, double y_pred);

void initialize_classifier(BinaryClassifier* model);
double forward_pass(BinaryClassifier* model, double x);

void train_classifier(BinaryClassifier* model, double x, double y_true, double learning_rate, int epochs);

#endif // _H_CLASSIFIED_
