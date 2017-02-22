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

    fscanf(fileIn, "%d", &numInputs);
    //printf("%d\n", numInputs);
    Graph testGraph = newGraph(numInputs);
    int vertexOne, vertexTwo;
    //fscanf(fileIn, "%d %d", &vertexOne, &vertexTwo);
    //printf("Vertex One = %d Vertex Two = %d\n", vertexOne, vertexTwo);
    //addEdge(testGraph,vertexOne, vertexTwo);
    //printf("line 33\n");
    while(fgets(buffer, 100, fileIn)!=NULL) {
        //printf("line 34\n");
        //fscanf(fileIn, "%d %d", &vertexOne, &vertexTwo);
        //printf("Vertex One = %d Vertex Two = %d\n", vertexOne, vertexTwo);
        //printf("line 36\n");
        fscanf(fileIn, "%d %d", &vertexOne, &vertexTwo);
        //printf("Vertex One = %d Vertex Two = %d\n", vertexOne, vertexTwo);
        if (vertexOne==0 && vertexTwo==0) {
            break;
        }
        addEdge(testGraph,vertexOne, vertexTwo);

    }
    //printf("line 42");
    printGraph(fileOut, testGraph);
    fprintf(fileOut,"\n");

    //Perform BFS on the list of source vertices
    while (fgets(buffer, 100, fileIn)!=NULL) {
        int sourceVertex, destinationVertex;
        fscanf(fileIn, "%d %d", &sourceVertex, &destinationVertex);
        //printf("sourceVertex = %d destinationVertex = %d\n", sourceVertex, destinationVertex);
        if (sourceVertex==0 && destinationVertex==0) {
            break;
        }
        BFS(testGraph, sourceVertex);
        int distance = getDist(testGraph,destinationVertex);
        fprintf(fileOut,"The distance from %d to %d is %d\n",sourceVertex,destinationVertex,distance);
        fprintf(fileOut,"A shortest %d-%d path is: ",sourceVertex,destinationVertex);
        List pathList = newList();
        getPath(pathList,testGraph,destinationVertex);
        moveFront(pathList);
        while(index(pathList)!=-1) {
            fprintf(fileOut,"%d ",get(pathList));
            moveNext(pathList);
        }
        fprintf(fileOut,"\n\n");
    }

    return 0;
}
