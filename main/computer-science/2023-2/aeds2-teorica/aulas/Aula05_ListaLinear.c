#include<stdio.h>
#include<stdlib.h>

/**
* Códigos referentes aos slides da aula: Aula05_ListaLinear
**/

typedef struct no_
{
    int chave;
    int valor;
    struct no_ * prox;
} no;

/**
* pseudocódigo - buscar
**/

//procedimento buscar(x, ant, pont)
//	ant := ptlista;
//  pont := nulo
//	ptr := ptlista↑.prox
//
//	enquanto ptr ≠ nulo faça
//			se ptr↑.chave < x então
//				ant := ptr
//				ptr := ptr↑.prox
//			senão se ptr↑.chave = x então
//					pont := ptr
//				ptr := nulo

/**
* implementacao - buscar
**/

void buscar(no* ptlista,
    int x, no** ant, no** pont){
    *ant = ptlista;
    *pont = NULL;
    no * ptr = ptlista->prox;

    while(ptr != NULL){
        if(ptr->chave < x){
            *ant = ptr;
            ptr = ptr->prox;
        }else{
            if(ptr->chave == x){
                *pont = ptr;
            }
            ptr = NULL;
        }
    }
}

void main(){
    no * ptlista;
    ptlista = malloc(sizeof(no));
    
    //alocando o primeiro nó e atribuindo o seu valor de chave.
    //usei a notação de ponteiro,
    //lembrando que as linhas comentadas são equivalentes (mas em notação de seta).

    //ptlista->prox = malloc(sizeof(no));
    (*ptlista).prox = malloc(sizeof(no));
    //ptlista->prox->chave = 5;
    (*(*ptlista).prox).chave = 5;
    

    //alocando o segundo nó e atribuindo o seu valor de chave.
    //usei a notação de seta, para vocês poderem comparar.
    //vocês conseguem converter de volta para a notação de ponteiro?
    ptlista->prox->prox = malloc(sizeof(no));
    ptlista->prox->prox->chave = 10;
    ptlista->prox->prox->prox = NULL;

    //descomente as linhas a seguir, e complete os parâmetros que faltam para a função buscar.
    //como você vai declarar ant e pont?

    no ** ant = malloc(sizeof(no*));
    no ** pont = malloc(sizeof(no*));

    buscar(ptlista, 10, ant, pont);
    printf("endereco: %p\n", *pont);
    if(*pont != NULL)
        printf("chave: %d\n", (*(*pont)).chave);
}
