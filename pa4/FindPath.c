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
    FILE *fileIn, *fileOut;
    char buffer[100];
    int numInputs;
    // Exit if the file input doesn't match the format
    if (argc==0) {
        fprintf(stderr,
        "Usage: FindPath <inputfile> <outputfile>\n");
        exit(EXIT_FAILURE);
    }

    // Open the files for reading and writing
    fileIn = fopen(argv[1], "r");
    fileOut = fopen(argv[2], "w");

    fscanf(fileIn, "%d", &numInputs);
    printf("%d\n", numInputs);
    Graph testGraph = newGraph(numInputs);
    int vertexOne, vertexTwo;
    fscanf(fileIn, "%d %d", &vertexOne, &vertexTwo);
    printf("Vertex One = %d Vertex Two = %d\n", vertexOne, vertexTwo);
    addEdge(testGraph,vertexOne, vertexTwo);
    //printf("line 33\n");
    while(fgets(buffer, 100, fileIn)!=NULL && (vertexOne!=0 && vertexTwo!=0)) {
        //printf("line 34\n");
        //fscanf(fileIn, "%d %d", &vertexOne, &vertexTwo);
        printf("Vertex One = %d Vertex Two = %d\n", vertexOne, vertexTwo);
        //printf("line 36\n");
        addEdge(testGraph,vertexOne, vertexTwo);
        fscanf(fileIn, "%d %d", &vertexOne, &vertexTwo);
    }
    //printf("line 42");
    printGraph(fileOut, testGraph);
    return 0;
}
