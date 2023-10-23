#ifndef _H_ARVORES
#define _H_ARVORES

/**
 * Estrutura para nós sub-arvores.
*/
typedef struct arvore {
    struct arvore *esquerda;
    int conteudo;
    struct arvore *direita;
} arvore;

double arvore_binaria(int instancia_num);
double arvore_balanceada(int instancia_num);

#endif // _H_ARVORES