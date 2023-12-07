#ifndef HEADER_H
#define HEADER_H

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

// Hashing Function
int hashing(const char* key);

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
void freeList(List* head);
void freeAVLTree(AVLTree* root);
void freeOpenAddressing(Hash* hash);

#endif // HEADER_H