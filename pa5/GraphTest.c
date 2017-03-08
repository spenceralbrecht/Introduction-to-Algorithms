//-----------------------------------------------------------------------------
// Spencer Albrecht
// salbrech
// PA5 CS101
// GraphTest.c
// Independently tests Graph.c
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
int main(int argc, char const *argv[]) {
    // Tests Graph.c
    int size = 5;
    List testList = newList();
    Graph testGraph = newGraph(size);

    for(int i = 1; i<=size; i++) append(testList, i);

    addArc(testGraph, 1,2);
    addArc(testGraph, 1,5);
    addArc(testGraph, 2,3);
    addArc(testGraph, 2,5);
    addArc(testGraph, 3,2);
    addArc(testGraph, 3,4);
    addArc(testGraph, 3,5);
    addArc(testGraph, 4,2);
    addArc(testGraph, 4,4);
    addArc(testGraph, 5,1);
    addArc(testGraph, 5,3);
    printGraph(stdout, testGraph);

    DFS(testGraph, testList);
    fprintf(stdout, "\n");

    // Tests the getDiscover() function
    fprintf(stdout, "getDiscover()\n");
    fprintf(stdout, "%d\n", getDiscover(testGraph, 1));

    // Tests the getFinish() function
    fprintf(stdout, "getFinish()\n");
    fprintf(stdout, "%d\n", getFinish(testGraph, 2));

    // Tests the getParent() function
    fprintf(stdout, "getParent()\n");
    fprintf(stdout, "%d\n", getParent(testGraph, 3));

    Graph transposeGraph = transpose(testGraph);
    Graph copy  = copyGraph(testGraph);

    fprintf(stdout, "Copy of Graph = \n");
    printGraph(stdout, copy);
    fprintf(stdout, "\n");

    fprintf(stdout, "Transpose of Graph\n");
    printGraph(stdout, transposeGraph);
    fprintf(stdout, "\n");

    DFS(transposeGraph, testList);
    fprintf(stdout, "\n");

    // Tests the getDiscover() function
    fprintf(stdout, "getDiscover()\n");
    fprintf(stdout, "%d\n", getDiscover(transposeGraph, 3));

    // Tests the getFinish() function
    fprintf(stdout, "getFinish()\n");
    fprintf(stdout, "%d\n", getFinish(transposeGraph, 4));

    // Tests the getParent() function
    fprintf(stdout, "getParent()\n");
    fprintf(stdout, "%d\n", getParent(transposeGraph, 5));

    freeList(&testList);
    freeGraph(&testGraph);
    freeGraph(&transposeGraph);
    freeGraph(&copy);
    return(0);
}
