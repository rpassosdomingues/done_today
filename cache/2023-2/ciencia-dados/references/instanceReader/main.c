/**
 * ____________________________________________
 *  - Instance Reader: Features Recognition -
 * --------------------------------------------
 * Author: Rafael Passos Domingues
 * ____________________________________________
*/

#include <stdio.h>
#include <stdlib.h>

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

int main() {
    
    const char *filename = "../data/input.csv";
    int numInstances;
    Instance *instances;

    readCSV(filename, &instances, &numInstances);

    printf("\n\tFeatures successfully recognized!\n\n");

    free(instances);

    return 0;
}
