#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

struct stack {
    int top;
    int size;
    int *items;
};

struct stack *create_stack(int size) {
    struct stack *stack = (struct stack *)malloc(sizeof(struct stack));
    stack->size = size;
    stack->top = -1;
    stack->items = (int *)malloc(stack->size * sizeof(int));
    return stack;
}

bool is_full(struct stack *stack) {
    return stack->top == stack->size - 1;
}

bool is_empty(struct stack *stack) {
    return stack->top == -1;
}

void push(struct stack *stack, int item) {
    if (is_full(stack)) {
        printf("\nStack is full. Cannot insert elements.");
        return;
    }
    stack->top++;
    stack->items[stack->top] = item;
}

int pop(struct stack *stack) {
    if (is_empty(stack)) {
        printf("\nStack is empty. Cannot remove elements.");
        return -1;
    }
    return stack->items[stack->top--];
}

int get_top(struct stack *stack) {
    if (is_empty(stack)) {
        printf("\nStack is empty. Cannot get elements.");
        return INT_MIN;
    }
    return stack->items[stack->top];
}

int main() {
    int val, choice;
    bool aux;
    // Create a stack with size 5
    struct stack *stack = create_stack(5);
    do {
        printf("\n************************* MENU ************************");
        printf("\n1. Push");
        printf("\n2. Pop");
        printf("\n3. Get Top Element");
        printf("\n4. Is Stack Empty?");
        printf("\n5. Is Stack Full?");
        printf("\n6. Exit");
        printf("\n Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("\nEnter the value: ");
                scanf("%d", &val);
                push(stack, val);
                break;
            case 2:
                printf("\nRemoved Element: %d", pop(stack));
                break;
            case 3:
                printf("\nTop Element: %d", get_top(stack));
                break;
            case 4:
                aux = is_empty(stack);
                if (aux) {
                    printf("\nStack is empty");
                } else {
                    printf("\nStack is not empty");
                }
                break;
            case 5:
                aux = is_full(stack);
                if (aux) {
                    printf("\nStack is full");
                } else {
                    printf("\nStack is not full");
                }
                break;
            case 6:
                free(stack->items);
                free(stack);
                return 0;
            default:
                printf("\nWrong option!");
                break;
        }
    } while (1);

    return 0;
}
