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
    List testList = newList();
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

    printf("Running BFS\n");
    BFS(testGraph,4);

    printf("getSource = %d\n", getSource(testGraph));

    printf("getParent of 2 = %d\n", getParent(testGraph, 2));

    printf("getDist from 3 = %d\n", getDist(testGraph, 3));

    printf("getPath = ");
    getPath(testList,testGraph,4);
    printList(stdout, testList);

    printf("\nRunning addEdge\n");
    addEdge(testGraph,1,2);

    printf("Running addArc\n");
    addArc(testGraph,1,2);

    printf("Running makeNull\n");
    makeNull(testGraph);

    printf("getOrder = %d\n", getOrder(testGraph));

    printf("getSize = %d\n", getSize(testGraph));

    printf("printGraph\n");
    printGraph(stdout, testGraph);

    freeGraph(&testGraph);

    return 0;
}
