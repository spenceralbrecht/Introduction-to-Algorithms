//-----------------------------------------------------------------------------
// Spencer Albrecht
// salbrech
// PA1 CS101
// Lex.c
// Sorts the words in files alphabetically
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
//#include<string.h>
#include"List.h"

//#include<string.h>
#define MAX_LEN 160

int strcmp(const char *s1, const char *s2);
//char* strcpy(char* dst, char* src);

int main(int argc, char* argv[]){

    // int n, x, count=0;
    // FILE *in, *out;
    // char line[MAX_LEN];
    // char tokenlist[MAX_LEN];
    // char* token;

    if (argc!=3) {
        fprintf(stderr,
            "Usage: Lex <input file> <output file>\n");
            exit(EXIT_FAILURE);
    }

    //-------------------------------

    FILE *infile, *outfile;
    char *stringList[MAX_LEN];
    char line[MAX_LEN];
    int counter = 0;
    int x = 0;

    // Open files for reading and writing
    infile = fopen(argv[1], "r");
    outfile = fopen(argv[2], "w");

    // Makes sure the file exists
    if( infile==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if( outfile==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // Reads in the lines of the file to the string array
    //while ((length = getline(&line, &bufferLength, infile)) != -1) {
    while (fgets(line, sizeof(line), infile)) {
        //strcpy(stringList[counter], line);
        //stringList[counter] = &line;
        stringList[counter] = calloc(strlen(line)+1, 1);
        strcpy(stringList[counter], line);
        //printf("%s", line);
        //printf("%d\n", counter);
        //printf("%s", stringList[counter]);
        counter++;
    }


    //printf("counter = %d\n", counter);

    // for(int i = 0; i < counter; i++) {
    //     printf("%s\n", stringList[i]);
    // }

    //-------------------------------

    // /* read each line of input file, then count and print tokens */
    // while( fgets(line, MAX_LEN, in) != NULL)  {
    //     count++;
    //     n = 0;
    //     token = strtok(line, " \n");
    //     tokenlist[0] = '\0';
    //     while( token!=NULL ){
    //         strcat(tokenlist, "   ");
    //         strcat(tokenlist, token);
    //         strcat(tokenlist, "\n");
    //         n++;
    //         token = strtok(NULL, " \n");
    //     }
    //     fprintf(out, "line %d contains %d token%s: \n", count, n, n==1?"":"s");
    //     fprintf(out, "%s\n", tokenlist);
    // }



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
    //printList(stdout,tempList);

    // Prints the correct output to the file based on the list
    moveFront(tempList);
    while(index(tempList)>=0){
        x = get(tempList);
        // Prints the correct array element
        // based on the sorted List
        fprintf(outfile, "%s", stringList[x]);
        moveNext(tempList);
    }


    /* close files */
    fclose(infile);
    fclose(outfile);


    return(0);
}

int strcmp(const char *s1, const char *s2) {
  int ret = 0;
  while (!(ret = *(unsigned char *) s1 - *(unsigned char *) s2) && *s2) ++s1, ++s2;
  if (ret < 0)
    ret = -1;
  else if (ret > 0)
    ret = 1 ;
  return ret;
}

// char* strcpy(char* dst, char* src) {
//    char* ret;
//    for(ret= dst; *dst++= *src++; );
//    return ret;
// }
