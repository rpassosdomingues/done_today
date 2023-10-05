#include <stdio.h>

typedef struct {
  int parts;
  float price;
} Sale;

void printTotalSales (Sale *s1, Sale *s2) {
  Sale total = {0, 0.0};
  
  total.parts = (*s1).parts + (*s2).parts;
  total.price = (*s1).price + (*s2).price;
  
  printf("Number of parts: %d\n", total.parts);
  printf("    Total Price: %.2f\n", total.price);
}

int main () {
  Sale s1 = {1, 20}, s2 = {3, 10};
  printTotalSales(&s1, &s2);
  return 0;
}
