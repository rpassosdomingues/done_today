# include <stdio.h>

void swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main () {

    int a = 10;
    int b = 20;

    swap (&a, &b);

    printf("\na = %d", a);
    printf("\nb = %d\n\n", b);

    return (0);
}
