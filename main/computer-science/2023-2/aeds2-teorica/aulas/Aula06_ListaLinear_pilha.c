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
 * pseudocódigo - inserir_pilha
*/

// procedimento inserir_pilha(no)
// 	no↑.prox := topo
// 	topo := no

/**
 * implementação - inserir_pilha
*/

void inserir_pilha(no ** topo, no* novo_no){
    novo_no->prox = (*topo);
    *topo = novo_no;
}

/**
 * pseudocódigo - remover_pilha
*/

// função remover_pilha( )
// 	remove-pilha := nulo
// 	se topo ≠ nulo então
// 		remove-pilha := topo
// 		topo := topo↑.prox

/**
 * implementação - remover_pilha
*/

no* remover_pilha(no ** topo){
    no* tmp = NULL;
    if(*topo != NULL){
        tmp = *topo;
        (*topo) = (*(*topo)).prox;
    }
    return tmp;
}

void imprimir(no * topo){
    if(topo == NULL){
        printf("pilha vazia");
        return;
    }

    printf("topo --> ");
    while(topo != NULL){
        printf("%d:%d", topo->chave, topo->valor);
        topo = topo->prox;
        if(topo != NULL)
            printf(" -> ");
    }
}

void desalocar_lista(no * topo){
    while(topo != NULL){
        no * no_temp = topo->prox;
        free(topo);
        topo = no_temp;
    }
}

void desalocar_pilha(no * topo){
    while(topo != NULL){
        no * no_temp = topo->prox;
        printf("desalocando: %d:%d\n", topo->chave, topo->valor);
        free(topo);
        topo = no_temp;
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
    no * topo = NULL;

    int resposta = 1;

    while(resposta != 0){
        ler_menu(&resposta);
        if(resposta == 0){
            //sair
            desalocar_pilha(topo);
            return ;
        } if(resposta == 1){
            //inserir
            no * novo_no = alocar_no();
            inserir_pilha(&topo, novo_no);
        } else if(resposta == 2){
            //remover
            no* no_removido = remover_pilha(&topo);
            if(no_removido != NULL){
                printf("nó removido\n");
                printf("chave: %d\n", no_removido->chave);
                printf("valor: %d\n", no_removido->valor);
                free(no_removido);
            }else{
                printf("pilha vazia");
            }
        }else if(resposta == 3){
            //imprimir
            imprimir(topo);
        }else {
            printf("Opcao invalida\n");
        }
    }
}
