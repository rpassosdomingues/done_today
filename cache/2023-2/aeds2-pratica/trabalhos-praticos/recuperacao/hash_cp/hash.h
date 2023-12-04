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

// Node structure for linked list
typedef struct List {
    Player player;
    struct List* next;
} List;

// Node structure for AVL Tree
typedef struct AVLTree {
    Player player;
    struct AVLTree* left;
    struct AVLTree* right;
    int height;
} AVLTree;

// Structure for Open Addressing
typedef struct Hash {
    struct Player* players;
} Hash;

// Create a hash
Hash* createHash(Hash* existingHash, int collisionResolutionStrategy);

// Function to handle collisions using linked lists
void hash_LinkedList(Hash* hash, Player player);
// Function to handle collisions using balanced Trees (AVL Trees)
void hash_BalancedTrees(Hash* hash, Player player);
// Function to handle collisions using open addressing (linear probing)
void hash_OpenAddressing(Hash* hash, Player player);

// Hashing Function
int hashing(const char* key);

// Gets a player from the hash
Player search(Hash* hash, Player player, int collision_resolution_strategy);
// Insert a new element in the hash
void hash_insert(Hash* hash, Player player, int collisionResolutionStrategy);
// Remove an element from the hash according to its key
void hash_remove(Hash* hash, Player player, int collisionResolutionStrategy);

// Auxiliary functions to handle collisions using linked list
List* createList(Player player);
List* searchList(List* head, const char* playerName);
void insertList(List** head, Player player);
void removeList(List** head, const char* playerName);

// Auxiliary functions to handle collisions using balanced tree
AVLTree* createAVLTree(Player player);
AVLTree* searchAVLTree(AVLTree* node);
AVLTree* searchFather(AVLTree* root, AVLTree* node, AVLTree* parent);
AVLTree* insertAVLTree(AVLTree* root);
AVLTree* removeAVLTree(AVLTree* root);
AVLTree* minValueNode(AVLTree* node);
AVLTree* rotateRight(AVLTree* node);
AVLTree* rotateLeft(AVLTree* node);
AVLTree* balanceNode(AVLTree* node);
int height(AVLTree* node);
int balanceFactor(AVLTree* node);
void updateHeight(AVLTree* node);

// Free Memory allocated for the hash table
void free_hash(Hash* hash, int collision_resolution_strategy);
void freeList(List* chain);
void freeAVLTree(AVLTree* node);

// Instance Reader
int readPlayers(Player playersArray[], int maxPlayers);

// Show the menu for choices of Collision Handling
void collision_handling_choice();

#endif // _H_HASH_
