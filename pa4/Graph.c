//-----------------------------------------------------------------------------
// Spencer Albrecht
// salbrech
// PA4 CS101
// Graph.c
// Provides Graph interface for clients
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
// Definition of the GraphObj type
typdef struct GraphObj {
    int order;
    int size;
    int lastVertex;
    List adjacent[size];
    int color[order];
    int parent[order];
    int distance[size];
} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n) {
    Graph tempGraph = (Graph) malloc(sizeof(GraphObj));
    if (temp==NULL) {
        fprintf(stderr,
        "malloc() failed when trying to allocate for newGraph\n");
        exit(EXIT_FAILURE);
    }
    // Initialize all fields
    tempGraph->order = n;
    tempGraph->size = 0;
    tempGraph->lastVertex = 0;
    tempGraph->adjacent = calloc(n+1, sizeof(List));
    tempGraph->color = calloc(n+1, sizeof(int));
    tempGraph->parent = calloc(n+1, sizeof(int));
    tempGraph->distance = calloc(n+1, sizeof(int));

    // Initialize the empty lists of the graph
    for(int i = 1; i <= tempGraph->order+1; i++) {
      tempGraph->adj[i] = newList();
      tempGraph->color[i] = WHITE;
      tempGraph->distance[i] = INF;
      tempGraph->parent[i] = NIL;
   }

    return tempGraph;

}
void freeGraph(Graph* pG) {
    if(pG!=NULL && *pG!=NULL){
        /* free all heap memory associated with *pG */
        // Loop through the Graph and free each List
        Graph temp = *pG;
        for (int i = 0; i< (*pG)->order+1; i++) {
            free(&(temp->adjacent[i]));
        }
        // Free the array now that it's lists have been freed
        free(&temp->adjacent);
        // Free each int array
        free(&temp->color);
        free(&temp->parent);
        free(&temp->distance);
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/
int getOrder(Graph G) {
    return G->order;
}
int getSize(Graph G) {
    return G->size;
}
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

/*** Other operations ***/
void printGraph(FILE* out, Graph G);
