/**
 * =========================================================================
 * Utility functions to collision handling using Open Addressing
 * =========================================================================
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "header.h"

#include "../data/instanceReader.c"

#define HASH_TABLE_SIZE 1200 // M

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
    printf("Player '%s' not found in open addressing\n", playerName);
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