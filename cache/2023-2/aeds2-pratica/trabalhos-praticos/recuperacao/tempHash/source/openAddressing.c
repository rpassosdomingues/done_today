/**
 * =========================================================================
 * Utility functions to collision handling using Open Addressing
 * =========================================================================
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "header.h"

#include "instanceReader.c"

#define HASH_TABLE_SIZE 1200 // M

// Function to create a open addressing
Player* createOpenAddressing(const char* playerName, int age) {
    Player* newPlayer = (Player*)malloc(sizeof(Player));
    if (newPlayer == NULL) {
        // Handle allocation failure
        printf("Unable to create player. Memory Allocation Error\n");
        return NULL;
    }

    // Copy player information to the new player
    strcpy(newPlayer->name, playerName);
    newPlayer->age = age;

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
        // Optionally print a success message or handle success in some way
    } else {
        // Handle collision or attempt to insert in a non-empty slot
        printf("Collision or non-empty slot at index %d\n", index);
        // Optionally return an error code or handle the error in some way
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

// Function to free the memory used by open addressing
void freeOpenAddressing(Hash* hash) {
    if (hash == NULL || hash->players == NULL) {
        return;
    }
    // Free the array itself
    free(hash->players);
}