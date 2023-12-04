#ifndef _H_HASH_
#define _H_HASH_

// Define a struct for the player object
typedef struct Player {
    char name[256];
    char position[64];
    char naturalness[64];
    char team[64];
    int age;
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
    Player* players;
} Hash;

// Instance Reader
int readPlayers(Player playersArray[]);

// Creates and initializes a hash table according to a specific collision resolution strategy.
Hash* createHash(Hash* existingHash, Player player[], int collision_resolution_strategy);

// Function to handle collisions using linked lists
void hash_LinkedList(Hash* hash, Player player);
// Function to handle collisions using balanced Trees (AVL Trees)
void hash_BalancedTrees(Hash* hash, Player player);
// Function to handle collisions using open addressing (linear probing)
void hash_OpenAddressing(Hash* hash, Player player);

// Hashing Function
int hashing(const char* key);

// Gets a player from the hash
Player searchHash(Hash* hash, Player player, int collision_resolution_strategy);
// Insert a new element in the hash
void insertHash(Hash* hash, Player player, int collisionResolutionStrategy);
// Remove an element from the hash according to its key
void removeHash(Hash* hash, Player player, int collisionResolutionStrategy);

// Auxiliary functions to handle collisions using Linked List
List* createList(Player player);
List* searchList(List* head, const char* playerName);
void insertList(List** head, Player player);
void removeList(List** head, const char* playerName);

// Auxiliary functions to handle collisions using AVL tree
AVLTree* createAVLTree(Player player);
AVLTree* searchAVLTree(AVLTree* node, Player player);
AVLTree* searchFather(AVLTree* root, AVLTree* node, AVLTree* parent);
AVLTree* insertAVLTree(AVLTree* root, Player player);
AVLTree* removeAVLTree(AVLTree* root, Player player);
AVLTree* minValueNode(AVLTree* node);
AVLTree* rotateRight(AVLTree* node);
AVLTree* rotateLeft(AVLTree* node);
AVLTree* balanceNode(AVLTree* node);
int height(AVLTree* node);
int balanceFactor(AVLTree* node);
void updateHeight(AVLTree* node);

// Auxiliary functions to handle collisions using Open Addressing
Player* createOpenAddressing(const char* playerName, int age);
Player* searchOpenAddressing(Hash* hash, const char* playerName);
void insertOpenAddressing(Hash* hash, Player* player, int index);
void removeOpenAddressing(Hash* hash, const char* playerName);
int isEmptySlot(Hash* hash, int index);

// Free Memory allocated for the hash table
void freeHash(Hash* hash, int collision_resolution_strategy);
void freeList(List* chain);
void freeAVLTree(AVLTree* node);
void freeOpenAddressing(Hash* hash);

// Show the menu for choices of Collision Handling
void collision_handling_choice();

#endif // _H_HASH_
