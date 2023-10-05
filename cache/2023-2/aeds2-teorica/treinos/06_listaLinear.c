#include<stdio.h>
#include<stdlib.h>

/**
 * Exercício referente aos slides da aula: Aula05_ListaLinear.pdf
 * Você deve implementar o conteúdo das funções de inserir e remover
 * de modo que todo o programa funcione corretamente.
 * Você não pode alterar mais nenhuma linha de código, exceto o conteúdo das funções.
*/

typedef struct no_
{
    int chave;
    int valor;
    struct no_ * prox;
} no;

void buscar(no* ptlista, int x, no** ant, no** pont){
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

/**
 * pseudocódigo - inserir
*/

// função inserir(no)
// 	insere-enc := -1
// 	busca-enc(no.chave, ant, pont)
// 	se pont = nulo então
// 			no↑.prox := ant↑.prox
// 			ant↑.prox := no
// 			insere-enc := 0

/**
 * implementação - inserir
*/

//Fiz uma pequena alteração no retorno, onde caso a
//inserção ocorra com sucesso, o valor de retorno será NULL.
//Caso o nó já exista, a inserção não será realizada e portanto,
//o valor de retorno será igual ao endereco do no já presente na lista.
no* inserir(no * ptlista, no* novo_no){
    // a variável insere será usada mais tarde para indicar se a inserção deu certo.
    int insere = -1;
    // novo nó e velho nó
    no *ant, *pont;
    // busca e retorna o local de inserção do novo nó.
 	buscar(ptlista, novo_no->chave, &ant, &pont);
    /***
     * se o pont for nulo após a chamada
     * da função 'buscar', isso significa que
     * não há nenhum nó na lista com uma chave
     * maior que a chave do novo nó.
     * portanto, o novo nó pode ser inserido na posição
     * atual. 
    */
 	if (pont == NULL) {
        /***
         * o campo prox do novo_no é definido para apontar
         * para o proximo nó da lista 
         * [que é, no momento, apontado por ant]
        */
 		novo_no->prox = ant->prox;
        /***
         * o campo prox do velho_no (ant)
         * é então definido para apontar para o novo nó.
        */
 		ant->prox = novo_no;
 		insere = 0;
    }
    if (insere != -1) {
        printf("\nSucesso!\n");
    } else {
        printf("\nHouston. I have a problem!\n");
    }
}



/**
 * pseudocódigo - remover
*/

// função remover(x)
// 	remove-enc := nulo
// 	busca-enc(x, ant, pont)
// 	se pont ≠ nulo então
// 			ant↑.prox := pont↑.prox
// 			remove-enc := pont

/**
 * implementação - remover
*/

no* remover(no * ptlista, int x){
    int removido = NULL;
    no *ant, *pont;
    buscar(ptlista, x , &ant, &pont);
    if (pont != NULL) {
        ant->prox = pont->prox;
        removido = pont;
    }
}

void imprimir(no * ptlista){
    if(ptlista->prox == NULL){
        printf("<lista vazia!>");
        return;
    }

    ptlista = ptlista->prox;
    while(ptlista != NULL){
        printf("%d", ptlista->valor);
        ptlista = ptlista->prox;
        printf(" -> ");
        if(ptlista == NULL)
            printf("NULL");
            
    }
}

void desalocar_lista(no * ptlista){
    no * no_prox = ptlista->prox;
    while(no_prox != NULL){
        no * no_temp = no_prox->prox;
        free(no_prox);
        no_prox = no_temp;
    }
    free(ptlista);
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
    no * ptlista;
    ptlista = malloc(sizeof(no));
    ptlista->prox = NULL;

    int resposta = 1;

    while(resposta != 0){
        ler_menu(&resposta);
        if(resposta == 0){
            //sair
            desalocar_lista(ptlista);
            return ;
        } if(resposta == 1){
            //inserir
            no * novo_no = alocar_no();
            if(inserir(ptlista, novo_no) == NULL){
                printf("elemento inserido\n");
            }else{
                printf("nó já existente na lista\n");
            }
        } else if(resposta == 2){
            //remover
            int chave;
            printf("informe a chave do no a ser removido: ");
            scanf("%d", &chave);
            no * no_removido = remover(ptlista, chave);
            if(no_removido != NULL){
                printf("nó removido\n");
                printf("chave: %d\n", no_removido->chave);
                printf("valor: %d\n", no_removido->valor);
                free(no_removido);
            }else{
                printf("nó inexistente\n");
            }

        }else if(resposta == 3){
            //imprimir
            imprimir(ptlista);
        }else {
            printf("Opcao invalida\n");
        }
    }
}
