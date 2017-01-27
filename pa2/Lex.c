//-----------------------------------------------------------------------------
// Spencer Albrecht
// salbrech
// PA1 CS101
// Lex.c
// Sorts the words in files alphabetically
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

// Constant for the length of a line and string
#define MAX_LEN 160

int main(int argc, char* argv[]){
    // Check if the number of command line arguments are correct
    if (argc!=3) {
        fprintf(stderr,
            "Usage: Lex <input file> <output file>\n");
            exit(EXIT_FAILURE);
    }

    FILE *infile, *outfile;
    char *stringList[MAX_LEN];
    char line[MAX_LEN];
    int counter = 0;
    int x = 0;

    // Open files for reading and writing
    infile = fopen(argv[1], "r");
    outfile = fopen(argv[2], "w");

    // Makes sure the infile and outfile are not NULL
    if( infile==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if( outfile==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // Reads in the file to a string array one line at a time
    while (fgets(line, sizeof(line), infile)) {
        stringList[counter] = calloc(strlen(line)+1, 1);
        strcpy(stringList[counter], line);
        counter++;
    }

    //Correctly insert indices into tempList
    List tempList = newList();
    for (int i = 0; i < counter; i++) {
        // Add the first element to the list without any
        // comparison needed
        if (i==0) {
            // Add the first element and put the cursor on it
            prepend(tempList, i);
        }
        else {
            int j = i-1;
            // Move the cursor to the back for start of comparisons
            moveBack(tempList);
            // Compares the words in the file to the indices of tempList
            while(j>=0 && strcmp(stringList[i],stringList[get(tempList)])<0) {
                movePrev(tempList);
                j--;
            }

            moveFront(tempList);
            // If we are supposed to insert before the first element
            if (j==-1) {
                insertBefore(tempList, i);
            }
            else {
                // Move the cursor to the correct spot for insertion
                for (int k = 0; k<j; k++) {
                    moveNext(tempList);
                }
                insertAfter(tempList, i);
            }
        }

    }

    // Free the memory allocated for the string array that held the
    // lines of the file
    for(int i = 0; i<counter; i++) {
    	free(stringList[i]);
    }

    // Prints the correct output to the file based on the list
    moveFront(tempList);
    while(index(tempList)>=0){
        x = get(tempList);
        // Prints the correct array element
        // based on the sorted List
        fprintf(outfile, "%s", stringList[x]);
        moveNext(tempList);
    }

    // Free the memory we allocated for the list
    freeList(&tempList);

    /* close files */
    fclose(infile);
    fclose(outfile);


    return(0);
}
