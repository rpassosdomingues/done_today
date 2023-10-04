#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

// Function to create a new tree node
Node* newNode(int item) {
    Node* temp = malloc(sizeof(Node));
    temp->value = item;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a new node with a given value into the binary tree
Node* insertNode(Node* node, int value) {
    if (node == NULL) {
        return newNode(value);
    }

    if (value < node->value) {
        node->left = insertNode(node->left, value);
    } else if (value > node->value) {
        node->right = insertNode(node->right, value);
    }

    return node;
}

// Function to find the minimum value node in a binary tree
Node* findMin(Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Function to remove a node with a given value from the binary tree
Node* removeNode(Node* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->value) {
        root->left = removeNode(root->left, value);
    } else if (value > root->value) {
        root->right = removeNode(root->right, value);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children, get the inorder successor (smallest in the right subtree)
        Node* temp = findMin(root->right);

        // Copy the inorder successor's content to this node
        root->value = temp->value;

        // Delete the inorder successor
        root->right = removeNode(root->right, temp->value);
    }
    return root;
}

// Function to print the binary tree in order
void printInOrder(Node* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%d ", root->value);
        printInOrder(root->right);
    }
}

// Function to print the binary tree pre order
void printPreOrder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->value);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

// Function to print the binary tree pos order
void printPosOrder(Node* root) {
    if (root != NULL) {
        printPosOrder(root->left);
        printPosOrder(root->right);
        printf("%d ", root->value);
    }
}

// Function to deallocate the binary tree
void deallocateTree(Node* root) {
    if (root != NULL) {
        deallocateTree(root->left);
        deallocateTree(root->right);
        free(root);
    }
}

// Function to display the menu
void displayMenu() {
    printf("================================\n");
    printf("Menu:\n");
    printf("--------------------------------\n");
    printf("0 - Quit\n");
    printf("1 - Insert a value\n");
    printf("2 - Remove a value\n");
    printf("3 - Print In Order\n");
    printf("4 - Print Pre Order\n");
    printf("5 - Print Pos Order\n");
    printf("================================\n");
}

int main() {
    Node* root = NULL;
    int choice, value;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                // Deallocate the tree before exiting
                deallocateTree(root);
                break;
            case 1:
                // Insert a value
                // Order of the insertion: 8 3 1 6 4 7 10 14 13
                printf("\tEnter a value to insert: ");
                scanf(" %d", &value);
                root = insertNode(root, value);
                break;
            case 2:
                // Remove a value
                printf("\tEnter a value to remove: ");
                scanf(" %d", &value);
                root = removeNode(root, value);
                break;
            case 3:
                // Print In Order
                printf("\nIn Order: ");
                printInOrder(root);
                printf("\n");
                break;
            case 4:
                // Print Pre Order
                printf("\nPre Order: ");
                printPreOrder(root);
                printf("\n");
                break;
            case 5:
                // Print Pos Order
                printf("\nPos Order: ");
                printPosOrder(root);
                printf("\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
