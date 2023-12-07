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
    Player* players;
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

// Auxiliary functions to handle collisions using Linked List
List* createList(Player player[]);
List* searchList(List* head, const char* playerName);
List* insertList(List* head, Player player);
List* removeList(List* head, const char* playerName);

// Auxiliary functions to handle collisions using AVL tree
AVLTree* createAVLTree(Player player[]);
AVLTree* createAVLNode(Player player);
AVLTree* searchAVLTree(AVLTree* node, Player player);
AVLTree* searchFather(AVLTree* root, AVLTree* node, AVLTree* parent);
AVLTree* insertAVLTree(AVLTree* root, Player player);
AVLTree* removeAVLTree(AVLTree* root, Player player);
AVLTree* removeMinValueNode(AVLTree* root);
AVLTree* minValueNode(AVLTree* node);
AVLTree* rotateRight(AVLTree* node);
AVLTree* rotateLeft(AVLTree* node);
AVLTree* balanceNode(AVLTree* node);
int height(AVLTree* node);
int balanceFactor(AVLTree* node);
void updateHeight(AVLTree* node);

// Auxiliary functions to handle collisions using Open Addressing
Player* createOpenAddressing(Player player[]);
Player* searchOpenAddressing(Hash* hash, const char* playerName);
void insertOpenAddressing(Hash* hash, Player* player, int index);
Player* removeOpenAddressing(Hash* hash, const char* playerName);
Player* markAsDeleted(Hash* hash, int index);
int isEmptySlot(Hash* hash, int index);

// Free Memory allocated for the hash table
void freeHash(Hash* hash, int collision_resolution_strategy);
void freeList(List* head);
void freeAVLTree(AVLTree* root);
void freeOpenAddressing(Hash* hash);

// Show the menu for choices of Collision Handling
void collision_handling_choice();

#endif // _H_HASH_
