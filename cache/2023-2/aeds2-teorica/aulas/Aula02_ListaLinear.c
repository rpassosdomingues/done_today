#include<stdio.h>
#include<stdlib.h>

/**
* Códigos referentes aos slides da aula: Aula02_ListaLinear
**/

typedef struct dados_
{
    int chave;
    int valor;
} dados;


/**
* pseudocódigo - busca (versão 1)
**/

//função busca1(x)
//	i := 1;   busca1 := 0
//	enquanto i <= n faça
//		se L[i].chave = x então
//			busca1 := i
//			i := n + 1
//		senão i := i + 1


/**
* implementacao - busca (versão 1)
**/

// int busca1(dados L[], int n, int x){
//     int i = 0;
//     int retorno = -1;
//     while(i < n){
//         if(L[i].chave == x){
//             retorno = i;
//             i = n;
//         }else{
//             i = i + 1;
//         }
//     }
//     return retorno;
// }

/**
* implementacao usando return "direto" - busca (versão 1)
**/

int busca1(dados L[], int n, int x){
    int i = 0;
    while(i < n){
        if(L[i].chave == x){
            return i;
        }else{
            i = i + 1;
        }
    }
    return -1;
}

/**
* pseudocódigo - busca (versão 2)
**/

//função busca(x)
//	L[n+1].chave := x; i := 1;
//	enquanto L[i].chave ≠ x faça
//			i := i + 1		
//	se i ≠ n + 1 então
//			busca := i
//	senão busca := 0

/**
* implementacao - busca (versão 2)
**/

int busca (dados L[], int n, int x){
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
* pseudocódigo - busca ordenada
**/

// função busca-ord(x)
// 	L[n+1].chave := x; i := 1;
// 	enquanto L[i].chave < x faça
// 			i := i + 1		
// 	se i = n + 1 ou L[i].chave ≠ x então
// 			busca-ord := 0
// 	senão busca-ord := i

/**
* implementacao - busca ordenada
**/

int busca_ord (dados L[], int n, int x){
    L[n].chave = x;
    int i = 0;
    while(L[i].chave < x){
        i = i+1;//i++
    }
    if(i == n || L[i].chave != x){
        return -1;
    }
    return i;
}

/**
* pseudocódigo - busca binária
**/

// função busca-bin(x)
// 	inf := 1; sup := n; busca-bin := 0;
// 	enquanto inf <= sup faça
// 		meio := ⌊(inf + sup)/2⌋
// 		se L[meio].chave = x então
// 			busca-bin := meio
// 			inf := sup + 1
// 		senão se L[meio].chave < x
// 				inf := meio + 1
// 			senão sup := meio - 1

/**
* implementacao - busca binária
**/

int busca_bin(dados L[], int n, int x){
    int inf = 0, sup = n-1;
    while(inf <= sup){
        int meio = (inf + sup)/2;
        if(L[meio].chave == x){
            return meio;
        }else{
            if(L[meio].chave < x){
                inf = meio + 1;
            }else{
                sup = meio - 1;
            }
        }
    }
    return -1;
}    

void main(){
    dados L[4];
    L[0].chave = 10;
    L[1].chave = 20;
    L[2].chave = 30;
    L[3].chave = 40;
    L[4].chave = 50;
    L[5].chave = 60;


    //int retorno = busca1(L, 3, 5);
    int retorno = busca_bin(L, 6, 55);
    if(retorno == -1){
        printf("Valor nao encontrado.\n");
    }else{
        printf("Valor encontrado no indice %d.\n", retorno);
    }
}
