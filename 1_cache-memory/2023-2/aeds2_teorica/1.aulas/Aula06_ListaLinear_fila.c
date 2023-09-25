#include<stdio.h>
#include<stdlib.h>

/**
* Códigos referentes aos slides da aula: Aula06_ListaLinear
**/

typedef struct no_
{
    int chave;
    int valor;
    struct no_ * prox;
} no;

/**
 * pseudocódigo - inserir_fila
*/

// procedimento inserir_fila(no)
// 	se	fim ≠ nulo então
// 		fim↑.prox := no
// 	senão inicio := no
// fim := no

/**
 * implementação - inserir_fila
*/

void inserir_fila(no** inicio, no** fim, no* novo_no){
    if(*fim != NULL){
        (*(*fim)).prox = novo_no;
    }else{
        (*inicio) = novo_no;
    }
    (*fim) = novo_no;
}

/**
 * pseudocódigo - remover_fila
*/

// função remover_fila( )
// 	remove-fila := nulo
// 	se inicio ≠ nulo então
// 		remove-fila := inicio
// 		inicio := inicio↑.prox
// 		se inicio = nulo então fim := nulo

/**
 * implementação - remover_fila
*/

no* remover_fila(no** inicio, no** fim){
    no* tmp = NULL;
    if(*inicio != NULL){
        tmp = *inicio;
        *inicio = (*(*inicio)).prox;
        if(*inicio == NULL){
            *fim = NULL;
        }
    }
    return tmp;
}

void imprimir(no * inicio){
    if(inicio == NULL){
        printf("fila vazia");
        return;
    }

    printf("inicio --> ");
    while(inicio != NULL){
        printf("%d:%d", inicio->valor, inicio->chave);
        inicio = inicio->prox;
        if(inicio != NULL)
            printf(" -> ");
        else
            printf(" <-- fim");
    }
}

void desalocar_fila(no * inicio){
    while(inicio != NULL){
        no * no_temp = inicio->prox;
        printf("desalocando: %d:%d\n", inicio->chave, inicio->valor);
        free(inicio);
        inicio = no_temp;
    }
}

void ler_menu(int * resposta){
    printf("\n-----------------------\n");
    printf("escolha uma das opcoes:\n");
    printf("0 - sair\n");
    printf("1 - inserir\n");
    printf("2 - remover\n");
    printf("3 - imprimir\n");
    scanf("%d", resposta);
    printf("-----------------------\n\n");
}

no* alocar_no(){
    no * novo_no = malloc(sizeof(no));
    printf("informe a chave: ");
    scanf("%d", &(*novo_no).chave);
    printf("informe o valor: ");
    scanf("%d", &(*novo_no).valor);
    printf("\n");
    novo_no->prox = NULL;
    return novo_no;
}


void main(){
    no * inicio = NULL;
    no * fim = NULL;

    int resposta = 1;

    while(resposta != 0){
        ler_menu(&resposta);
        if(resposta == 0){
            //sair
            desalocar_fila(inicio);
            return ;
        } if(resposta == 1){
            //inserir
            no * novo_no = alocar_no();
            inserir_fila(&inicio, &fim, novo_no);
        } else if(resposta == 2){
            //remover
            no* no_removido = remover_fila(&inicio, &fim);
            if(no_removido != NULL){
                printf("nó removido\n");
                printf("chave: %d\n", no_removido->chave);
                printf("valor: %d\n", no_removido->valor);
                free(no_removido);
            }else{
                printf("fila vazia");
            }
        }else if(resposta == 3){
            //imprimir
            imprimir(inicio);
        }else {
            printf("Opcao invalida\n");
        }
    }
}
