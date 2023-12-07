# include <stdio.h>
# define LENGTH 6

typedef struct {
  int array[LENGTH];
  int key;
  int value;
} data;

int binarySearch (data array[], int n, int wanted) {
  int head = n, tail = 0;
  while (tail <= head) {
    int half = (tail + head)/2;
    if (array[half].key == wanted) {
      return (half);
      tail = head + 1;
    } else if (array[half].key < wanted) {
        tail = half + 1;
      } else
      	  head = half - 1;
  }
  return (-1);
}

int main () {

  data array[LENGTH];
  
  array[0].key = 1;
  array[1].key = 2;
  array[2].key = 3;
  array[3].key = 4;
  array[4].key = 5;
  array[5].key = 6;
  
  int wanted = 3;
  
  int found = binarySearch (array, LENGTH, wanted);
  
  if (found == -1) {
    printf("\nWanted not found.\n\n");
  } else {
      printf("\nWanted was found in the position %d.\n\n", found);
    }
  
  return (0);
}
