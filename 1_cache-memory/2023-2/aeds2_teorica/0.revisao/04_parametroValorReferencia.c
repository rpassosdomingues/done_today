/**
 * Passsagem de parâmetro por valor VS por referência 
*/

#include <stdio.h>
#include <stdlib.h>

/**
 * Recebe um ponteiro para um número inteiro e retorna o dobro do valor dele. 
*/
void dobra (int (*n)) {
    (*n) = (*n) * 2;
    printf("\nValor de n: %d", (*n));
    //printf("\nEndereco de n: %p", n);
}

int main () {
    int num1 = 10;

    //dobra(num1); // Passagem de parâmetro por valor
    dobra(&num1);  // Passagem de parâmetro por referência
                   // [Alterações feitas dentro das funções serão refletidas na função main]
    
    printf("\nValor de num1: %d", num1);
    //printf("\nEndereco de num1: %p\n", num1);

    return 0;
}