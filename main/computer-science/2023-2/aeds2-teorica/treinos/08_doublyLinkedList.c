#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node in the doubly linked list
typedef struct node {
    int data;           // Data stored in the node
    struct node *next, *prev;  // Pointer to the next and previous node in the chain
} Node;

// Function to create a new node and return a pointer to it
Node *create_node(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("\nMemory allocation error for the node.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert a new element at the beginning of the list, checking for duplicates
void insert(Node **head, int data) {
    // Check if the element already exists in the list
    if (search(*head, data) != NULL) {
        printf("%d is already in the list. It was not inserted again.\n", data);
        return;
    }

    Node *newNode = create_node(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    }
}

// Function to remove the first element from the list
void remove_head(Node **head) {
    if (*head != NULL) {
        Node *temp = *head;
        *head = (*head)->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        free(temp);
    }
}

// Function to search for an element in the list
Node *search(Node *head, int value) {
    Node *current = head;
    while (current != NULL) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to print the elements in the list
void print_list(Node *head) {
    printf("List elements: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Function to free the memory used by the list
void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node *head = NULL;
    int choice, data, searchValue;
    Node *searchResult;

    while (1) {
        printf("---------------------------\n");
        printf("\t Menu \n");
        printf("---------------------------\n");
        printf("0. Quit\n");
        printf("...........................\n");
        printf("1. Insert\n");
        printf("2. Remove\n");
        printf("3. Search\n");
        printf("4. Print\n");
        printf("---------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                // Free the memory used by the list and exit
                free_list(head);
                return 0;
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insert(&head, data);
                break;
            case 2:
                remove_head(&head);
                break;
            case 3:
                printf("Enter value to search for: ");
                scanf("%d", &searchValue);
                searchResult = search(head, searchValue);
                if (searchResult != NULL) {
                    printf("Found %d in the list.\n", searchValue);
                } else {
                    printf("%d not found in the list.\n", searchValue);
                }
                break;
            case 4:
                print_list(head);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
