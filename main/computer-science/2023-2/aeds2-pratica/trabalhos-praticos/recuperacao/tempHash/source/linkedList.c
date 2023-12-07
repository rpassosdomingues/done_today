/**
 * =========================================================================
 * Utility functions to collision handling using Linked List
 * =========================================================================
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "header.h"

#include "../data/instanceReader.c"

#define MAX_PLAYERS 1149

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

// Function to free the memory used by the linked list
void freeList(List* head) {
    while (head != NULL) {
        List* temp = head;
        head = head->next;
        free(temp->player.name);
        free(temp);
    }
}