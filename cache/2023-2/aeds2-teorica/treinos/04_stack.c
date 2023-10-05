#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
    int top;
    int height;
    int *items;
} Stack;

Stack* createStack(int height) {
    Stack *newStack = malloc(sizeof(Stack));
    if (newStack == NULL) {
        printf("\n! Memory allocation error !\n");
        return NULL;
    } else {
        newStack->height = height;
        newStack->top = -1;
        newStack->items = (int *)malloc(sizeof(int) * height);
        if (newStack->items == NULL) {
            printf("\n! Memory allocation error for stack items !\n");
            free(newStack);
            return NULL;
        }
        printf("\n Memory allocated successfully!\n");
        return newStack;
    }
}

int isFull(Stack *stack) {
    return stack->top == stack->height - 1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("\n Stack is full. Cannot push.\n");
    } else {
        stack->items[++stack->top] = value;
        printf("\n Pushed %d onto the stack.\n", value);
    }
}

void pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("\n Stack is empty. Cannot pop.\n");
    } else {
        int popped = stack->items[stack->top--];
        printf("\n Popped %d from the stack.\n", popped);
    }
}

void showStack(Stack *stack) {
    if (isEmpty(stack)) {
        printf("\n Stack is empty.\n");
    } else {
        printf("\n Stack contents (top to bottom):\n");
        for (int i = stack->top; i >= 0; i--) {
            printf("%d\n", stack->items[i]);
        }
        printf("\n");
    }
}

void showMenu(int *choice) {
    printf("---------------------------\n");
    printf("\t Menu \n");
    printf("---------------------------\n");
    printf("0. Quit\n");
    printf("...........................\n");
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Show Stack\n");
    printf("---------------------------\n");
    printf("Enter your choice (0-3): ");
    scanf("%d", choice);
    while (*choice < 0 || *choice > 3) {
        printf("Invalid input, try again: ");
        scanf("%d", choice);
    }
}

int main() {
    Stack *stack = NULL;
    int height;

    printf("Enter the max height of the stack: ");
    scanf("%d", &height);

    stack = createStack(height);
    if (stack == NULL) {
        return 1; // Error in creating the stack
    }

    int choice;
    do {
        showMenu(&choice);
        switch (choice) {
            case 0:
                break;
            case 1:
                int value;
                printf("\tEnter the value to push: ");
                scanf("%d", &value);
                push(stack, value);
                break;
            case 2:
                pop(stack);
                break;
            case 3:
                showStack(stack);
                break;
            default:
        }
    } while (choice != 0);

    free(stack->items);
    free(stack);
    return 0;
}
