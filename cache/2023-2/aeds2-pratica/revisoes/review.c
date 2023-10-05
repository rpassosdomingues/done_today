#include<stdio.h>

int main() {
  const double PI = 3.141592;
  double radius;
  
  printf("\n Enter a radius of circle: ");
  scanf("%lf", &radius);
  
  double squareCircle = PI * radius*radius;
  
  printf("\n\t The square of circle is %lf m² \n\n", squareCircle);
  
  return 0;
}

