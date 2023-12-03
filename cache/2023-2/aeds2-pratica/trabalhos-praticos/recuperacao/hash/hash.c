/**
 * ===============================
 * Hash Table
 * -------------------------------
 * Author. Rafael Passos Domingues
 *     RA. 2023.1.08.036
 * ===============================
 */


#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include "hash.h"

int M; // Hash table size

// Function to create a hash table with the specified size
Hash* create_hash(int size, int collision_resolution_strategy) {
    M = size;
    Hash* hash = (Hash*) malloc(sizeof(Hash));
    // Initialize players based on collision resolution strategy (linked list or AVL tree)
    if (collision_resolution_strategy == 1) {
        hash->players = (ListNode**) malloc(size * sizeof(ListNode*));
        for (int i = 0; i < size; i++) {
            ((ListNode**)(hash->players))[i] = NULL; // Initialize all linked lists to NULL
        }
    } else if (collision_resolution_strategy == 2) {
        hash->players = (AVLNode**) malloc(size * sizeof(AVLNode*));
        for (int i = 0; i < size; i++) {
            ((AVLNode**)(hash->players))[i] = NULL; // Initialize all AVL trees to NULL
        }
    } else {
        // Handle other collision resolution strategies if needed
    }
    return hash;
}

// Function to handle collisions using linked lists
void hash_LinkedList(Hash* hash, Player player) {
    int index = hashing(player.name);

    // Create a new node for the current player
    ListNode* newNode = (ListNode*) malloc(sizeof(ListNode));
    newNode->player = player;
    newNode->next = NULL;

    // If the linked list at the index is empty, insert the new node
    if (((ListNode**)(hash->players))[index] == NULL) {
        ((ListNode**)(hash->players))[index] = newNode;
    } else {
        // If not empty, traverse the linked list and insert at the end
        ListNode* current = ((ListNode**)(hash->players))[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to handle collisions using balanced trees (AVL trees)
void hash_BalancedTrees(Hash* hash, Player player) {
    int index = hashing(player.name);

    // Insert the player into the AVL tree at the index
    ((AVLNode**)(hash->players))[index] = insertAVLNode(((AVLNode**)(hash->players))[index], player);
}

// Function to handle collisions using open addressing (linear probing)
void hash_OpenAddressing(Hash* hash, Player player) {
    int index = hashing(player.name);

    // Linear probing to find the next available slot
    while (((Player*)(hash->players))[index].name != -1) {
        index = (index + 1) % M;
    }

    // Insert the player into the found slot
    ((Player*)(hash->players))[index] = player;
}

// Hashing function
int hashing(int chave) {
    return (chave % M);
}

// Function to search for an player in the hash table based on the chosen strategy
Player search(Hash* hash, Player player, int collision_resolution_strategy) {
    // Implement based on the chosen collision resolution strategy
    if (collision_resolution_strategy == 1) {
        // Implement search for linked lists
    } else if (collision_resolution_strategy == 2) {
        // Implement search for balanced trees
    } else {
        // Implement search for open addressing
    }
    // Dummy return; replace with actual logic
    Player dummyPlayer;
    strcpy(dummyPlayer.name, "");  // Initialize name as an empty string
    return dummyPlayer;
}

// Function to insert an player into the hash table based on the chosen strategy
void hash_insert(Hash* hash, Player player, int collision_resolution_strategy) {
    // Implement based on the chosen collision resolution strategy
    if (collision_resolution_strategy == 1) {
        hash_LinkedList(hash, player);
    } else if (collision_resolution_strategy == 2) {
        hash_BalancedTrees(hash, player);
    } else {
        hash_OpenAddressing(hash, player);
    }
}

// Function to remove an player from the hash table based on the chosen strategy
void hash_remove(Hash* hash, Player player, int collision_resolution_strategy) {
    // Implement based on the chosen collision resolution strategy
    if (collision_resolution_strategy == 1) {
        // Implement removal for linked lists
    } else if (collision_resolution_strategy == 2) {
        // Implement removal for balanced trees
    } else {
        // Implement removal for open addressing
    }
}

// Utility function to insert a player into an AVL tree
AVLNode* insertAVLNode(AVLNode* node, Player player) {
    // Perform standard BST insertion
    if (node == NULL) {
        AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
        strcpy(newNode->player.name, player.name);
        newNode->player.age = player.age;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    // Compare player names using strcmp
    int comparisonResult = strcmp(player.name, node->player.name);

    if (comparisonResult < 0) {
        // player.name is lexicographically less than node->player.name
        node->left = insertAVLNode(node->left, player);
    } else if (comparisonResult > 0) {
        // player.name is lexicographically greater than node->player.name
        node->right = insertAVLNode(node->right, player);
    } else {
        // Duplicate keys are not allowed
        return node;
    }

    // Update height of the current node
    updateHeight(node);

    // Get the balance factor
    int balance = getBalance(node);

    // Perform rotations if needed to balance the tree
    // Left Left Case
    if (balance > 1 && strcmp(player.name, node->left->player.name) < 0) {
        return rotateRight(node);
    }
    // Right Right Case
    if (balance < -1 && strcmp(player.name, node->right->player.name) > 0) {
        return rotateLeft(node);
    }
    // Left Right Case
    if (balance > 1 && strcmp(player.name, node->left->player.name) > 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // Right Left Case
    if (balance < -1 && strcmp(player.name, node->right->player.name) < 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Utility function to perform left rotation in AVL tree
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

// Utility function to perform right rotation in AVL tree
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

// Utility function to get the balance factor of an AVL tree node
int getBalance(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Utility function to get the height of an AVL tree node
int getHeight(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Utility function to update the height of an AVL tree node
void updateHeight(AVLNode* node) {
    if (node != NULL) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
    }
}

// Instance Reader
int readPlayers(Player playersArray[], int maxPlayers) {
    FILE *file = fopen("players.csv", "r");
    if (file == NULL) {
        perror("Error opening the file");
        return 0;
    }

    int count = 0;
    char line[256]; // Assuming each line is at most 256 characters

    // Skip the header line
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        perror("Error reading header");
        return 0;
    }

    while (fgets(line, sizeof(line), file)) {
        if (count >= maxPlayers) {
            printf("Warning: Maximum player limit reached. Some players may not be loaded.\n");
            break;
        }

        // Parse the CSV line into struct fields
        char *token = strtok(line, ",");
        if (token == NULL) {
            fclose(file);
            perror("Error reading name");
            return count;
        }
        strncpy(playersArray[count].name, token, sizeof(playersArray[count].name) - 1);
        playersArray[count].name[sizeof(playersArray[count].name) - 1] = '\0'; // Ensure null-termination

        token = strtok(NULL, ",");
        if (token == NULL) {
            fclose(file);
            perror("Error reading position");
            return count;
        }
        strncpy(playersArray[count].position, token, sizeof(playersArray[count].position) - 1);
        playersArray[count].position[sizeof(playersArray[count].position) - 1] = '\0';

        token = strtok(NULL, ",");
        if (token == NULL) {
            fclose(file);
            perror("Error reading naturalness");
            return count;
        }
        strncpy(playersArray[count].naturalness, token, sizeof(playersArray[count].naturalness) - 1);
        playersArray[count].naturalness[sizeof(playersArray[count].naturalness) - 1] = '\0';

        token = strtok(NULL, ",");
        if (token == NULL) {
            fclose(file);
            perror("Error reading team");
            return count;
        }
        strncpy(playersArray[count].team, token, sizeof(playersArray[count].team) - 1);
        playersArray[count].team[sizeof(playersArray[count].team) - 1] = '\0';

        token = strtok(NULL, ",");
        if (token == NULL) {
            fclose(file);
            perror("Error reading age");
            return count;
        }
        playersArray[count].age = atoi(token);

        count++;
    }
    fclose(file);

    return count;
}

// Display the menu
void collision_handling_choice() {
    printf("\n===============================");
    printf("\n\t Collision Handling");
    printf("\n===============================");
    printf("\n0. Exit");
    printf("\n1. Linked List");
    printf("\n2. Balanced Trees");
    printf("\n3. Open Addressing");
    printf("\n===============================");
}

int main() { 
    clock_t start_time, end_time;
    double cpu_time_used;
    // Read player data from the file
    int maxPlayers = 1200; // Maximum number of players to read
    Player playersArray[maxPlayers];
    int numPlayers = readPlayers(playersArray, maxPlayers);

    if (numPlayers == 0) {
        return (1);
    }

    // Add this variable to store the chosen strategy
    int collision_resolution_strategy = -1;
    do {
        collision_handling_choice();
        printf("\n\tEnter your choice: ");
        scanf("%d", &collision_resolution_strategy);

        // Benchmarking
        start_time = clock();
        switch(collision_resolution_strategy) {
            case 0:
                // </> Halt </>.
                return 0;
            case 1:
                // Linked List
                /* Create a hash */
                Hash* hash = create_hash(10, collision_resolution_strategy);
                Player player;
                for (int i = 0; i < numPlayers; i++) {
                    hash_insert(hash, playersArray[i], collision_resolution_strategy);
                }
                break;
            case 2:
                // Balanced Trees
                /* Create a hash */
                Hash* hash = create_hash(10, collision_resolution_strategy);
                Player player;
                for (int i = 0; i < numPlayers; i++) {
                    hash_insert(hash, playersArray[i], collision_resolution_strategy);
                }
                break;
            case 3:
                // Open Addressing
                /* Create a hash */
                Hash* hash = create_hash(10, collision_resolution_strategy);
                Player player;
                for (int i = 0; i < numPlayers; i++) {
                    hash_insert(hash, playersArray[i], collision_resolution_strategy);
                }
                break;
            default:
                printf("\nInvalid Output!");
                break;
        }
        end_time = clock();
        cpu_time_used = ((double)(1000 * (end_time - start_time))) / CLOCKS_PER_SEC;
        printf("\nTime taken: %.4f milliseconds", cpu_time_used);
    } while(1);

    return 0;
}
