//-----------------------------------------------------------------------------
// Spencer Albrecht
// salbrech
// PA4 CS101
// FindPath.c
// Provides Graph interface for clients
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
int main(int argc, char const *argv[]) {
    FILE *fileIn, fileOut;
    char buffer[100];

    // Exit if the file input doesn't match the format
    if (argc==0) {
        fprintf(stderr,
        "Usage: FindPath <inputfile> <outputfile>\n");
        exit(EXIT_FAILURE);
    }

    // Open the files for reading and writing
    fileIn = fopen(argv[1], "r");
    fileOut = fopen(argv[2], "w");

    int numInputs = fgetc(fileIn)
    Graph testGraph = newGraph(numInputs);
    int vertexOne, vertexTwo;
    sscanf(buffer, "%d %d", &vertexOne, &vertexTwo);
    while(sscanf(buffer, "%d %d", &vertexOne, &vertexTwo)!=NULL && vertexOne) {
        sscanf(buffer, "%d %d", &vertexOne, &vertexTwo);
        addEdge(vertexOne, vertexTwo);
    }
    return 0;
}
