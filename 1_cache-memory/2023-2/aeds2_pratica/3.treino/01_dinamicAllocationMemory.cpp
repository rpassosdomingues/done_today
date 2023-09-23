#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    int length;

    cout << "\n\nEnter a length of the array: ";
    cin >> length;

    srand(time(NULL));

    int *array = new int[length];

    for (int i = 0; i < length; i++) {
        array[i] = rand() % 100;
    }

    cout << "\nSuccessfully allocated memory!\n" << endl;
    cout << "\narray: { ";
    for (int i = 0; i < length; i++) {
        cout << array[i] << " ";
    }
    cout << "}\n" << endl;

    delete[] array;
    cout << "\nSuccessfully freed memory!\n" << endl;

    return (0);
}
