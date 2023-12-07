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
#include "main.h"

#include "data/instanceReader.c"

#include "source/linkedList.c"
#include "source/avlTree.c"
#include "source/openAddressing.c"

#define HASH_TABLE_SIZE 1200 // M
#define MAX_PLAYERS 1149

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
    if (hash == NULL) {
        // Handle allocation failure
        printf("Memory Allocation Error\n");
        return NULL;
    }

    // Initialize the players array based on the collision resolution strategy
    if (collision_resolution_strategy == 1) {
        // Linked List strategy
        hash->playerList = (List*)malloc(HASH_TABLE_SIZE * sizeof(List*));
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            ((List**)(hash->playerList))[i] = createList(player);
        }
    } else if (collision_resolution_strategy == 2) {
        // Balanced Trees strategy
        hash->playerTree = (AVLTree*)malloc(HASH_TABLE_SIZE * sizeof(AVLTree*));
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            ((AVLTree**)(hash->playerTree))[i] = createAVLTree(player);
        }
    } else if (collision_resolution_strategy == 3) {
        // Open Addressing strategy
        hash->playerOpen = (Player*)malloc(HASH_TABLE_SIZE * sizeof(Player*));
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
        List* current = searchList(((List**)(hash->playerList))[index], player.name);

        if (current != NULL) {
            // Player found in linked list
            return hash;
        }
    } else if (collision_resolution_strategy == 2) {
        // Search for balanced Trees
        AVLTree* result = searchAVLTree(((AVLTree**)(hash->playerTree))[index], player);

        if (result != NULL) {
            // Player found in AVL Tree
            return hash;
        }
    } else if (collision_resolution_strategy == 3) {
        // Search for open addressing
        Player* result = searchOpenAddressing(hash->playerOpen, player.name);

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
        ((List**)(hash->playerList))[index] = removeList(((List**)(hash->playerList))[index], player.name);
    } else if (collision_resolution_strategy == 2) {
        // Balanced Trees strategy
        int index = hashing(player.name);
        ((AVLTree**)(hash->playerTree))[index] = removeAVLTree(((AVLTree**)(hash->playerTree))[index], player);
    } else if (collision_resolution_strategy == 3) {
        // Open Addressing strategy
        removeOpenAddressing(hash->playerOpen, player.name);
    } else {
        // Handle unknown collision resolution strategy
        printf("Invalid collision resolution strategy\n");
        return hash;
    }

    // Return the modified hash table
    return hash;
}

// Function to free the memory allocated for the hash table
void freeHash(Hash* hash, int collision_resolution_strategy) {
    if (hash == NULL) {
        return;
    }

    if (collision_resolution_strategy == 1) {
        // Linked List strategy
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            freeList(((List**)(hash->playerList))[i]);
        }
    } else if (collision_resolution_strategy == 2) {
        // Balanced Trees strategy
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            freeAVLTree(((AVLTree**)(hash->playerTree))[i]);
        }
    } else if (collision_resolution_strategy == 3) {
        // Open Addressing strategy
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            freeOpenAddressing(((Hash**)(hash->playerOpen))[i]);
        }
    } else {
        free(hash);
    }
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