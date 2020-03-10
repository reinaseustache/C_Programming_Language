// Reina Eustache (N00867316@students.ncc.edu)
// CSC217 D1
// Project 2: "Inventory Part 1"
// Due 11/26/18 11:59 pm
// Item.c
// This file contains functions that manipulate items in the store
// such as merging the duplicate items received from standard input
// and printing the final tree will all the items in it.

#include "item.h"

// void treePrint
// This function print a tree in order, first the left children, then
// the parent then the right children.
// It accepts the root node for the tree that should be printed
void treePrint(struct tnode *node)
{
    if(node != NULL){
        treePrint(node->left);

        deleteSpace(node->price);

        if(node->count != 0)
            printf("%d %s $%s: %d in stock\n", node->sku, node->description, node->price, node->count);

        treePrint(node->right);
    }
}

// void deleteSpace
// This function deletes any trailing spaces from the string passed
// to the function
// It accepts a point to char where the trailing spaces should be removed
void deleteSpace (char *tempDescription)
{            
    int i; // stores the position of a character in tempDescription
    i = strlen(tempDescription) - 1;

    while(isspace(tempDescription[i]))
        --i;

    tempDescription[i + 1] = '\0';
}

// struct tnode *addRightChild
// This function adds items to the right of the parent only as they come.
// Memory is dynamically alloccated of the position of the child to add is found.
// It accepts a struct tnode pointer for the root of a tree, an integer SKU, pointer
// to char description and the pointer to char price.
// It returns a struct tnode pointer for the root of a tree with the 
// added item
struct tnode *addRightChild(struct tnode *newNode, int sku, char *descr, char *price)
{
    if(newNode == NULL) {
        newNode = (struct tnode *)malloc(sizeof(struct tnode));
        newNode->sku = sku;
        newNode->description = strDuplicate(descr);
        newNode->price = strDuplicate(price);
        newNode->count = 1;
        newNode->left = newNode->right = NULL;
    }
    else
        newNode->right = addRightChild(newNode->right, sku, descr, price);

    return newNode;
}

// struct tnode *addToTree
// This function adds items to the sorted tree based on whether an SKU is less than
// or greater that the current root's SKU.
// It accepts a struct tnode pointer for the root of a tree, an integer SKU, pointer
// to char description and the pointer to char price.
// It returns a struct tnode pointer for the root of a tree with no dupplicates
struct tnode *addToTree(struct tnode *newNode, int sku, char *descr, char *price)
{
    int cond = 0; // checks whether an SKU is less than or greater that the current root's SKU

    if(newNode == NULL) {
        newNode = (struct tnode *)malloc(sizeof(struct tnode));
        newNode->sku = sku;
        newNode->description = strDuplicate(descr);
        newNode->price = strDuplicate(price);
        newNode->count = 1;
        newNode->left = newNode->right = NULL;
    } 
    // checks if only description is given
    else if (sku == 0 && (strcmp(descr, "NULL") != 0) && strcmp(price, "NULL") == 0){
        newNode = findDescription(newNode, descr, price);
    }
    // checks if SKU and description are given
    else if (((cond = (sku - newNode->sku)) == 0) && (strcmp(descr, "NULL") != 0) && strcmp(price, "NULL") == 0){
        newNode->description = strDuplicate(descr);
        newNode->count++;
    }
    // checks if SKU, description and price are given
    else if (((cond = (sku - newNode->sku)) == 0) && (strcmp(descr, "NULL") != 0) && strcmp(price, "NULL") != 0){
        newNode->description = strDuplicate(descr);
        newNode->price = strDuplicate(price);
        newNode->count++;
    }
    // checks if SKU and price are given
    else if (((cond = (sku - newNode->sku)) == 0) && (strcmp(descr, "NULL") == 0) && strcmp(price, "NULL") != 0){
        newNode->price = strDuplicate(price);
        newNode->count++;
    }
    // checks if description and price are given
    else if (sku == 0 && (strcmp(descr, "NULL") != 0) && strcmp(price, "NULL") != 0)
        newNode = findDescription(newNode, descr, price);
    // checks if only SKU is given
    else if (((cond = (sku - newNode->sku)) == 0) && (strcmp(descr, "NULL") == 0) && strcmp(price, "NULL") == 0)
        newNode->count++;
    // checks if sku provided is less than the root's sku
    else if (cond < 0)
        newNode->left = addToTree(newNode->left, sku, descr, price);
    // sku provided is greater than the root's sku
    else
        newNode->right = addToTree(newNode->right, sku, descr, price);
    
    return newNode;
}

// struct tnode *findDescription
// This function looks through an entire tree for the node with the
// specified description.
// It accepts a struct tnode pointer for the root of a tree, pointer
// to char description to look for and the pointer to char price to
// modify if any
// It returns a struct tnode pointer for the root of a tree with the 
// modified count or pice
struct tnode *findDescription(struct tnode *node, char *descr, char *price)
{
    if(node != NULL){
        node->left = findDescription(node->left, descr, price);

        // checks if the description is equal to the description in another node
        // and no price is provided
        if((strcmp(descr, node->description) == 0) && (strcmp(price, "NULL") == 0))
            node->count++;
        // checks if the description is equal to the description in another node
        // and price is provided
        else if((strcmp(descr, node->description) == 0) && (strcmp(price, "NULL") != 0)){
            node->price = strDuplicate(price);
            node->count++;
        }

        node->right = findDescription(node->right, descr, price);
    }
    return node;
}

// struct tnode *mergeItems
// This function iterates through the tree looking for items where the
// sku and description are provided and calls a funtion to add them 
// first to another tree then it adds the rest of the items.
// It accepts a struct tnode pointer for the root of a tree
// It returns a struct tnode pointer to a fully sorted tree
struct tnode *mergeItems(struct tnode *node)
{
    struct tnode *merged; // stores the root of the tree with no duplicates
    merged = NULL;

    struct tnode *temp = NULL; // stores the items left over that do not have an sku and description

    while(node != NULL){
        // checks if sku and description are provided
        if (node->sku != 0 && strcmp(node->description, "NULL") != 0) 
            merged = addToTree(merged, node->sku, node->description, node->price);
        // adds anything where sku and description are not provided to another tree
        else
            temp = addRightChild(temp, node->sku, node->description, node->price);
        
        node = node->right;
    }

    while(temp != NULL){
        merged = addToTree(merged, temp->sku, temp->description, temp->price);
        temp = temp->right;
    }
    
    return merged; 
    
}

// char *strDuplicate
// This function dynamically allocates memory for a given string and
// returns a copy of the string.
// It accepts a pointer to char
// It returns a copy of the string that was passed to the function
char *strDuplicate(char *str)
{
    char *p; // pointer for str based on the amount of memory needed
    p = (char *)malloc(strlen(str) + 1);

    if(p != NULL)
        strcpy(p, str);
    
    return p;
}
