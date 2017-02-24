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
    for(int i = 1; i <= tempGraph->order+1; i++) {
      tempGraph->adjacent[i] = newList();
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
    if (vertex==terminus) {
        prepend(L,vertex);
    }
    else if (G->parent[terminus]==NIL) {
        append(L,NIL);
    }
    else {
        prepend(L,terminus);
        getPath(L, G, G->parent[terminus]);
    }
}

/*** Manipulation procedures ***/
void makeNull(Graph G) {
    // Clear each adjacency list
    for (int i = 1; i<=getOrder(G)+1; i++) {
        clear(G->adjacent[i]);
    }
    G->size = 0;
}
void addEdge(Graph G, int vertexOne, int vertexTwo) {
    //printf("adding vertexOne = %d and vertexTwo = %d to graph\n", vertexOne, vertexTwo);
    // Add vertexTwo to adjacency list of vertexOne
    addArc(G, vertexOne, vertexTwo);
    // Add vertexOne to adjacency list of vertexTwo
    addArc(G, vertexTwo, vertexOne);
    // Decrease the size by one because two edges were added by addArc
    G->size--;
}
void addArc(Graph G, int vertexOne, int vertexTwo) {
    List listOne = G->adjacent[vertexOne];
    //printf("adding %d to adjacency list of %d\n", vertexTwo, vertexOne);
    // if (length(listOne) > 0) {
        moveFront(listOne);
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
        //printf("adjacency list\n");
        //printList(stdout, listOne);
        //printf("\n");
    // }
    // else {
    //     prepend(listOne, vertexTwo);
    // }
    G->size++;
}

void BFS(Graph G, int sourceVertex) {
    for (int i = 1; i < G->order+1; i++) {
        //printf("line 185 in BFS\n");
        G->parent[i] = NIL;
        G->distance[i] = INF;
        G->color[i] = WHITE;
    }
    //printf("line 190 in BFS\n");
    G->lastVertex = sourceVertex;
    G->color[sourceVertex] = GREY;
    G->distance[sourceVertex] = 0;
    List Queue = newList();
    append(Queue, sourceVertex);
    //printf("line 196 in BFS\n");
    while (length(Queue)>0) {
        moveFront(Queue);
        int vertex = get(Queue);
        //printf("vertex = %d\n", vertex);

        deleteFront(Queue);
        //printf("line 201 in BFS\n");
        List adjacentList = G->adjacent[vertex];
        //printf("adjacentList length = %d\n", length(adjacentList));
        //printf("adjacentList = \n");
        //printList(stdout,adjacentList);
        moveFront(adjacentList);
        while (index(adjacentList)!=-1) {
            //printf("line 205 in BFS\n");
            //printf("index in adj list = %d\n", index(adjacentList));
            int adjVertex = get(adjacentList);
            //printf("line 207 in BFS\n");
            if (G->color[adjVertex]==WHITE) {
                G->color[adjVertex] = GREY;
                G->parent[adjVertex] = vertex;
                G->distance[adjVertex] = G->distance[vertex]+1;
                append(Queue, adjVertex);
            }
            moveNext(adjacentList);
        }
    }
    //freeList(&Queue);
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G) {
    // Print the graph's adjacency list line by line
    //printf("printing a graph\n");
    //printf("G->order = %d\n", getOrder(G));
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ",i);
        if (length(G->adjacent[i])>0) {
            printList(out, G->adjacent[i]);
        }
        fprintf(out,"\n");
    }
}
