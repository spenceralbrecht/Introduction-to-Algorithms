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
#define WHITE 1
#define GREY 2
#define BLACK 3

// Definition of the GraphObj type
typedef struct GraphObj {
    int order;
    int size;
    int lastVertex;
    // Declaration of arrays
    List *adjacent;
    int *color;
    int *parent;
    int *distance;
} GraphObj;


/*** Constructors-Destructors ***/
Graph newGraph(int n) {
    Graph tempGraph = (Graph) malloc(sizeof(GraphObj));
    if (tempGraph==NULL) {
        fprintf(stderr,
        "malloc() failed when trying to allocate for newGraph\n");
        exit(EXIT_FAILURE);
    }
    // Initialize all fields
    tempGraph->order = n;
    tempGraph->size = 0;
    tempGraph->lastVertex = NIL;
    tempGraph->adjacent = calloc(n+1, sizeof(List));
    tempGraph->color = calloc(n+1, sizeof(int));
    tempGraph->parent = calloc(n+1, sizeof(int));
    tempGraph->distance = calloc(n+1, sizeof(int));

    // Initialize the empty lists of the graph
    for(int i = 1; i < tempGraph->order+1; i++) {
      tempGraph->adjacent[i] = newList();
      tempGraph->color[i] = WHITE;
      tempGraph->distance[i] = INF;
      tempGraph->parent[i] = NIL;
   }

    return tempGraph;

}
// Frees all memory in a GraphObj
void freeGraph(Graph* pG) {
    if(pG!=NULL && *pG!=NULL){
        /* free all heap memory associated with *pG */
        // Loop through the Graph and free each List
        Graph temp = *pG;
        for (int i = 1; i< (*pG)->order+1; i++) {
            freeList(&(temp->adjacent[i]));
        }
        // Free the array now that it's lists have been freed
        free(temp->adjacent);
        // Free each int array
        free(temp->color);
        free(temp->parent);
        free(temp->distance);
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/
// Returns the order of the Graph
int getOrder(Graph G) {
    return G->order;
}
// Returns the size of the Graph
int getSize(Graph G) {
    return G->size;
}
// Returns source vertex most recently used
int getSource(Graph G) {
    return G->lastVertex;
}
// Returns the parent of the vertex if it exits
// Precondition: 1<=vertex<=getOrder(G)
int getParent(Graph G, int vertex) {
    if (vertex < 1 || vertex > getOrder(G)) {
        fprintf(stderr,
        "getParent() must be passed a valid vertex in Graph.c\n");
        exit(EXIT_FAILURE);
    }
    if (G->parent[vertex] == NIL) {
        return NIL;
    }
    else {
        return G->parent[vertex];
    }
}
// Returns the distance from the most recent BFS source to the vertex
// Precondition: 1<=vertex<=getOrder(G)
int getDist(Graph G, int vertex) {
    if (vertex < 1 || vertex > getOrder(G)) {
        fprintf(stderr,
        "getDist() must be passed a valid vertex in Graph.c\n");
        exit(EXIT_FAILURE);
    }
    if (G->distance[vertex]!=NIL) {
        return G->distance[vertex];
    }
    else {
        return NIL;
    }
}
// Appends to the List the vertices of the shortest path in G from the
// source to the vertex
// Precondition: getSource(G)!=NIL
void getPath(List L, Graph G, int terminus) {
    if (terminus < 1 || terminus > getOrder(G)) {
        fprintf(stderr,
        "getPath() must be passed a valid vertex in Graph.c\n");
        exit(EXIT_FAILURE);
    }
    if (getSource(G)==NIL) {
        fprintf(stderr,
        "getSource() must be called before getPath() in Graph.c\n");
        exit(EXIT_FAILURE);
    }
    int vertex = G->lastVertex;
    // If the vertex we are at is the one we were trying to reach
    if (vertex==terminus) {
        prepend(L,terminus);
    }
    // If the vertex we are trying to reach has no parent, it is unreachable
    // and therefore the PATH is NIL
    else if (G->parent[terminus]==NIL) {
        append(L,NIL);
    }
    // If the vertex we are at is along the path to the terminus add it to the
    // list and then search the parent vertex
    else {
        prepend(L,terminus);
        getPath(L, G, G->parent[terminus]);
    }
}

/*** Manipulation procedures ***/
void makeNull(Graph G) {
    // Clear each adjacency list
    for (int i = 1; i<getOrder(G)+1; i++) {
        clear(G->adjacent[i]);
    }
    // Set the number of edges to zero
    G->size = 0;
}
// Adds an undirected edge between two vertices
void addEdge(Graph G, int vertexOne, int vertexTwo) {
    // Add vertexTwo to adjacency list of vertexOne
    addArc(G, vertexOne, vertexTwo);
    // Add vertexOne to adjacency list of vertexTwo
    addArc(G, vertexTwo, vertexOne);
    // Decrease the size by one because two edges were added by addArc
    G->size--;
}
// Adds a directed edge between two vertices
void addArc(Graph G, int vertexOne, int vertexTwo) {
    List listOne = G->adjacent[vertexOne];
    moveFront(listOne);
    // Move to the correct position in the list
    while (index(listOne)!=-1 && vertexTwo >= get(listOne)) {
        moveNext(listOne);
    }
    // If we haven't reached the end of the List
    if (index(listOne)!=-1) {
        insertBefore(listOne, vertexTwo);
    }
    // Append if vertexTwo is larger than all other vertices in the List
    else {
        append(listOne, vertexTwo);
    }
    G->size++;
}
// Performs BFS on a Graph with a source vertex
void BFS(Graph G, int sourceVertex) {
    // Initialize all of the vertices
    for (int i = 1; i < G->order+1; i++) {
        G->parent[i] = NIL;
        G->distance[i] = INF;
        G->color[i] = WHITE;
    }
    // Set the properties of the source vertex
    G->lastVertex = sourceVertex;
    G->color[sourceVertex] = GREY;
    G->distance[sourceVertex] = 0;
    List Queue = newList();
    append(Queue, sourceVertex);
    // Discover vertices until all have been found
    while (length(Queue)>0) {
        moveFront(Queue);
        int vertex = get(Queue);
        deleteFront(Queue);
        List adjacentList = G->adjacent[vertex];
        moveFront(adjacentList);
        while (index(adjacentList)!=-1) {
            int adjVertex = get(adjacentList);
            // Discover the vertex if it was undiscovered
            if (G->color[adjVertex]==WHITE) {
                G->color[adjVertex] = GREY;
                G->parent[adjVertex] = vertex;
                G->distance[adjVertex] = G->distance[vertex]+1;
                append(Queue, adjVertex);
            }
            moveNext(adjacentList);
        }
    }
    freeList(&Queue);
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G) {
    // Print the graph's adjacency list line by line
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ",i);
        if (length(G->adjacent[i])>0) {
            printList(out, G->adjacent[i]);
        }
        fprintf(out,"\n");
    }
}
