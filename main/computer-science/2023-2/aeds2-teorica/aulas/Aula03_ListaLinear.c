#include<stdio.h>
#include<stdlib.h>

/**
* Códigos referentes aos slides da aula: Aula03_ListaLinear
**/

typedef struct no_
{
    int chave;
    int valor;
} no;

/**
* implementacao - buscar (versão 2)
**/

int buscar (no L[], int n, int x){
    L[n].chave = x;
    int i = 0;
    while(L[i].chave != x){
        i = i+1;//i++
    }

    if(i != n){
        return i;
    }
    return -1;
}

/**
* pseudocódigo - inserir
**/

// função inserir(no)
// 	se n < m então
// 		se busca(no.chave) = 0 então
// 			L[n + 1] := no
// 			n := n + 1
// 			insere := n
// 		senão insere := 0
// 	senão insere := -1

/**
* implementacao - inserir (versão 1)
**/

// int inserir (no L[], int n, int m, no d){
//     if(n < m){
//         if(busca(L, n, d.chave) == -1){
//             L[n+1].chave = d.chave;
//             L[n+1].valor = d.valor;
//             n = n+1;
//             return n;
//         }else{
//             return 0;
//         }
//     }else{
//         return -1;
//     }
// }

/**
* implementacao - inserir (versão 2)
**/

int inserir (no L[], int n, int m, no d){
    if(n < m){
        if(buscar(L, n, d.chave) == -1){
            L[n].chave = d.chave;
            L[n].valor = d.valor;
            return n + 1;
        }
        return 0;
    }
    return -1;
}

/**
* pseudocódigo - remover
**/

// função remover(x)
// 	remove := nulo
// 	se n ≠ 0 então
// 		indice := busca(x)
// 		se indice ≠ 0 então
// 			remove := L[indice] 
// 			para i := indice, n – 1 faça
// 				L[i] := L[i + 1]
// 			n := n - 1	

/**
* implementacao - remover
**/

no* remover(int x, no L[], int *n){
    no * retorno = NULL;
    if(n != 0){
        int indice = buscar(L, *n, x);
        if(indice >= 0){
            retorno = malloc(sizeof(no));
            (*retorno).chave = L[indice].chave;
            (*retorno).valor = L[indice].valor;

            for(int i = indice; i < (*n)-1; i++){
                L[i].chave = L[i+1].chave;
                L[i].valor = L[i+1].valor;
            }
            *n = (*n)-1;
        }    
    }

    return retorno;
}

/**
* implementacao - imprimir
**/

void imprimir(no L[], int n){
    if(!n){
        printf("<lista vazia!>");
    }
    for(int i = 0; i < n; i++){
        printf("%d: %d\n", L[i].chave, L[i].valor);
        printf("=========\n");
    }
}

/**
* funcoes auxiliares, apenas para diminuir a quantidade de codigo na main
**/

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

void ler_no(no * novo_no){
    printf("informe a chave: ");
    scanf("%d", &(*novo_no).chave);
    printf("informe o valor: ");
    scanf("%d", &(*novo_no).valor);
    printf("\n");
}

void main(){
    int m;//tamanho maximo da lista
    int n = 0;//tamanho atual da lista
    int resposta = 1;//resposta do usuario p/ as opcoes

    printf("informe o tamanho desejado p/ a lista: ");
    scanf("%d", &m);
    //estamos declarando o vetor com tamanho m + 1
    //porque a funcao busca utiliza a posicao m + 1
    no L[m + 1];

    while(resposta != 0){
        ler_menu(&resposta);

        if(resposta == 0){
            //sair
            return ;
        } if(resposta == 1){
            //inserir
            no novo_no;
            ler_no(&novo_no);
            int valor_retornado = inserir (L, n, m, novo_no);
            if(valor_retornado == -1){
                printf("lista cheia\n");
            }else if(valor_retornado == 0){
                printf("elemento ja existente\n");
            }else{
                n = valor_retornado;
                printf("elemento inserido\ntamanho da lista: %d\n",n);
            }
        } else if(resposta == 2){
            //remover
            int chave;
            printf("informe a chave a remover: ");
            scanf("%d", &chave);

            no * no_removido = remover(chave, L, &n);
            if(no_removido != NULL){
                printf("conteudo do no removido:\n");
                printf("%d: %d\n",(*no_removido).chave, (*no_removido).valor);
                printf("tamanho da lista: %d\n", n);
                free(no_removido);
            }else{
                printf("elemento inexistente\n");
            }
        }else if(resposta == 3){
            //imprimir
            imprimir(L, n);
        }else {
            printf("Opcao invalida\n");
        }
    }
}
