#ifndef _H_ARVORES
#define _H_ARVORES

typedef struct AVLNode_ {
    int data;
    int height;
    struct AVLNode_ *left;
    struct AVLNode_ *right;
} AVLNode;

typedef struct BinaryNode_ BinaryNode;

double arvore_binaria(int instancia_num);
double arvore_balanceada(int instancia_num);

#endif // _H_ARVORES