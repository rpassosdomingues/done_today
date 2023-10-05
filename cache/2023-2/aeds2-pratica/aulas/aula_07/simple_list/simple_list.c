#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "simple_list.h"

// Define a structure for a linked list node
struct node {
    int data;
    struct node *next;
} *p, *tmp, *tmp1;

// Function to insert an element in the middle of the list
void insert_middle(int new_element) {
    tmp = p;
    tmp1 = (struct node*) malloc(sizeof(struct node));
    tmp1->data = new_element;

    if (p == NULL) {
        // If the list is empty, insert the element at the beginning
        insert_beginning(new_element);
        return;
    }

    int size = 0;
    while (tmp != NULL) {
        size++;
        tmp = tmp->next;
    }

    int middle_position = size / 2;
    tmp = p;

    for (int i = 0; i < middle_position; i++) {
        tmp = tmp->next;
    }

    tmp1->next = tmp->next;
    tmp->next = tmp1;
}

// Function to remove the middle element from the list
void remove_middle() {
    if (p == NULL) {
        printf("\nEmpty list. Nothing to remove.\n");
        return;
    }

    tmp = p;
    tmp1 = p;
    struct node *previous = NULL;

    while (tmp != NULL && tmp1 != NULL && tmp1->next != NULL) {
        previous = tmp;
        tmp = tmp->next;
        tmp1 = tmp1->next->next;
    }

    if (previous == NULL) {
        // The middle element is the first element in the list
        p = p->next;
    } else {
        // The middle element is in the middle or at the end of the list
        previous->next = tmp->next;
    }

    free(tmp);
}

// Function to get the data of the middle element
int get_middle_position() {
    if (p == NULL) {
        printf("\nEmpty list. No element in the middle.\n");
        return -1; // or some appropriate error value
    }

    tmp = p;
    tmp1 = p;

    while (tmp != NULL && tmp1 != NULL && tmp1->next != NULL) {
        tmp = tmp->next;
        tmp1 = tmp1->next->next;
    }

    return tmp->data;
}

// Function to insert an element at the end of the list
void insert_end(int element) {
    tmp = p;
    tmp1 = (struct node*) malloc (sizeof(struct node));
    tmp1->data = element;
    tmp1->next = NULL;
    if (p == NULL) {
        p = tmp1;
    } else {
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = tmp1;
    }
}

// Function to insert an element at the beginning of the list
void insert_beginning(int element) {
    tmp = p;
    tmp1 = (struct node*) malloc (sizeof(struct node));
    tmp1->data = element;
    tmp1->next = p;
    p = tmp1;
}

// Function to remove a specific element from the list
void remove_element(int ele) {
    tmp = p;
    struct node *previous = tmp;
    while (tmp != NULL) {
        if (tmp->data == ele) {
            if (tmp == p) {
                p = tmp->next;
                free(tmp);
                return;
            } else {
                previous->next = tmp->next;
                free(tmp);
                return;
            }
        } else {
            previous = tmp;
            tmp = tmp->next;
        }
    }
    printf("\n Value not found! ");
}

// Function to remove the first element from the list
void remove_beginning() {
    tmp = p;
    if (p == NULL) {
        printf("\n No element deleted ");
    } else {
        printf("\nElement deleted - %d", p->data);
        p = p->next;
    }
}

// Function to remove the last element from the list
void remove_end() {
    tmp = p;
    struct node* previous;
    if (p == NULL) {
        printf("\n No element deleted ");
    } else if (p->next == NULL) {
        printf("\nElement deleted - %d", p->data);
        p = NULL;
    } else {
        while (tmp->next != NULL) {
            previous = tmp;
            tmp = tmp->next;
        }
        previous->next = NULL;
        printf("\nElement deleted - %d", tmp->data);
    }
}

// Function to check if the list is empty
bool isEmpty() {
    if (p == NULL) {
        return true;
    } else {
        return false;
    }
}

// Function to print the elements of the list
void print() {
    tmp = p;
    while (tmp != NULL) {
        printf("\n %d", tmp->data);
        tmp = tmp->next;
    }
}

// Function to get the data of the first element
int get_first(void) {
    tmp = p;
    if (p == NULL) {
        printf("\n No element found ");
    } else {
        return p->data;
    }
    return 0; // or some appropriate error value
}

// Function to get the data of the last element
int get_last(void) {
    tmp = p;
    struct node* previous;
    if (p == NULL) {
        printf("\n No element found ");
        return 0; // or some appropriate error value
    } else if (p->next == NULL) {
        return p->data;
    } else {
        while (tmp->next != NULL) {
            previous = tmp;
            tmp = tmp->next;
        }
        previous->next = NULL;
        return tmp->data;
    }
}

// Main function to interact with the user
void main() {
    int val, choice;
    p = NULL;
    do {
        printf("\n************************* MENU ************************");
        printf("\n1. Insert at the end");
        printf("\n2. Insert at the beginning");
        printf("\n3. Remove a specific element");
        printf("\n4. Remove from the beginning");
        printf("\n5. Remove from the end");
        printf("\n6. Insert in the middle");
        printf("\n7. Remove from the middle");
        printf("\n8. Get the first element");
        printf("\n9. Get the last element");
        printf("\n10. Get the middle element");
        printf("\n0. Exit");
        printf("\nChoose your option: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("\nEnter the value: ");
                scanf("%d", &val);
                insert_end(val);
                break;
            case 2:
                printf("\nEnter the value: ");
                scanf("%d", &val);
                insert_beginning(val);
                break;
            case 3:
                printf("\nEnter the value: ");
                scanf("%d", &val);
                remove_element(val);
                break;
            case 4:
                remove_beginning();
                break;
            case 5:
                remove_end();
                break;
            case 6:
                printf("\nEnter the value: ");
                scanf("%d", &val);
                insert_middle(val);
                break;
            case 7:
                remove_middle();
                break;
            case 8:
                val = get_first();
                if (val != 0) {
                    printf("%d\n", val);
                }
                break;
            case 9:
                val = get_last();
                if (val != 0) {
                    printf("%d\n", val);
                }
                break;
            case 10:
                val = get_middle_position();
                if (val != -1) {
                    printf("Middle element: %d\n", val);
                }
                break;
            case 0:
                exit(0);
                break;
            default:
                printf("\n Wrong option!");
                break;
        }
    } while(1);
}
