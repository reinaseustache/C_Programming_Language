// Reina Eustache
// Project 2: "Inventory Part 1"
// Due 11/26/18 11:59 pm
// Item.h
// This header file contains header files along with the struct
// definitions and function prototypes needed in item.c.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct tnode {
    int sku; // stores an integer SKU associated with an item
    char *description; // stores an item description as a string
    char *price; // stores the price for an item as a string

    int count; // stores the number of a particular item that is in stock
        
    struct tnode *left; // pointer to store another item as a left child 
    struct tnode *right; // pointer to store another item as a right child 
};

struct tnode *addRightChild(struct tnode *newNode, int sku, char *description, char *price);
void treeprint(struct tnode *);
char *strDuplicate(char *str);
struct tnode *addToTree(struct tnode *newNode, int sku, char *description, char *price);
struct tnode *mergeItems(struct tnode *node);
struct tnode *findDescription(struct tnode *node, char *description, char *price);
void deleteSpace(char *description);
