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
    tempGraph->lastVertex = 0;
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
// void getPath(List L, Graph G, int vertex) {
//     if (vertex < 1 || vertex > getOrder(G)) {
//         fprintf(stderr,
//         "getPath() must be passed a valid vertex in Graph.c\n");
//         exit(EXIT_FAILURE);
//     }
// }

/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int vertexOne, int vertexTwo) {
    // Add vertexTwo to adjacency list of vertexOne
    printf("line 133\n");
    //printf("v1 = %d", vertexOne);
    //printf("v2 = %d", vertexTwo);
    List listOne = G->adjacent[vertexOne];
    List listTwo = G->adjacent[vertexTwo];
    printf("line 135\n");
    // Insert the vertex in order
    if (length(listOne) > 0) {
        moveFront(listOne);
        while (index(listOne)!=-1 && vertexTwo >= get(listOne)) {
            moveNext(listOne);
        }
        if (index(listOne)!=-1) {
            insertBefore(listOne, vertexTwo);
        }
        else {
            append(listOne, vertexTwo);
        }

        printf("line 137\n");
    }
    else {
        append(listOne, vertexTwo);
    }


    // Add vertexOne to adjacency list of vertexTwo
    if (length(listTwo) > 0) {
        moveFront(listTwo);
        while (index(listTwo)!=-1 && vertexOne >= get(listTwo)) {
            moveNext(listTwo);
        }
        if (index(listTwo)!=-1) {
            insertBefore(listTwo, vertexOne);
        }
        else {
            append(listTwo, vertexOne);
        }
    }
    else {
        append(listTwo, vertexOne);
    }
}
void addArc(Graph G, int u, int v);

void BFS(Graph G, int sourceVertex);

/*** Other operations ***/
void printGraph(FILE* out, Graph G) {
    for (int i = 1; i <= G->order; i++) {
        fprintf(out, "%d: ",i);
        printList(out, G->adjacent[i]);
        fprintf(out,"\n");
    }
}
