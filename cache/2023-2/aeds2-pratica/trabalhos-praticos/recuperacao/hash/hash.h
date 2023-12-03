#ifndef _H_HASH_
#define _H_HASH_

typedef struct Item {
    int valor;
} Item;

typedef struct Hash {
 struct Item* items;   /* vetor de items da hash */
} Hash;

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
    Item item;
    struct ListNode* next;
} ListNode;

// Node structure for AVL tree
typedef struct AVLNode {
    Item item;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

// Create a hash
Hash* create_hash(int size);

// Insere um novo elemento na hash
void hash_insert(Hash* hash, Item item);

// Remove um elemento da hash de acordo com sua chave
void hash_remove(Hash* hash, Item item);

// Obtém um item da hash
Item search(Hash* hash, Item item);

// Função de hashing
int hashing(int key);

// Functions to handle collisions using balanced trees
int getHeight(AVLNode* node);
void updateHeight(AVLNode* node);
AVLNode* rotateRight(AVLNode* y);
AVLNode* rotateLeft(AVLNode* x);
int getBalance(AVLNode* node);
AVLNode* insertAVLNode(AVLNode* node, Item item);

// Instance Reader
int readPlayers(Player playersArray[], int maxPlayers);

// Function to handle collisions using linked lists
void hash_LinkedList(Hash* hash, Item item);
// Function to handle collisions using balanced trees (AVL trees)
void hash_BalancedTrees(Hash* hash, Item item);
// Function to handle collisions using open addressing (linear probing)
void hash_OpenAddressing(Hash* hash, Item item)

void displayMenu();

#endif // _H_HASH_