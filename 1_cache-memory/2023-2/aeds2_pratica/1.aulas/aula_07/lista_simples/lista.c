#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h" 

struct node {
    int data;
    struct node *next;
}*p,*tmp,*tmp1;

void inserir_meio(int novo_elemento) {
    tmp = p;
    tmp1 = (struct node*) malloc(sizeof(struct node));
    tmp1->data = novo_elemento;
    
    if (p == NULL) {
        // Se a lista estiver vazia, insira o elemento no início
        inserir_inicio(novo_elemento);
        return;
    }

    int tamanho = 0;
    while (tmp != NULL) {
        tamanho++;
        tmp = tmp->next;
    }

    int posicao_meio = tamanho / 2;
    tmp = p;

    for (int i = 0; i < posicao_meio; i++) {
        tmp = tmp->next;
    }

    tmp1->next = tmp->next;
    tmp->next = tmp1;
}

void remover_meio() {
    if (p == NULL) {
        printf("\nLista vazia. Nada para remover.\n");
        return;
    }

    tmp = p;
    tmp1 = p;
    struct node *anterior = NULL;

    while (tmp != NULL && tmp1 != NULL && tmp1->next != NULL) {
        anterior = tmp;
        tmp = tmp->next;
        tmp1 = tmp1->next->next;
    }

    if (anterior == NULL) {
        // O elemento do meio é o primeiro elemento da lista
        p = p->next;
    } else {
        // O elemento do meio está no meio ou no final da lista
        anterior->next = tmp->next;
    }

    free(tmp);
}

int obter_posicao_meio() {
    if (p == NULL) {
        printf("\nLista vazia. Nenhum elemento no meio.\n");
        return -1; // ou algum valor de erro apropriado
    }

    tmp = p;
    tmp1 = p;

    while (tmp != NULL && tmp1 != NULL && tmp1->next != NULL) {
        tmp = tmp->next;
        tmp1 = tmp1->next->next;
    }

    return tmp->data;
}

void inserir_fim(int elemento) {
    tmp = p;
    tmp1 = (struct node*) malloc (sizeof(struct node));
    tmp1->data=elemento;
    tmp1->next=NULL;
    if (p == NULL) {
        p = tmp1;
    } else {
        while (tmp->next!=NULL) {
            tmp = tmp->next;
        }
        tmp->next = tmp1;
    }
}

void inserir_inicio(int elemento) {
	 tmp = p;
	 tmp1 = (struct node*) malloc (sizeof(struct node));
	 tmp1->data=elemento;
	 tmp1->next = p;
	 p=tmp1;
}

void apagar(int ele) {
    tmp = p;
	struct node *pre=tmp;
	while (tmp != NULL) {
		if (tmp->data==ele) {
            if (tmp == p) {
                p = tmp->next;
			    free(tmp);
			    return;
			} else {
                pre->next=tmp->next;
			    free(tmp);
			    return;
			}
		} else {
            pre = tmp;
		    tmp = tmp->next;
		}
	}
	printf("\n Valor não encontrado! ");
 }
 
void apagar_inicio() {	
	tmp = p;
	if (p == NULL) {
		printf("\n Nenhum elemento deletado ");
    } else {
		printf("\nElemento deletado - %d", p->data);
		p = p->next;
	}
 }
 
void apagar_fim() {	
	tmp=p;
	struct node* pre;
	if(p == NULL) {
		printf("\n Nenhum elemento deletado ");
    } else if (p->next == NULL) {
		printf("\nElemento deletado - %d", p->data);
		p = NULL;
	} else {
		while (tmp->next != NULL) {
			pre=tmp;
			tmp=tmp->next;
		}
		pre->next=NULL;
		printf("\nElemento deletado - %d", tmp->data);
	}
}

bool ehVazia() {
    if (p == NULL) {
        return (1);
    } else {
        return (0);
    }
}
void imprimir() {
	tmp = p;
 	while (tmp != NULL) {
        printf("\n %d",tmp->data);
	 	tmp = tmp->next;
	}
}

int obter_primeiro(void) {
    tmp = p;
	if (p == NULL) {
		printf("\n Nenhum elemento encontrado ");
    } else {
		return (p->data);
	}
}

int obter_ultimo(void) {
    tmp = p;
	struct node* pre;
	if (p == NULL) {
		printf("\n Nenhum elemento encontrado ");
        return (0);
    } else if (p->next==NULL) {
		return(p->data);
	} else {
		while (tmp->next!=NULL) {
			pre=tmp;
			tmp=tmp->next;
		}
		pre->next=NULL;
		return(tmp->data);
	}
}

void main() { 
  int val, n;
  p = NULL;
  do {
    printf("\n************************* MENU ************************");
    printf("\n1.Inserir no fim");
    printf("\n2.Inserir no início");
    printf("\n3.Apagar um elemento em particular");
    printf("\n4.Apagar do início");
    printf("\n5.Apagar do fim");
    printf("\n6.Inserir no meio");
    printf("\n7.Apagar do meio");
    printf("\n8.Obter primeiro");
    printf("\n9.Obter último");
	printf("\n10.Obter meio");
    printf("\n0.Sair");
    printf("\nEscolha sua opção : ");
    scanf("%d",&n);
    switch(n) {
        case 1: printf("\nDigite o valor ");
                scanf("%d",&val);
                inserir_fim(val);
                break;
        case 2: printf("\nDigite o valor ");
                scanf("%d",&val);
                inserir_inicio(val);
                break;
        case 3: printf("\nDigite o valor ");
                scanf("%d",&val);
                apagar(val);
                break;
        case 4: 
                apagar_inicio();
                break;
        case 5: 
                apagar_fim();
                break;
        case 6: printf("\nDigite o valor ");
                scanf("%d",&val);
                inserir_meio(val);
                break;
        case 7: 
                remover_meio();
                break;
        case 8: val = obter_primeiro();
                if (val != 0) {
                    printf("%d\n", val); // Adicione a formatação para imprimir um inteiro
                }
                break;
        case 9: val = obter_ultimo();
                if (val != 0) {
                    printf("%d\n", val); // Adicione a formatação para imprimir um inteiro
                }
                break;
		case 10: val = obter_posicao_meio();
    			if (val != -1) {
        			printf("Elemento do meio: %d\n", val);
    			}
    			break;
        case 0: exit(0);
                break;
        default: printf("\n Opção errada!");
                break;
        }
    } while(1);
}