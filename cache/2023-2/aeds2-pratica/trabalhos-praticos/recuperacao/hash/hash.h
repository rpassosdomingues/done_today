#ifndef _H_HASH_
#define _H_HASH_

// Define a struct to player object
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

// Node structure for AVL tree
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
Hash* create_hash(Hash* existingHash, int collision_resolution_strategy);

// Function to handle collisions using linked lists
void hash_LinkedList(Hash* hash, Player player);
// Function to handle collisions using balanced trees (AVL trees)
void hash_BalancedTrees(Hash* hash, Player player);
// Function to handle collisions using open addressing (linear probing)
void hash_OpenAddressing(Hash* hash, Player player);

// Hashing Function
int hashing(const char* key);

// Gets an player from the hash
Player search(Hash* hash, Player player, int collision_resolution_strategy);
// Insert a new element in hash
void hash_insert(Hash* hash, Player player, int collision_resolution_strategy);
// Remove a element of the hash according to your key
void hash_remove(Hash* hash, Player player, int collision_resolution_strategy);

// Auxiliary functions to handle collisions using balanced tree
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

// Free Memory allocated for hash table
void free_hash(Hash* hash, int collision_resolution_strategy);
void freeAVLTree(AVLTree* node);

// Instance Reader
int readPlayers(Player playersArray[], int maxPlayers);

// Show the menu for choices of the Collision Handling
void collision_handling_choice();

#endif // _H_HASH_