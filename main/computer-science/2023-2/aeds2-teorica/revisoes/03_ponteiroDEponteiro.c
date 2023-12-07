#include <stdio.h>
#include <stdlib.h>

int main () {
    int num1 = 10;
    // "Não há limites" para criação de ponteiros de ponteiros. 
    int *pont1 = &num1;
    int **pont2 = &pont1;
    //int ***pont3 = &pont2;

    // Conteúdo de pont2 = Endereço de pont1.
    printf("................................\n");
    printf("    Segundo ponteiro: %p\n", pont2);
    printf("Endereco do ponteiro: %p\n", &pont1);
    // Conteúdo de pont2 = Endereço de num1.
    printf("................................\n");
    printf("Conteudo do ponteiro: %p\n", *pont2);
    printf("Endereco da variavel: %p\n", &num1);
    // Conteúdo do conteúdo de pont2 = Conteúdo de num1.
    printf("................................\n");
    printf("Conteudo do conteudo: %d\n", **pont2);
    printf("................................\n");

    return 0;
}
