#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>

using namespace std;

// Function to generate an ordered array and shuffle it
void randomArrayGenerator(int length, int randomArray[]) {
    for (int i = 0; i < length; i++) {
        randomArray[i] = i;
    }

    // shuffle array
    for (int i = length - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = randomArray[i];
        randomArray[i] = randomArray[j];
        randomArray[j] = temp;
    }
}

int main() {
    const int start = 10;
    const int end = 100;
    const int step = 10;

    ofstream outputFile("random_array.txt");
    if (!outputFile.is_open()) {
        cout << "Unable to open the file." << endl;
        return 1;
    }

    int shuffleArray[end];
    for (int length = start; length <= end; length += step) {
        // Generate a random array to be shuffled
        randomArrayGenerator(length, shuffleArray);

        // Random Shuffle Array
        int randomArray[length];
        for (int i = 0; i < length; i++) {
            randomArray[i] = shuffleArray[i];
        }

        // Save the array in the file
        for (int i = 0; i < length; i++) {
            outputFile << randomArray[i] << " ";
        }
        outputFile << endl;
    }

    outputFile.close();
    cout << "Random arrays saved in 'random_array.txt' successfully." << endl;

    return 0;
}
