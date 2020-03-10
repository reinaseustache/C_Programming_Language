// Reina Eustache
// Project 3: "Inventory Part 2"
// Due 12/19/18 11:59 pm
// Sales.c
// This file has methods to process the sale of an item by taking in 
// a tree containing inventory data and a file pointer for the file 
// to read sales data from for a particular sales person.

#include "sales.h"

// void makeSale
// This function processes items for sale from a file containing an
// SKU and an amount line by line and modifies the inventory for 
// that item based on how many are sold then displays the total price
// before and after tax for each customer.
// It accepts a FILE pointer from which to read the sales data from and 
// a struct tnode pointer for the tree with the inventory.
void makeSale(FILE *fp, struct tnode *root){
    int tempSku; // stores the item's SKU read from the file
    int tempNum; // stored the amount of items to sell read from the file

    char salesPerson[MAXLINE]; // stores the salsperson's name read from the file
    char customer[MAXLINE]; // stores the customer's name read from the file

    struct tnode *found; // stores the node with the item being sold

    float total; // stores the price times the amount being sold for an item
    float price; // stores the float converted value from the string price in an item
    float beforeTax; // stores the running total being added to until the sales are done
    float tax; // stores the New York sales tax rate of 8.25%
    float afterTax; // stores the final bill with the added tax

    char line[MAXLINE]; // stores the line that was just read in

    // grabs the sales person's name
    readLineFromFile(line, MAXLINE, fp);
    if(sscanf(line, "%[^/1234567890]", salesPerson) == 1)
        deleteSpace(salesPerson);
    
    readLineFromFile(line, MAXLINE, fp);
    if(sscanf(line, "%[^/1234567890]", customer) == 1)
        deleteSpace(customer);

    printf("\nThank you, %s, for choosing CSC Music Stores!\n", customer);

    while(readLineFromFile(line, MAXLINE, fp) > 0){
        if(line[0] != '\n'){
            // checks if sku and amount are given and stores them in temporary variables
            if(sscanf(line, "%d %d", &tempSku, &tempNum) == 2)
                found = search(root, tempSku);

            // if the SKU is not found in the inventory
            if(found == NULL  || (found->count == 0)) {
                printf("SKU %d not in stock\n", tempSku);
            }
            // if there is enough of an item to sell the desired amount
            else if(found->count >= tempNum){
                found->count = found->count - tempNum;
                price = strtof(found->price, NULL);
                total = price * tempNum;
                beforeTax = beforeTax + total;
                printf("%d x %s @ $%s: $%0.2f\n", tempNum, found->description, found->price, total);
            }
            // if more of an item is being requested than there is in stock
            else if(found->count < tempNum){
               printf("Requested %d %s; only %d in stock", tempNum, found->description, found->count);
                price = strtof(found->price, NULL);
                total = price * found->count;
                beforeTax = beforeTax + total;
                printf("\n%d x %s @ $%s: $%0.2f\n", found->count, found->description, found->price, total);
                found->count = 0;
            }
        }
    }

    printf("Total sales: $%0.2f\n", beforeTax);

    tax = beforeTax * 0.0825;
    printf("Sales tax (8.25%%): $%0.2f\n", tax);

    afterTax = beforeTax + tax;
    printf("Final price: $%0.2f\n", afterTax);

    printf("Your salesperson: %s\n\n", salesPerson);

    treePrint(root);
}

// struct tnode *search
// This function looks through a tree recursively looking for the 
// specified SKU, it goes left if the current SKU is less than
// the root and right otherwise.
// It accepts a struct tnode pointer for the root of a tree, and an 
// integer with the SKU to look for.
// It returns a struct tnode pointer to the node with the specified
// SKU that it was found at and null if it was not found.
struct tnode *search(struct tnode *root, int sku) 
{
    if (root == NULL || root->sku == sku) 
       return root; 
     
    if (root->sku < sku) 
       return search(root->right, sku); 
  
    return search(root->left, sku); 
}

// int readLineFromFile
// This function reads a line at a time from a file pointer until it
// either reaches a new line charater, end of file or the maximum
// characters.
// It accepts the maximum number of characters there can be in a line 
// and a char array to put the characters in.
// It returns an integer with the number of charaters in a line
int readLineFromFile(char currentLine[], int maxChars, FILE *fp)
{
    int character; // store a single character from input
    int i; // to move over in the char array

    // gets a new charater from input until the maximum characters have
    // been reached, there is a new line character or the file has ended
    for (i = 0; i < maxChars - 1 && (character = fgetc(fp)) != EOF && character != '\n'; ++i) 
        currentLine[i] = character;

    if (character == '\n') 
    {
        currentLine[i] = character;
        ++i;
    }

    currentLine[i] = '\0';

    return i;
}
