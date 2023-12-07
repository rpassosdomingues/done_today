#include <stdio.h>
#include <stdlib.h>

typedef struct _rb_node {
    int key;
    char color; // 'R' for red, 'B' for black
    struct _rb_node *parent;
    struct _rb_node *left;
    struct _rb_node *right;
} rb_node;

typedef struct {
    rb_node *root;
    rb_node *nil;
} rb_tree;

rb_node *createNode(rb_tree *tree, int key) {
    rb_node *newNode = (rb_node *)malloc(sizeof(rb_node));
    newNode->key = key;
    newNode->color = 'R';
    newNode->parent = tree->nil;
    newNode->left = tree->nil;
    newNode->right = tree->nil;
    return newNode;
}

rb_tree *createRBTree() {
    rb_tree *newTree = (rb_tree *)malloc(sizeof(rb_tree));
    newTree->nil = createNode(newTree, -1);
    newTree->nil->color = 'B';
    newTree->root = newTree->nil;
    return newTree;
}

void leftRotate(rb_tree *tree, rb_node *x) {
    rb_node *y = x->right;
    x->right = y->left;

    if (y->left != tree->nil) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == tree->nil) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void rightRotate(rb_tree *tree, rb_node *y) {
    rb_node *x = y->left;
    y->left = x->right;

    if (x->right != tree->nil) {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == tree->nil) {
        tree->root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}

void rbInsertFixup(rb_tree *tree, rb_node *z) {
    while (z->parent->color == 'R') {
        if (z->parent == z->parent->parent->left) {
            rb_node *y = z->parent->parent->right;

            if (y->color == 'R') {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(tree, z);
                }

                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                rightRotate(tree, z->parent->parent);
            }
        } else {
            rb_node *y = z->parent->parent->left;

            if (y->color == 'R') {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(tree, z);
                }

                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                leftRotate(tree, z->parent->parent);
            }
        }
    }

    tree->root->color = 'B';
}

void rbInsert(rb_tree *tree, int key) {
    rb_node *z = createNode(tree, key);
    rb_node *y = tree->nil;
    rb_node *x = tree->root;

    while (x != tree->nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;

    if (y == tree->nil) {
        tree->root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    rbInsertFixup(tree, z);
}

void inOrderTraversal(rb_tree *tree, rb_node *x) {
    if (x != tree->nil) {
        inOrderTraversal(tree, x->left);
        printf("%d(%c) ", x->key, x->color);
        inOrderTraversal(tree, x->right);
    }
}

rb_node *treeMinimum(rb_tree *tree, rb_node *x) {
    while (x->left != tree->nil) {
        x = x->left;
    }
    return x;
}

void rbTransplant(rb_tree *tree, rb_node *u, rb_node *v) {
    if (u->parent == tree->nil) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void rbDeleteFixup(rb_tree *tree, rb_node *x) {
    while (x != tree->root && x->color == 'B') {
        if (x == x->parent->left) {
            rb_node *w = x->parent->right;

            if (w->color == 'R') {
                w->color = 'B';
                x->parent->color = 'R';
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == 'B' && w->right->color == 'B') {
                w->color = 'R';
                x = x->parent;
            } else {
                if (w->right->color == 'B') {
                    w->left->color = 'B';
                    w->color = 'R';
                    rightRotate(tree, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = 'B';
                w->right->color = 'B';
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            rb_node *w = x->parent->left;

            if (w->color == 'R') {
                w->color = 'B';
                x->parent->color = 'R';
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == 'B' && w->left->color == 'B') {
                w->color = 'R';
                x = x->parent;
            } else {
                if (w->left->color == 'B') {
                    w->right->color = 'B';
                    w->color = 'R';
                    leftRotate(tree, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = 'B';
                w->left->color = 'B';
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }

    x->color = 'B';
}

void rbDelete(rb_tree *tree, int key) {
    rb_node *z = tree->root;

    while (z != tree->nil) {
        if (key == z->key) {
            break;
        } else if (key < z->key) {
            z = z->left;
        } else {
            z = z->right;
        }
    }

    if (z == tree->nil) {
        printf("Key %d not found in the Red-Black Tree.\n", key);
        return;
    }

    rb_node *y = z;
    rb_node *x;
    char yOriginalColor = y->color;

    if (z->left == tree->nil) {
        x = z->right;
        rbTransplant(tree, z, z->right);
    } else if (z->right == tree->nil) {
        x = z->left;
        rbTransplant(tree, z, z->left);
    } else {
        y = treeMinimum(tree, z->right);
        yOriginalColor = y->color;
        x = y->right;

        if (y->parent == z) {
            x->parent = y;
        } else {
            rbTransplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rbTransplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (yOriginalColor == 'B') {
        rbDeleteFixup(tree, x);
    }
}

void freeRBTreeNodes(rb_tree *tree, rb_node *x) {
    if (x != tree->nil) {
        freeRBTreeNodes(tree, x->left);
        freeRBTreeNodes(tree, x->right);
        free(x);
    }
}

void freeRBTree(rb_tree *tree) {
    freeRBTreeNodes(tree, tree->root);
    free(tree->nil);
    free(tree);
}

void menu() {
    printf("================================\n");
    printf("Menu:\n");
    printf("--------------------------------\n");
    printf("0 - Exit\n");
    printf("1 - Insert\n");
    printf("2 - Remove\n");
    printf("3 - Print In-Order\n");
    printf("================================\n");
}

int main() {
    rb_tree *redBlackTree = createRBTree();

    int option, key;

    do {
        menu();
        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 0:
                // Free memory and exit
                freeRBTree(redBlackTree);
                return 0;
            case 1:
                // Insert into Red-Black Tree
                printf("Enter key to insert into Red-Black Tree: ");
                scanf("%d", &key);
                rbInsert(redBlackTree, key);
                printf("Key %d inserted into Red-Black Tree.\n", key);
                break;
            case 2:
                // Delete from Red-Black Tree
                printf("Enter key to delete from Red-Black Tree: ");
                scanf("%d", &key);
                rbDelete(redBlackTree, key);
                printf("Key %d deleted from Red-Black Tree.\n", key);
                break;
            case 3:
                // Print Red-Black Tree (In-Order)
                printf("Red-Black Tree (In-Order): ");
                inOrderTraversal(redBlackTree, redBlackTree->root);
                printf("\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 0);

}
