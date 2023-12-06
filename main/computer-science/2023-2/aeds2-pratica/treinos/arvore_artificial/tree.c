#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

// Function to print the binary tree in order
void printInOrder(Node* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%d ", root->value);
        printInOrder(root->right);
    }
}

// Function to build a random unbalanced tree with 'n' nodes
Node* seed(int n) {
    Node* root = NULL;
    for (int i = 0; i < n; i++) {
        int randomValue = rand() % 51; // Generates a random value between 0 and 50
        root = insertNode(root, randomValue);
    }
    return root;
}

// Function to balance the tree using trim
Node* trim(int arr[], int start, int end) {
    if (start > end) {
        return NULL;
    }
    int mid = (start + end) / 2;
    Node* root = newNode(arr[mid]);
    root->left = trim(arr, start, mid - 1);
    root->right = trim(arr, mid + 1, end);
    return root;
}

// Function to create a balanced tree from an unbalanced tree
Node* balanceTree(Node* root, int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    storeInOrder(root, arr, 0);
    return trim(arr, 0, n - 1);
}

int main() {
    srand(time(NULL)); // Seed for random number generation
    Node* unbalancedTree = seed(10); // Construct an unbalanced tree with 10 nodes
    printf("Unbalanced Tree in Order: ");
    printInOrder(unbalancedTree);
    printf("\n");

    // Convert the unbalanced tree into a balanced tree
    int n = 10; // Number of nodes in the unbalanced tree
    Node* balancedTree = balanceTree(unbalancedTree, n);
    printf("Balanced Tree in Order: ");
    printInOrder(balancedTree);
    printf("\n");

    return 0;
}
