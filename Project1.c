// Reina Eustache
// CSC217 D1
// Project 1: "Vowel Counter"
// Due 10/17/18 11:59 pm
// Project1.c
// This program reads an unknown amount of lines from standard input
// and displays the line with the most vowels to standard output.

#include <stdio.h>
#define MAXLINE 120 // for the maximum characters per line

// function prototypes
int getline2(char line[], int maxline);
void copy(char outputln[], char inputln[]);
int countvowels(char line[]);

// int main
// This functions gets each line from standard input and if the
// vowels in the current line are more than the line with the
// previous most vowels, it copies that line as the new line to
// be displayed
// Returns an exit code of 0 if the program ran successully
int main()
{
    int lastMaxVows; // stores the previous number of maximum vowels
    lastMaxVows = 0;

    int nowMaxVows; // stores the most recent number of maximum vowels
    nowMaxVows = 0;

    char line[MAXLINE]; // stores the line that was just read in
    char mostVows[MAXLINE]; // stores the line with the most vowels

    printf("\nInput:\n");

    // calls the copy function if the number of vowels from the line
    // retrieved is greater than the number of vowels from the last
    // said maximum vowel line until there are no more chararacters
    // to be retireved by getLine2
    while (getLine2(line, MAXLINE) > 0)
    {
        if ((lastMaxVows = countVowels(line)) > nowMaxVows)
        {
            nowMaxVows = lastMaxVows;
            copy(mostVows, line);
        }
    }

    printf("\n\nOutput:\n");
    if (nowMaxVows > 0)
        printf("%s\n", mostVows);

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

// void copy
// This function copies the current line with the most vowels into
// another character array to be saved for output.
// It accepts the an array with the current line to be copied and 
// an array for the line to be copied into.
void copy(char outputln[], char inputln[])
{
    int i; // to move over in both char arrays
    i = 0;

    while ((outputln[i] = inputln[i]) != '\0')
        ++i;
}

// int countVowels
// This function counts the number of vowels in a given line.
// It accepts the line in which the vowels should be counted.
// It returns the number of vowels in that line.
int countVowels(char line[])
{
    int vowels; // stores the number of vowels in a line
    vowels = 0;

    int i; // to move over in the array
    i = 0;

    while(line[i] != '\0') 
    {
        if(line[i]=='a' || line[i]=='e' || line[i]=='i' || line[i]=='o' 
           || line[i]=='u' || line[i]=='A' || line[i]=='E' || line[i]=='I' 
           || line[i]=='O' || line[i]=='U')
        {
            ++vowels;
        }

        ++i;
    }

    return vowels;
}
