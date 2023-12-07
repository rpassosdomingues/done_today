#ifndef _H_HASH_
#define _H_HASH_

// Define a struct for the player object
typedef struct Player {
    char name[256];
    char position[64];
    char naturalness[64];
    char team[64];
    int age;
    int deleted;
} Player;

// Node structure for the linked list
typedef struct List {
    Player player;
    struct List* next;
} List;

// Node structure for the AVL Tree
typedef struct AVLTree {
    Player player;
    struct AVLTree* left;
    struct AVLTree* right;
    int height;
} AVLTree;

// Structure for Open Addressing
typedef struct Hash {
    List** playerList;
    AVLTree** playerTree;
    Player** playerOpen;
} Hash;

// Instance Reader
int readPlayers(Player playersArray[]);

// Creates and initializes a hash table according to a specific collision resolution strategy.
Hash* createHash(Hash* existingHash, Player player[], int collision_resolution_strategy);

// Function to handle collisions using linked lists
Hash* hash_LinkedList(Hash* hash, Player player);
// Function to handle collisions using balanced Trees (AVL Trees)
Hash* hash_BalancedTrees(Hash* hash, Player player);
// Function to handle collisions using open addressing (linear probing)
Hash* hash_OpenAddressing(Hash* hash, Player player);

// Hashing Function
int hashing(const char* key);

// Gets a player from the hash
Hash* searchHash(Hash* hash, Player player, int collision_resolution_strategy);
// Insert a new element in the hash
Hash* insertHash(Hash* hash, Player player, int collision_resolution_strategy);
// Remove an element from the hash according to its key
Hash* removeHash(Hash* hash, Player player, int collision_resolution_strategy);

// Free Memory allocated for the hash table
void freeHash(Hash* hash, int collision_resolution_strategy);

// Show the menu for choices of Collision Handling
void collision_handling_choice();

#endif // _H_HASH_
