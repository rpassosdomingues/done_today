#include <stdio.h>
#include <stdlib.h>

typedef struct _share_node {
    int key;
    struct _share_node *left;
    struct _share_node *right;
} share_node;

typedef struct {
    share_node *root;
} share_tree;

share_node *createShareNode(int key) {
    share_node *newNode = (share_node *)malloc(sizeof(share_node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

share_tree *createShareTree() {
    share_tree *newTree = (share_tree *)malloc(sizeof(share_tree));
    newTree->root = NULL;
    return newTree;
}

void shareInsert(share_tree *tree, int key) {
    if (tree->root == NULL) {
        tree->root = createShareNode(key);
        return;
    }

    share_node *current = tree->root;
    share_node *parent = NULL;

    while (current != NULL) {
        parent = current;

        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (key < parent->key) {
        parent->left = createShareNode(key);
    } else {
        parent->right = createShareNode(key);
    }
}

void inOrderShareTraversal(share_node *x) {
    if (x != NULL) {
        inOrderShareTraversal(x->left);
        printf("%d ", x->key);
        inOrderShareTraversal(x->right);
    }
}

void printShareTree(share_tree *tree) {
    printf("Share Tree (In-Order): ");
    inOrderShareTraversal(tree->root);
    printf("\n");
}

int main() {
    share_tree *shareTree = createShareTree();

    int option, key;

    do {
        printf("================================\n");
        printf("Menu:\n");
        printf("--------------------------------\n");
        printf("0 - Exit\n");
        printf("1 - Insert\n");
        printf("2 - Print In-Order\n");
        printf("================================\n");

        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 0:
                // Free memory and exit
                // Implement freeing of share tree nodes here
                free(shareTree);
                return 0;
            case 1:
                // Insert into Share Tree
                printf("Enter key to insert into Share Tree: ");
                scanf("%d", &key);
                shareInsert(shareTree, key);
                printf("Key %d inserted into Share Tree.\n", key);
                break;
            case 2:
                // Print Share Tree (In-Order)
                printShareTree(shareTree);
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 0);

    return 0;
}
