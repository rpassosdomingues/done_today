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
typedef struct ListNode {
    Player player;
    struct ListNode* next;
} ListNode;

// Node structure for AVL tree
typedef struct AVLNode {
    Player player;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

// Structure for Open Addressing
typedef struct Hash {
 struct Player* players;
} Hash;

// Create a hash
Hash* create_hash(Hash* existingHash, int size, int collision_resolution_strategy);

// Function to handle collisions using linked lists
void hash_LinkedList(Hash* hash, Player player);
// Function to handle collisions using balanced trees (AVL trees)
void hash_BalancedTrees(Hash* hash, Player player);
// Function to handle collisions using open addressing (linear probing)
void hash_OpenAddressing(Hash* hash, Player player);

// Hashing Function
int hashing(const char* key, int M);

// Gets an player from the hash
Player search(Hash* hash, Player player, int collision_resolution_strategy);
// Insert a new element in hash
void hash_insert(Hash* hash, Player player, int collision_resolution_strategy);
// Remove a element of the hash according to your key
void hash_remove(Hash* hash, Player player, int collision_resolution_strategy);

// Aux functions to handle collisions using balanced trees
AVLNode* searchAVLTree(AVLNode* node, const char* playerName);
AVLNode* insertAVLNode(AVLNode* node, Player player);
AVLNode* removeAVLNode(AVLNode* node, const char* playerName);
AVLNode* minValueNode(AVLNode* node);
AVLNode* rotateLeft(AVLNode* x);
AVLNode* rotateRight(AVLNode* y);
int getBalance(AVLNode* node);
int getHeight(AVLNode* node);
void updateHeight(AVLNode* node);

// Free Memory allocated for hash table
void free_hash(Hash* hash, int collision_resolution_strategy);
void freeAVLTree(AVLNode* node);

// Instance Reader
int readPlayers(Player playersArray[], int maxPlayers);

// Show the menu for choices of the Collision Handling
void collision_handling_choice();

#endif // _H_HASH_