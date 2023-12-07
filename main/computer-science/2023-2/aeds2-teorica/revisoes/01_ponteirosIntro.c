#include <stdio.h>
#include <stdlib.h>

int main () {
    int num1 = 10;

    // conteudo
    printf("conteudo: %d\n", num1);

    // endereco
    printf("endereco: %p\n", &num1);

    num1 = 20; // o conteudo mudou, mas o endereco permanece o mesmo.

    // conteudo
    printf("conteudo: %d\n", num1);

    // endereco
    printf("endereco: %p\n", &num1);

    return 0;
}