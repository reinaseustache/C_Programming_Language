# C_Programming_Language

Projects

### Project 1
* project1.c

This program reads an unknown amount of lines from standard input and displays the line with the most vowels to standard output.

### Project 2
* project2.c
* project2.h

This program processes inventory for a store be reading information such as SKU, description and price as they come from standard input and formats each line to store data in the appropriate category.

### Project 3 
* project3.c
* project3.h
* item.c
* item.h
* sales.c
* sales.h
* Makefile
* input.txt (sample input)
* sales.txt (sample salesperson data)
* sales2.txt (sample salesperson data)

To run:
> make

> ./project3 < input.txt sales.txt sales2.txt

This program builds on project 2 but also processing inventory for a store be reading information such as SKU, description and price as they come from standard input and formats each line to store data in the appropriate category. It also processes the sale of an item by taking in a tree containing inventory data and a file pointer for the file to read sales data from for a particular sales person. It manipulates items in the store such as merging the duplicate items received from standard input and printing the final tree will all the items in it.
