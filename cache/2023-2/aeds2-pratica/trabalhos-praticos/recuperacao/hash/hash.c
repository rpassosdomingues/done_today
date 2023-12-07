/**
 * ===============================
 * Collision Handling | Hash Table
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

#define HASH_TABLE_SIZE 1200 // M
#define MAX_PLAYERS 1149

// Instance Reader
int readPlayers(Player playersArray[]) {
    FILE *file = fopen("players.csv", "r");
    if (file == NULL) {
        perror("Error opening the file");
        return 0;
    }

    int count = 0;
    char line[256];

    // Skip the header line
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        perror("Error reading header");
        return 0;
    }

    while (fgets(line, sizeof(line), file)) {
        if (count >= MAX_PLAYERS) {
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

// Creates and initializes a hash table according to a specific collision resolution strategy.
Hash* createHash(Hash* existingHash, Player player[], int collision_resolution_strategy) {
    // Free the old hash memory if not NULL
    if (existingHash != NULL) {
        freeHash(existingHash, collision_resolution_strategy);
    }

    if (HASH_TABLE_SIZE <= 0) {
        printf("Error: Invalid hash table size.\n");
        return NULL;
    }

    // Allocate memory for the Hash structure
    Hash* hash = (Hash*)malloc(sizeof(Hash));
    hash->players = (Player*)malloc(HASH_TABLE_SIZE * sizeof(Player));
    if (hash == NULL) {
        // Handle allocation failure
        printf("Memory Allocation Error\n");
        return NULL;
    }

    // Initialize the players array based on the collision resolution strategy
    if (collision_resolution_strategy == 1) {
        // Linked List strategy
        hash->playerList = malloc(HASH_TABLE_SIZE * sizeof(List*));
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            ((List**)(hash->playerList))[i] = createList(player);
        }
    } else if (collision_resolution_strategy == 2) {
        // Balanced Trees strategy
        hash->playerTree = malloc(HASH_TABLE_SIZE * sizeof(AVLTree*));
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            ((AVLTree**)(hash->playerTree))[i] = createAVLTree(player);
        }
    } else if (collision_resolution_strategy == 3) {
        // Open Addressing strategy
        hash->playerOpen = malloc(HASH_TABLE_SIZE * sizeof(Player*));
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            ((Player**)(hash->playerOpen))[i] = createOpenAddressing(player);
        }
    } else {
        // Free allocated memory in case of an error
        printf("Error: Invalid collision resolution strategy.\n");
        free(hash);
        return NULL;
    }

    return hash;
}

// Function to handle collisions using separate linked list
Hash* hash_LinkedList(Hash* hash, Player player) {
    int index = hashing(player.name);
    
    // Update the hash table with the new head returned by insertList
    ((List**)(hash->playerList))[index] = insertList(((List**)(hash->playerList))[index], player);

    // Return the modified hash table
    return hash;
}

// Function to handle collisions using AVL Tree
Hash* hash_BalancedTrees(Hash* hash, Player player) {
    // Calculate the index using the hash function
    int index = hashing(player.name);

    // Access the AVL Tree at the calculated index
    AVLTree** avlTree = &(((AVLTree**)(hash->playerTree))[index]);

    // Insert the player into the AVL Tree at the index
    *avlTree = insertAVLTree(*avlTree, player);
    if (*avlTree == NULL) {
        printf("Error: AVL node insertion failed.\n");
    }

    // Return the original or modified hash table
    return hash;
}

// Function to handle collisions using open addressing (linear probing)
Hash* hash_OpenAddressing(Hash* hash, Player player) {
    int index = hashing(player.name);
    int initialIndex = index;

    // Linear probing to find the next available slot
    do {
        if (((Player**)(hash->playerOpen))[index] == NULL) {
            // Empty slot found, insert the player and break the loop
            insertOpenAddressing(hash, &player, index);
            //break;  // Uncomment this line to break out of the loop
        }
        // Move to the next slot using linear probing
        index = (index + 1) % HASH_TABLE_SIZE;
    } while (index != initialIndex);

    // Return the modified hash table
    return hash;
}

/**
 * -------------------------------------------------------------------
 * Hashing function for strings (djb2 algorithm) with modulo operation
 * -------------------------------------------------------------------
 * Reference:
 * ...................................................................
 * Shah, S., & Shaikh, A. (2016, August).
 * Hash based optimization for faster access to inverted index.
 * In 2016 International Conference on Inventive Computation
 * Technologies (ICICT) (Vol. 1, pp. 1-5). IEEE.
 * -------------------------------------------------------------------
 */
int hashing(const char* key) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    // Take modulo with the size of the hash table to ensure compatibility
    return (int)(hash % HASH_TABLE_SIZE);
}

// Function to search for a player in the hash table based on the chosen strategy
Hash* searchHash(Hash* hash, Player player, int collision_resolution_strategy) {
    int index = hashing(player.name);

    if (collision_resolution_strategy == 1) {
        // Search for linked lists
        List* current = searchList(((List**)(hash->players))[index], player.name);

        if (current != NULL) {
            // Player found in linked list
            return hash;
        }
    } else if (collision_resolution_strategy == 2) {
        // Search for balanced Trees
        AVLTree* result = searchAVLTree(((AVLTree**)(hash->players))[index], player);

        if (result != NULL) {
            // Player found in AVL Tree
            return hash;
        }
    } else if (collision_resolution_strategy == 3) {
        // Search for open addressing
        Player* result = searchOpenAddressing(hash, player.name);

        if (result != NULL) {
            // Player found in open addressing
            return hash;
        }
    }

    // Player not found, return the original hash table
    return hash;
}

// Function to insert a player into the hash table based on the chosen strategy
Hash* insertHash(Hash* hash, Player player, int collision_resolution_strategy) {
    // Implement based on the chosen collision resolution strategy
    if (collision_resolution_strategy == 1) {
        return hash_LinkedList(hash, player);
    } else if (collision_resolution_strategy == 2) {
        return hash_BalancedTrees(hash, player);
    } else if (collision_resolution_strategy == 3) {
        return hash_OpenAddressing(hash, player);
    } else {
        printf("\n\t No attack handling strategy chosen. \n");
        return NULL;
    }
}

// Function to remove a player from the hash table based on the chosen strategy
Hash* removeHash(Hash* hash, Player player, int collision_resolution_strategy) {
    if (collision_resolution_strategy == 1) {
        // Linked List strategy
        int index = hashing(player.name);
        ((List**)(hash->players))[index] = removeList(((List**)(hash->players))[index], player.name);
    } else if (collision_resolution_strategy == 2) {
        // Balanced Trees strategy
        int index = hashing(player.name);
        ((AVLTree**)(hash->players))[index] = removeAVLTree(((AVLTree**)(hash->players))[index], player);
    } else if (collision_resolution_strategy == 3) {
        // Open Addressing strategy
        removeOpenAddressing(hash, player.name);
    } else {
        // Handle unknown collision resolution strategy
        printf("Invalid collision resolution strategy\n");
        return hash;
    }

    // Return the modified hash table
    return hash;
}

/**
 * =========================================================================
 * Utility functions to collision handling using Linked List
 * =========================================================================
 */

// Function to create a new node for the linked list and insert an array of players
List* createList(Player player[]) {
    // Create a new node for the first player
    List* head = (List*)malloc(sizeof(List));
    if (head == NULL) {
        // Handle allocation failure
        printf("Memory Allocation Error\n");
        return NULL;
    }

    // Copy the player information to the allocated memory
    strcpy(head->player.name, player[0].name);
    strcpy(head->player.position, player[0].position);
    strcpy(head->player.naturalness, player[0].naturalness);
    strcpy(head->player.team, player[0].team);
    head->player.age = player[0].age;

    head->next = NULL;

    // Insert the remaining players into the linked list
    List* current = head;  // Maintain a pointer to the current end of the list
    for (int i = 1; i < MAX_PLAYERS; i++) {
        List* newNode = (List*)malloc(sizeof(List));
        if (newNode == NULL) {
            // Handle allocation failure
            printf("Memory Allocation Error\n");
            // Clean up: Free the memory used by the linked list
            //freeList(head);
            return NULL;
        }

        // Copy the player information to the allocated memory
        strcpy(newNode->player.name, player[i].name);
        strcpy(newNode->player.position, player[i].position);
        strcpy(newNode->player.naturalness, player[i].naturalness);
        strcpy(newNode->player.team, player[i].team);
        newNode->player.age = player[i].age;

        newNode->next = NULL;  // Set the next pointer of the new node to NULL

        // Link the new node to the end of the list
        current->next = newNode;
        current = newNode;  // Update the current pointer to the new end of the list
    }

    return head;
}

// Function to search for a node with a specific player name in a linked list
List* searchList(List* head, const char* playerName) {
    List* current = head;
    while (current != NULL) {
        if (strcmp(current->player.name, playerName) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;  // Player not found in the linked list
}

// Function to insert a new node into a linked list using createList
List* insertList(List* head, Player player) {
    // Create a new node for the current player
    List* newNode = (List*)malloc(sizeof(List));
    if (newNode == NULL) {
        // Handle allocation failure
        printf("Unable to insert player. Memory Allocation Error\n");
        return head;  // Return the original head unchanged
    }

    // Assign player to the new node
    newNode->player = player;
    newNode->next = NULL;

    // If the linked list is empty, insert the new node as the head
    if (head == NULL) {
        return newNode;  // Return the new node as the new head
    } else {
        // If not empty, find the last node and insert at the end
        List* lastNode = head;
        while (lastNode->next != NULL) {
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;

        return head;  // Return the original head unchanged
    }
}

// Function to remove a node with a specific player name from a linked list
List* removeList(List* head, const char* playerName) {
    // Use the searchList function to find the node to be removed
    List* current = searchList(head, playerName);
    if (current == NULL) {
        // Player not found in the linked list
        return head;  // Return the original head unchanged
    }

    // If the node to be removed is the head
    if (current == head) {
        head = head->next;
    } else {
        // Traverse the linked list to find the previous node
        List* prev = head;
        while (prev->next != current) {
            prev = prev->next;
        }

        // Remove the node
        prev->next = current->next;
    }

    // Free the memory used by the removed node
    //freeList(current);

    return head;  // Return the updated head after removal
}

/**
 * =========================================================================
 * Utility functions to collision handling using AVL Tree
 * =========================================================================
 */

// Function to create an AVL tree from an array of players
AVLTree* createAVLTree(Player player[]) {
    AVLTree* root = NULL;

    for (int i = 0; i < MAX_PLAYERS; i++) {
        root = insertAVLTree(root, player[i]);
        root = balanceNode(root);  // Ensure balancing after each insertion
    }

    return root;
}

// Utility function to create an AVL node
AVLTree* createAVLNode(Player player) {
    AVLTree* newNode = (AVLTree*)malloc(sizeof(AVLTree));
    if (newNode == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    newNode->player = player;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;

    return newNode;
}

// Function to search for a player in AVL Tree
AVLTree* searchAVLTree(AVLTree* node, Player player) {
    // Check for NULL node
    if (node == NULL) {
        //printf("Error: AVL Tree is NULL.\n");
        return NULL;
    }

    while (node != NULL) {
        int comparisonResult = strcmp(player.name, node->player.name);

        if (comparisonResult < 0) {
            node = node->left;
        } else if (comparisonResult > 0) {
            node = node->right;
        } else {
            // Player found in AVL Tree
            return node;
        }
    }

    // Player not found in AVL Tree
    printf("Player '%s' not found in AVL Tree.\n", player.name);
    return NULL;
}

// Function to find the parent node of a given node in the Tree
AVLTree* searchFather(AVLTree* root, AVLTree* node, AVLTree* parent) {
    if (root == NULL || node == NULL) {
        return NULL;  // Node not found or Tree is empty
    }

    AVLTree* foundNode = searchAVLTree(root, node->player);

    if (foundNode != NULL) {
        // Node found, check if it is the child of the provided parent
        if (parent == NULL || (root->left == foundNode || root->right == foundNode)) {
            return root;  // Found the parent of the given node
        }
    }

    // Search recursively
    AVLTree* nextRoot = (strcmp(node->player.name, root->player.name) < 0) ? root->left : root->right;
    return searchFather(nextRoot, node, root);
}

// Function to insert a node into an AVL Tree
AVLTree* insertAVLTree(AVLTree* root, Player player) {
    if (root == NULL) {
        // Create a new AVL node for the current player
        return createAVLNode(player);
    }

    int comparisonResult = strcmp(player.name, root->player.name);

    if (comparisonResult < 0) {
        root->left = insertAVLTree(root->left, player);
    } else if (comparisonResult > 0) {
        root->right = insertAVLTree(root->right, player);
    }

    return balanceNode(root);
}

// Function to remove a node from an AVL Tree
AVLTree* removeAVLTree(AVLTree* root, Player player) {
    AVLTree *oldNode = searchAVLTree(root, player);

    if (oldNode == NULL) {
        //printf("\nSub-Tree not found");
        return root;
    }

    AVLTree* father = searchFather(root, oldNode, NULL);

    if (oldNode->left == NULL && oldNode->right == NULL) {
        // Case 1: No children
        if (father == NULL) {
            // Remove root
            free(root);
            return NULL;
        } else if (father->left == oldNode) {
            free(father->left);
            father->left = NULL;
        } else {
            free(father->right);
            father->right = NULL;
        }
    } else if (oldNode->left == NULL || oldNode->right == NULL) {
        // Case 2: One child
        AVLTree *child = (oldNode->left != NULL) ? oldNode->left : oldNode->right;
        if (father == NULL) {
            //free(root);
            return child;
        } else if (father->left == oldNode) {
            free(father->left);
            father->left = child;
        } else {
            free(father->right);
            father->right = child;
        }
    } else {
        // Case 3: Two children.
        AVLTree *successor = minValueNode(oldNode->right);
        oldNode->player = successor->player;
        oldNode->right = removeMinValueNode(oldNode->right);
    }

    return balanceNode(father);
}

AVLTree* removeMinValueNode(AVLTree* root) {
    if (root == NULL || root->left == NULL) {
        return root->right;
    }

    root->left = removeMinValueNode(root->left);
    return balanceNode(root);
}

// Function to find the node with the minimum value in a Tree
AVLTree* minValueNode(AVLTree* node) {
    AVLTree *current = node;

    // Find the leftmost leaf node
    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}

// Function to perform a right rotation on a node in an AVL Tree
AVLTree* rotateRight(AVLTree* node) {
    AVLTree* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Function to perform a left rotation on a node in an AVL Tree
AVLTree* rotateLeft(AVLTree* node) {
    AVLTree* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Function to balance an AVL Tree node
AVLTree* balanceNode(AVLTree* node) {
    updateHeight(node);
    int factor = balanceFactor(node);

    if (factor > 1) {
        if (balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    if (factor < -1) {
        if (balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node;
}

// Function to get the height of a node (used in AVL Trees)
int height(AVLTree* node) {
    if (node == NULL) {
        return -1;
    }
    return node->height;
}

// Function to calculate the balance factor of a node (used in AVL Trees)
int balanceFactor(AVLTree* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// Function to update the height of a node
void updateHeight(AVLTree* node) {
    if (node == NULL) {
        return;
    }
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

/**
 * =========================================================================
 * Utility functions to collision handling using Open Addressing
 * =========================================================================
 */

// Function to create a open addressing
Player* createOpenAddressing(Player player[]) {
    Player* newPlayer = malloc(HASH_TABLE_SIZE * sizeof(Player));

    if (newPlayer == NULL) {
        // Handle memory allocation failure if necessary
        printf("Memory Allocation Error\n");
        return NULL;
    }

    // Initialize hash table slots
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        // Initialize each player in the slot as empty
        newPlayer[i].name[0] = '\0';
        newPlayer[i].position[0] = '\0';
        newPlayer[i].naturalness[0] = '\0';
        newPlayer[i].team[0] = '\0';
        newPlayer[i].age = 0;
    }

    // Insert players into the array using open addressing
    for (int i = 0; i < MAX_PLAYERS; i++) {
        int index = hashing(newPlayer[i].name);
        int initialIndex = index;

        do {
            if (newPlayer[index].name[0] == '\0' || index == initialIndex) {
                // Found an empty slot or returned to the starting index
                // Insert player into slot
                strcpy(newPlayer[index].name, player[i].name);
                strcpy(newPlayer[index].position, player[i].position);
                strcpy(newPlayer[index].naturalness, player[i].naturalness);
                strcpy(newPlayer[index].team, player[i].team);
                newPlayer[index].age = player[i].age;
                break;
            }
            index = (index + 1) % HASH_TABLE_SIZE;
        } while (index != initialIndex);
    }

    return newPlayer;
}

// Function to search for a player in open addressing
Player* searchOpenAddressing(Hash* hash, const char* playerName) {
    int index = hashing(playerName);
    int start_index = index;

    do {
        // Check if the slot is not empty and the player's name matches
        if (!isEmptySlot(hash, index) && strcmp(((Player*)(hash->players))[index].name, playerName) == 0) {
            return &((Player*)(hash->players))[index];
        }

        index = (index + 1) % HASH_TABLE_SIZE;
    } while (index != start_index);

    // Player not found
    return NULL;
}

// Function to insert a player into the hash table based on open addressing
void insertOpenAddressing(Hash* hash, Player* player, int index) {
    // Check if the slot is empty before inserting
    if (isEmptySlot(hash, index)) {
        // Copy player information to the hash table
        ((Player*)(hash->players))[index] = *player;
    } else {
        // Handle collision or attempt to insert in a non-empty slot
        printf("Collision or non-empty slot at index %d\n", index);
    }
}

// Function to remove a player from the hash table based on open addressing
Player* removeOpenAddressing(Hash* hash, const char* playerName) {
    int index = hashing(playerName);
    int start_index = index;

    do {
        // Check if the slot is not empty and the player's name matches
        if (!isEmptySlot(hash, index) && strcmp(((Player*)(hash->players))[index].name, playerName) == 0) {
            // Player found in open addressing, mark the slot as deleted
            return markAsDeleted(hash, index);
        }

        index = (index + 1) % HASH_TABLE_SIZE;
    } while (index != start_index);

    // Player not found
    //printf("Player '%s' not found in open addressing\n", playerName);
    return NULL;
}

// Function to mark a slot as deleted in open addressing
Player* markAsDeleted(Hash* hash, int index) {
    // Check if the slot is already marked as deleted
    if (((Player*)(hash->players))[index].deleted) {
        // Optionally handle this case differently (e.g., return an error code)
        printf("Slot at index %d is already marked as deleted\n", index);
        return NULL;
    }

    // Mark the slot as deleted
    ((Player*)(hash->players))[index].deleted = 1;

    // No need to allocate memory for deletedPlayer, as the original slot is not cleared

    return &((Player*)(hash->players))[index];
}

// Function to check if a slot in open addressing is empty
int isEmptySlot(Hash* hash, int index) {
    return strcmp(((Player*)(hash->players))[index].name, "") == 0;
}

// Function to free the memory allocated for the hash table
void freeHash(Hash* hash, int collision_resolution_strategy) {
    if (hash == NULL) {
        return;
    }

    if (collision_resolution_strategy == 1) {
        // Linked List strategy
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            freeList(((List**)(hash->players))[i]);
        }
    } else if (collision_resolution_strategy == 2) {
        // Balanced Trees strategy
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            freeAVLTree(((AVLTree**)(hash->players))[i]);
        }
    } else if (collision_resolution_strategy == 3) {
        // Open Addressing strategy
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            freeOpenAddressing(((Hash**)(hash->players))[i]);
        }
    } else {
        free(hash);
    }
}

// Function to free the memory used by the linked list
void freeList(List* head) {
    while (head != NULL) {
        List* temp = head;
        head = head->next;
        free(temp->player.name);
        free(temp);
    }
}

// Function to free the memory allocated for an AVL Tree
void freeAVLTree(AVLTree* root) {
    if (root != NULL) {
        freeAVLTree(root->left);
        freeAVLTree(root->right);
        free(root);
    }
}

void freeOpenAddressing(Hash* hash) {
    if (hash == NULL || hash->playerOpen == NULL) {
        return;
    }

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (((Hash**)(hash->playerOpen))[i] != NULL) {
            free(((Hash**)(hash->playerOpen))[i]);
        }
    }

    // Free the array itself
    free(hash->playerOpen);
}

// Display the menu
void collision_handling_choice() {
    printf("\n===============================");
    printf("\n       Collision Handling");
    printf("\n===============================");
    printf("\n0. Exit");
    printf("\n1. Linked List");
    printf("\n2. Balanced Trees");
    printf("\n3. Open Addressing");
    printf("\n===============================");
}

int main() { 
    
    Player playersArray[MAX_PLAYERS];
    // Read player data from the file
    int numPlayers = readPlayers(playersArray);

    if (numPlayers == 0) {
        return 1;
    }
    
    Hash* hash = NULL;
    int collision_resolution_strategy = -1;
    do {
        collision_handling_choice();
        printf("\n\tEnter your choice: ");
        scanf("%d", &collision_resolution_strategy);

        // Initialize clock to time benckmark
        clock_t start_time, end_time;
        double cpu_time_used = 0;

        // Benchmarking cases
        switch(collision_resolution_strategy) {
            case 0:
                // Free the memory allocated for the hash table
                freeHash(hash, collision_resolution_strategy);
                // </> Halt </>.
                return 0;
            case 1:
                // Linked List
                start_time = clock();
                hash = createHash(hash, playersArray, collision_resolution_strategy);
                for (int i = 0; i < numPlayers; i++) {
                    insertHash(hash, playersArray[i], collision_resolution_strategy);
                    removeHash(hash, playersArray[i], collision_resolution_strategy);
                }
                end_time = clock();
                cpu_time_used = ((double)(1000 * (end_time - start_time))) / CLOCKS_PER_SEC;

                // Output
                printf("\nTime taken: %.4f milliseconds", cpu_time_used);
                break;
            case 2:
                // Balanced Trees
                start_time = clock();
                hash = createHash(hash, playersArray, collision_resolution_strategy);
                for (int i = 0; i < numPlayers; i++) {
                    insertHash(hash, playersArray[i], collision_resolution_strategy);
                    removeHash(hash, playersArray[i], collision_resolution_strategy);
                }
                end_time = clock();
                cpu_time_used = ((double)(1000 * (end_time - start_time))) / CLOCKS_PER_SEC;

                // Output
                printf("\nTime taken: %.4f milliseconds", cpu_time_used);
                break;
            case 3:
                // Open Addressing
                start_time = clock();
                hash = createHash(hash, playersArray, collision_resolution_strategy);
                for (int i = 0; i < numPlayers; i++) {
                    insertHash(hash, playersArray[i], collision_resolution_strategy);
                    removeHash(hash, playersArray[i], collision_resolution_strategy);
                }
                end_time = clock();
                cpu_time_used = ((double)(1000 * (end_time - start_time))) / CLOCKS_PER_SEC;

                // Output
                printf("\nTime taken: %.4f milliseconds", cpu_time_used);
                break;
            default:
                printf("\nInvalid Output!");
                break;
        }

    } while(1);

}
