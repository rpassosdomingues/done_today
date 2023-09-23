#include <stdio.h>
#include <stdbool.h>
#define MAX_HEIGHT 5

// Define the stack structure using an array for data storage and a top index.
typedef struct {
    int data[MAX_HEIGHT]; // Array to store stack elements
    int top;              // Index to track the top of the stack
} Stack;

// Function to initialize the stack, setting the top index to -1 (empty stack).
void initialize(Stack *stack) {
    stack->top = -1;
}

// Function to check if the stack is full based on the top index.
bool isFull(Stack *stack) {
    return stack->top == MAX_HEIGHT - 1;
}

// Function to check if the stack is empty based on the top index.
bool isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack.
void push(Stack *stack, int data) {
    if (isFull(stack)) {
        printf("\nThe stack is full. Cannot push more elements.\n");
    } else {
        stack->top++;                // Increment the top index.
        stack->data[stack->top] = data; // Place the new element at the top.
        printf("\nElement %d pushed successfully.\n", data);
    }
}

// Function to pop (remove) an element from the stack.
void pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("\nThe stack is empty. Cannot pop.\n");
    } else {
        int popped = stack->data[stack->top]; // Get the element to be popped.
        stack->top--;                          // Decrement the top index.
        printf("\nElement %d popped.\n", popped);
    }
}

// Function to print the elements of the stack.
void printStack(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
    } else {
        printf("Stack: ");
        for (int i = 0; i <= stack->top; i++) {
            printf("%d ", stack->data[i]); // Print each element in the stack.
        }
        printf("\n");
    }
}

int main() {
    Stack stack;
    initialize(&stack); // Initialize the stack with an empty state.

    push(&stack, 10);   // Push elements onto the stack.
    push(&stack, 20);
    push(&stack, 30);

    printStack(&stack); // Print the current stack contents.

    pop(&stack);        // Pop elements from the stack.
    pop(&stack);

    printStack(&stack); // Print the updated stack contents.

    return 0;
}
