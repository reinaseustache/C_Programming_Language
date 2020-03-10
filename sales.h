// Reina Eustache
// Project 2: "Inventory Part 1"
// Due 11/26/18 11:59 pm
// Sales.h
// This header file contains header files along with the function 
// prototypes needed in sales.c.

#include "project3.h"

void makeSale(FILE *fp, struct tnode *root);
struct tnode* search(struct tnode* root, int sku);
int readLineFromFile(char currentLine[], int maxChars, FILE *fp);
