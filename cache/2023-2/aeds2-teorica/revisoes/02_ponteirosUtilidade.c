#include <stdio.h>
#include <stdlib.h>

int main () {
    int num1 = 10;

    int *pont1;         // isso eh um ponteiro
    pont1 = &num1;

    // conteudo de num1
    printf("    conteudo da variavel: %d\n", num1);
    // endereco de num1
    printf("    endereco da variavel: %p\n", &num1);
    // conteudo do ponteiro que guarda o endereco de num1
    printf("ponteiro para a variavel: %p\n", pont1);
    // endereco de pont1
    printf("    endereco do ponteiro: %p\n", &pont1);

    return 0;
}