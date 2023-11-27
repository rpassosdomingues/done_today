#include <stdio.h>
#include <stdlib.h>

typedef struct noArvore_
{
    int valor;
    struct noArvore_ *esq;
    struct noArvore_ *dir;
} noArvore;

noArvore *busca(noArvore *raiz, int k)
{
    if (raiz == NULL || raiz->valor == k)
    {
        return raiz;
    }
    if (k > raiz->valor)
    {
        return busca(raiz->dir, k);
    }
    else
    {
        return busca(raiz->esq, k);
    }
}

noArvore *buscaPai(noArvore *raiz, noArvore *n)
{
    if (raiz == NULL || raiz == n)
    {
        return NULL;
    }

    if (raiz->esq == n || raiz->dir == n)
    {
        return raiz;
    }
    if (n->valor > raiz->valor)
    {
        return buscaPai(raiz->dir, n);
    }
    else
    {
        return buscaPai(raiz->esq, n);
    }
}

noArvore *insere(noArvore *raiz, noArvore *n)
{
    if (raiz == NULL)
    {
        return n;
    }
    if (n->valor > raiz->valor)
    {
        raiz->dir = insere(raiz->dir, n);
    }
    else
    {
        raiz->esq = insere(raiz->esq, n);
    }

    return raiz;
}

noArvore *removeRaiz(noArvore *raiz)
{
    noArvore *p, *q;

    if (raiz->esq == NULL)
    {
        q = raiz->dir;
        free(raiz);
        return (q);
    }

    p = raiz;
    q = raiz->esq;

    while (q->dir != NULL)
    {
        p = q;
        q = q->dir;
    }
    // repare que q é o nó anterior a r
    // na ordem e-r-d
    // enquanto que p é o pai de q
    if (p != raiz)
    {
        p->dir = q->esq;
        q->esq = raiz->esq;
    }
    q->dir = raiz->dir;
    free(raiz);
    return q;
}

noArvore *removeNo(noArvore *raiz, int valor)
{
    noArvore *n = busca(raiz, valor);

    if (n != NULL)
    {
        noArvore *pai = buscaPai(raiz, n);
        if (pai != NULL)
        {
            if (pai->dir == n)
            {
                pai->dir = removeRaiz(n);
            }
            else
            {
                pai->esq = removeRaiz(n);
            }
        }
        else
        {
            raiz = removeRaiz(n);
        }
    }
    return raiz;
}

void imprimePreOrdem(noArvore *raiz)
{
    if (raiz != NULL)
    {
        printf("%d ", raiz->valor);
        if (raiz->esq != NULL)
        {
            imprimePreOrdem(raiz->esq);
        }
        if (raiz->dir != NULL)
        {
            imprimePreOrdem(raiz->dir);
        }
    }
}

void imprimeEmOrdem(noArvore *raiz)
{
    if (raiz != NULL)
    {
        if (raiz->esq != NULL)
        {
            imprimeEmOrdem(raiz->esq);
        }
        printf("%d ", raiz->valor);
        if (raiz->dir != NULL)
        {
            imprimeEmOrdem(raiz->dir);
        }
    }
}

void imprimePosOrdem(noArvore *raiz)
{
    if (raiz != NULL)
    {
        if (raiz->esq != NULL)
        {
            imprimePosOrdem(raiz->esq);
        }
        if (raiz->dir != NULL)
        {
            imprimePosOrdem(raiz->dir);
        }
        printf("%d ", raiz->valor);
    }
}

noArvore *alocaNo(int valor)
{
    noArvore *novo_no = (noArvore *)malloc(sizeof(noArvore));
    novo_no->valor = valor;
    novo_no->esq = NULL;
    novo_no->dir = NULL;
    return novo_no;
}

void desalocaArvore(noArvore *raiz)
{
    if (raiz != NULL)
    {
        if (raiz->esq != NULL)
        {
            desalocaArvore(raiz->esq);
        }
        if (raiz->dir != NULL)
        {
            desalocaArvore(raiz->dir);
        }
        free(raiz);
    }
}

void le_opcao(int *resposta)
{
    printf("\n-----------------------\n");
    printf("Escolha uma das opções:\n");
    printf("0 - sair\n");
    printf("1 - inserir\n");
    printf("2 - remover\n");
    printf("3 - imprimir\n");
    scanf("%d", resposta);
    printf("-----------------------\n");
}

int main()
{
    noArvore *raiz;

    int resposta = 1;

    while (resposta != 0)
    {
        le_opcao(&resposta);
        if (resposta == 0)
        {
            desalocaArvore(raiz);
        }
        else if (resposta == 1)
        {
            printf("Valor a ser inserido: ");
            int valor;
            scanf("%d", &valor);
            // busca antes para evitar inserir valor já existente
            if (busca(raiz, valor) == NULL)
            {
                noArvore *novo_no = alocaNo(valor);
                raiz = insere(raiz, novo_no);
            }
        }

        else if (resposta == 2)
        {
            int valor;
            printf("Valor a ser removido: ");
            scanf("%d", &valor);
            raiz = removeNo(raiz, valor);
        }
        else if (resposta == 3)
        {
            int ordem;
            printf("\t1 - pré-ordem\n\t2 - em ordem\n\t3 - pos-ordem\n");
            scanf(" %d", &ordem);
            printf("\n-----------------------\n");
            if (ordem == 1)
            {
                imprimePreOrdem(raiz);
            }
            else if (ordem == 2)
            {
                imprimeEmOrdem(raiz);
            }
            else if (ordem == 3)
            {
                imprimePosOrdem(raiz);
            }
            else
            {
                printf("Opção inválida.\n");
            }
        }
        else
        {
            printf("Opção inválida.\n");
        }
    }

    return 0;
}
