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

    // Makes sure the infile and outfile are not NULL
    if(fileIn==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if(fileOut==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    fgets(buffer, 100, fileIn);
    sscanf(buffer, "%d", &numInputs);

    Graph testGraph = newGraph(numInputs);
    int vertexOne = 0;
    int vertexTwo = 0;

    // Scan each line as two ints and add them as edges to the graph
    while(fgets(buffer, 100, fileIn)!=NULL) {
        sscanf(buffer, "%d %d", &vertexOne, &vertexTwo);
        if (vertexOne==0 && vertexTwo==0) {
            break;
        }
        addEdge(testGraph,vertexOne, vertexTwo);
    }

    printGraph(fileOut, testGraph);
    fprintf(fileOut,"\n");

    //Perform BFS on the list of source vertices
    while (fgets(buffer, 100, fileIn)!=NULL) {
        int sourceVertex, destinationVertex;
        sscanf(buffer, "%d %d", &sourceVertex, &destinationVertex);
        // Don't run BFS on the indicator values
        if (sourceVertex==0 && destinationVertex==0) {
            break;
        }
        BFS(testGraph, sourceVertex);
        int distance = getDist(testGraph,destinationVertex);
        // Print the output correctly to the file
        if (distance < 0 ) {
            fprintf(fileOut,"The distance from %d to %d is infinity\n",sourceVertex,destinationVertex);
            fprintf(fileOut,"No %d-%d path exists", sourceVertex, destinationVertex);
        }
        else {
            fprintf(fileOut,"The distance from %d to %d is %d\n",sourceVertex,destinationVertex,distance);
            fprintf(fileOut,"A shortest %d-%d path is: ",sourceVertex,destinationVertex);
            List pathList = newList();
            getPath(pathList,testGraph,destinationVertex);
            printList(fileOut, pathList);
            freeList(&pathList);
        }
        fprintf(fileOut,"\n\n");
    }

    freeGraph(&testGraph);

    fclose(fileIn);
    fclose(fileOut);
    
    return 0;
}
