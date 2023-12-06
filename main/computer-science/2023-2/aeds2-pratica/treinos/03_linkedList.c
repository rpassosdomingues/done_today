#include <stdio.h>
#include <stdlib.h>

// Define a struct for a node in the linked list
typedef struct node {
    int data;           // Data stored in the node
    struct node *next;  // Pointer to the next node in the chain
} Node;

// Function to create a new node and return a pointer to it
Node *create_link() {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("\n...Memory allocation error...\n");
    } else {
        printf("\nSuccessfully allocated memory!\n");
        newNode->next = NULL;
    }
    return newNode;
}

// Function to display the menu
void display_menu() {
    printf("\nMenu:\n");
    printf("0. Quit\n");
    printf("1. Insert at the beginning\n");
    printf("2. Remove from the beginning\n");
    printf("3. Insert in the middle\n");
    printf("4. Remove from the middle\n");
    printf("5. Insert at the end\n");
    printf("6. Remove from the end\n");
    printf("7. Print the chain\n");
    printf("Enter your choice: ");
}

// Function to insert a new element at the beginning of the chain
void insert_start(Node **chain, int number) {
    Node *newElement = create_link();
    if (newElement != NULL) {
        newElement->data = number;
        newElement->next = *chain;
        *chain = newElement;
    }
}

// Function to remove the first element from the chain
void remove_start(Node **chain) {
    if (*chain != NULL) {
        Node *temp = *chain;
        *chain = (*chain)->next;
        free(temp);
    }
}

// Function to insert a new element in the middle of the chain
void insert_middle(Node **chain, int data, int position) {
    if (position < 0) {
        printf("Invalid position.\n");
        return;
    }

    Node *newElement = create_link();
    if (newElement != NULL) {
        newElement->data = data;
        if (position == 0) {
            newElement->next = *chain;
            *chain = newElement;
        } else {
            Node *current = *chain;
            int current_position = 0;
            while (current != NULL && current_position < position - 1) {
                current = current->next;
                current_position++;
            }
            if (current == NULL) {
                printf("Invalid position.\n");
                free(newElement);
                return;
            }
            newElement->next = current->next;
            current->next = newElement;
        }
    }
}

// Function to remove an element from the middle of the chain
void remove_middle(Node **chain, int position) {
    if (position < 0 || *chain == NULL) {
        printf("Invalid position.\n");
        return;
    }

    if (position == 0) {
        remove_start(chain);
        return;
    }

    Node *current = *chain;
    int current_position = 0;
    while (current != NULL && current_position < position - 1) {
        current = current->next;
        current_position++;
    }

    if (current == NULL || current->next == NULL) {
        printf("Invalid position.\n");
        return;
    }

    Node *temp = current->next;
    current->next = temp->next;
    free(temp);
}

// Function to insert a new element at the end of the chain
void insert_end(Node **chain, int data) {
    Node *newElement = create_link();
    if (newElement != NULL) {
        newElement->data = data;
        newElement->next = NULL;
        if (*chain == NULL) {
            *chain = newElement;
        } else {
            Node *current = *chain;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newElement;
        }
    }
}

// Function to remove the last element from the chain
void remove_end(Node **chain) {
    if (*chain == NULL) {
        return;
    }

    if ((*chain)->next == NULL) {
        free(*chain);
        *chain = NULL;
        return;
    }

    Node *current = *chain;
    while (current->next->next != NULL) {
        current = current->next;
    }

    free(current->next);
    current->next = NULL;
}

// Function to print the elements in the chain
void print_chain(Node *chain) {
    printf("Chain elements: ");
    while (chain != NULL) {
        printf("%d ", chain->data);
        chain = chain->next;
    }
    printf("\n");
}

// Function to free the memory used by the chain
void free_chain(Node *chain) {
    while (chain != NULL) {
        Node *temp = chain;
        chain = chain->next;
        free(temp);
    }
}

int main() {
    Node *chain = NULL;
    int choice, data, position;

    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                // Free the memory used by the chain and exit
                free_chain(chain);
                return 0;
            case 1:
                printf("Enter data to insert at the beginning: ");
                scanf("%d", &data);
                insert_start(&chain, data);
                break;
            case 2:
                remove_start(&chain);
                break;
            case 3:
                printf("Enter data to insert in the middle: ");
                scanf("%d", &data);
                printf("Enter position to insert: ");
                scanf("%d", &position);
                insert_middle(&chain, data, position);
                break;
            case 4:
                printf("Enter position to remove from the middle: ");
                scanf("%d", &position);
                remove_middle(&chain, position);
                break;
            case 5:
                printf("Enter data to insert at the end: ");
                scanf("%d", &data);
                insert_end(&chain, data);
                break;
            case 6:
                remove_end(&chain);
                break;
            case 7:
                print_chain(chain);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
