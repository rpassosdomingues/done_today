# include <stdio.h>
# define LENGTH 4

typedef struct {
  int array[LENGTH];
  int key;
  int value;
} data;

int sortSearch (data array[], int n, int wanted) {
  array[n+1].key = wanted;
  int i = 0;
  while (array[i].key < wanted) {
    i++;
  }
  if (i == n+1 || array[i].key != wanted) {
    return (i);
  } else {
      return (-1);
    }
}

int main () {

  data array[LENGTH];
  
  array[0].key = 1;
  array[0].value = 10;
  
  array[1].key = 2;
  array[1].value = 20;
  
  array[2].key = 3;
  array[2].value = 30;
  
  int wanted = 1;
  
  int found = sortSearch (array, LENGTH, wanted);
  if (found == -1) {
    printf("\nWanted not found.\n\n");
  } else {
      printf("\nWanted was found in the position %d.\n\n", found);
    }
  
  return (0);
}
