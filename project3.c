// Reina Eustache (N00867316@students.ncc.edu)
// CSC217 D1
// Project 2: "Inventory Part 1"
// Due 11/26/18 11:59 pm
// Project2.c
// This file processes inventory for a store be reading information such 
// as SKU, description and price as they come from standard input and 
// formats each line to store data in the appropriate category.

#include "project3.h"

// int main
// This functions gets each line from standard input and uses sscanf to
// determine which item fields have been provided and stores them in temporary
// variables to later add them to a tree. It then calls mergeItems to get rid
// of dupplicate items and prints the final tree.
// Returns an exit code of 0 if the program ran successully
int main(int argc, char *argv[]) {
    struct tnode *root; // stores the root of the tree
    root = NULL;

    char line[MAXLINE]; // stores the line that was just read in
    
    int tempSku; // stores an item's SKU if one was read in
    char tempDescription[MAXLINE]; // stores an item's description if one was read in
    char tempPrice[MAXLINE]; // stores an item's price if one was read in
    char nothing[] = "NULL"; // stores null as a string in a field's place if it was not read in
    
    while (getLine2(line, MAXLINE) > 0){
        // checks if SKU, description and price are given
        if(sscanf(line, "%d %[^1234567890] %s", &tempSku, tempDescription, tempPrice) == 3){
            deleteSpace(tempDescription);
            deleteSpace(tempPrice);

            root = addRightChild(root, tempSku, tempDescription, tempPrice);
        }
        // checks if SKU and description are given
        else if(sscanf(line, "%d %[^/1234567890]", &tempSku, tempDescription) == 2){
            deleteSpace(tempDescription);

            root = addRightChild(root, tempSku, tempDescription, nothing);
        }
        // checks if SKU and price are given
        else if(sscanf(line, "%d %[^/abcdefghijklmnopqrstuvwxyz]", &tempSku, tempPrice) == 2){
            deleteSpace(tempPrice);

            root = addRightChild(root, tempSku, nothing, tempPrice);
        }
        // checks if description and price are given
        else if(sscanf(line, "%[^/1234567890] %[^/abcdefghijklmnopqrstuvwxyz]", tempDescription, tempPrice) == 2){
            deleteSpace(tempDescription);
            deleteSpace(tempPrice);

            root = addRightChild(root, 0, tempDescription, tempPrice);
        }
        // checks if only SKU is given
        else if(sscanf(line, "%d", &tempSku) == 1)
            root = addRightChild(root, tempSku, nothing, nothing);
        // checks if only description is given
        else if(sscanf(line, "%[^/1234567890]", tempDescription) == 1){
            deleteSpace(tempDescription);

            root = addRightChild(root, 0, tempDescription, nothing);
        }
    }
    
    // stores the final inventory tree with no duplicate items
    struct tnode *tFinal;
    tFinal = mergeItems(root);
    
    treePrint(tFinal);

    FILE *fp; // pointer to store the specified to read from

    if(argc == 1)
        printf("Please specify a file name.");
    else{
        while(--argc > 0){
            // unable to read the file
            if((fp = fopen(*++argv, "r")) == NULL){
                printf("Can't open file %s\n", *argv);
                return 1;
            }
            // able to read and make a sale
            else{
                makeSale(fp, tFinal);
                fclose(fp);
            }
        }
    }

    return 0;
}

// int getLine2
// This function reads a line at a time from standard input until it
// either reaches a new line charater, end of file or the maximum
// characters.
// It accepts the maximum number of characters there can be in a line 
// and a char array to put the characters in.
// It returns an integer with the number of charaters in a line
int getLine2(char currentLine[], int maxChars)
{
    int character; // store a single character from input
    int i; // to move over in the char array

    // gets a new charater from input until the maximum characters have
    // been reached, there is a new line character or the file has ended
    for (i = 0; i < maxChars - 1 && (character = getchar()) != EOF && character != '\n'; ++i) 
        currentLine[i] = character;

    if (character == '\n') 
    {
        currentLine[i] = character;
        ++i;
    }

    currentLine[i] = '\0';

    return i;
}