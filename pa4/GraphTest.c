//-----------------------------------------------------------------------------
// Spencer Albrecht
// salbrech
// PA4 CS101
// GraphTest.c
// Independently tests Graph.c
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
int main(int argc, char const *argv[]) {
    /* code */
    Graph testGraph = newGraph(4);
    addEdge(testGraph, 1, 2);
    addEdge(testGraph, 1, 3);
    addEdge(testGraph, 1, 4);
    addEdge(testGraph, 2, 3);
    addEdge(testGraph, 2, 4);
    addEdge(testGraph, 3, 4);

    printf("getOrder = %d\n", getOrder(testGraph));

    printf("getSize = %d\n", getSize(testGraph));

    printf("printGraph\n");
    printGraph(stdout, testGraph);

    // printf("getSource = %d\n", getSource(testGraph));
    //
    // printf("getParent of 2 = %d\n", getParent(testGraph, 2));
    //
    // printf("getDist from 3 = %d\n", getDist(testGraph, 3));
    //
    // printf("getPath");
    // getPath(testList,testGraph,4);
    //
    // printf("addEdge");
    // getPath(testGraph,1,2);
    //
    // printf("addArc");
    // getPath(testGraph,1,2);
    //
    // printf("BFS");
    // getPath(testGraph,4);
    //
    // printf("printGraph");
    // getPath(testGraph);
    //
    // printf("makeNull");
    // getPath(testGraph);

    freeGraph(&testGraph);

    return 0;
}
