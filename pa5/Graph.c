//-----------------------------------------------------------------------------
// Spencer Albrecht
// salbrech
// PA5 CS101
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
    // Declaration of arrays
    List *adjacent;
    int *color;
    int *parent;
    //int *time;
    int *discoverTime;
    int *finishTime;
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
    //tempGraph->time = 0;
    tempGraph->adjacent = calloc(n+1, sizeof(List));
    tempGraph->color = calloc(n+1, sizeof(int));
    tempGraph->parent = calloc(n+1, sizeof(int));
    tempGraph->discoverTime = calloc(n+1, sizeof(int));
    tempGraph->finishTime = calloc(n+1, sizeof(int));

    // Initialize the empty lists of the graph
    for(int i = 1; i < tempGraph->order+1; i++) {
      // Create an empty list for each adjacency list
      tempGraph->adjacent[i] = newList();
      // Initialize all other values properly
      tempGraph->discoverTime[i] = UNDEF;
      tempGraph->finishTime[i] = UNDEF;
      tempGraph->color[i] = WHITE;
      tempGraph->parent[i] = NIL;
   }
    return tempGraph;
}
// Frees all memory in a GraphObj
void freeGraph(Graph* pG) {
    if(pG!=NULL && *pG!=NULL){
        /* free all heap memory associated with *pG */
        // Loop through adjacent array and clear each list
        Graph temp = *pG;
        for (int i = 1; i< (*pG)->order+1; i++) {
            freeList(&(temp->adjacent[i]));
        }
        // Free the array now that the inner lists have been freed
        free(temp->adjacent);
        // Free each int array
        free(temp->color);
        free(temp->parent);
        free(temp->discoverTime);
        free(temp->finishTime);
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/
// Returns the discover time of a vertex
// Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u) {
   if (u<1 || u>getOrder(G)) {
      printf("getDiscover() in Graph.c cannot be called without a matching list size\n");
      exit(1);
   }
   return G->discoverTime[u];
}
// Returns the finish time of a vertex
// Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u) {
   if (u<1 || u>getOrder(G)) {
      printf("getFinish() in Graph.c cannot be called without a matching list size\n");
      exit(1);
   }
   return G->finishTime[u];
}
// Returns the order of the Graph
int getOrder(Graph G) {
    return G->order;
}
void DFS_VISIT(Graph G, List vertexOrder, int vertex, int* time);
// Runs DFS on a Graph G in the order of the list provided
// Pre: length(S)==getOrder(G)
void DFS(Graph G, List vertexOrder) {
   if (length(vertexOrder) != getOrder(G)) {
      fprintf(stderr,
      "DFS() in Graph.c cannot be called without a matching list size\n");
      exit(EXIT_FAILURE);
   }
   // Initialize the vertices of G
   for (int i = 1; i <=getOrder(G); i++) {
      G->color[i] = WHITE;
      G->discoverTime[i] = NIL;
   }
   int time = 0;
   //int* time = malloc(sizeof(int));
   // Make sure malloc was able to be performed
   //if (time==NULL) {
   //   fprintf(stderr,
   //   "malloc() failed when allocating for time in Graph.c\n");
   //   exit(EXIT_FAILURE);
   //}
   //*time = 0;
   //int time = 0;
   moveFront(vertexOrder);
   // Call DFS_VISIT based on the vertexOrder list
   while (index(vertexOrder)>-1) {
      int vertex = get(vertexOrder);
      if (G->color[vertex]==WHITE) {
         DFS_VISIT(G, vertexOrder, vertex, &time);
      }
      moveNext(vertexOrder);
   }
   // After DFS has finished, delete the back half of the vertexOrder
   // list because we appended all of the correct values to the beginning
   int newLength = length(vertexOrder)/2;
   for(int i = 0; i < newLength; i++) {
       deleteBack(vertexOrder);
   }
}

void DFS_VISIT(Graph G, List vertexOrder, int vertex, int* time) {
   (*time)++;
   G->discoverTime[vertex] = *time;
   G->color[vertex] = GREY;
   List adjacentList = G->adjacent[vertex];
   moveFront(adjacentList);
   // Go through the adjacency list of the current vertex
   while (index(adjacentList)>-1) {
      int adjacentVertex = get(adjacentList);
      if (G->color[adjacentVertex]==WHITE) {
         // Set the parent of the adjacent vertex to the current vertex
         G->parent[adjacentVertex] = vertex;
         DFS_VISIT(G,vertexOrder,adjacentVertex,time);
      }
      moveNext(adjacentList);
   }
   G->color[vertex] = BLACK;
   // Prepend vertices to the list so that the list ends up with
   // vertices in order of decreasing finish times
   prepend(vertexOrder, vertex);
   (*time)++;
   G->finishTime[vertex] = *time;
}

// Returns the transpose of a graph
Graph transpose(Graph G) {
   Graph tempGraph = newGraph(getOrder(G));
   int len = getOrder(G);
   for (int i = 1; i <= len; i++) {
      if (length(G->adjacent[i])>0) {
         List tempList = G->adjacent[i];
         moveFront(tempList);
         while (index(tempList)>-1) {
            int vertex = get(tempList);
            // Add the main vertex to the adjacency list of the adjacent vertex
            append(tempGraph->adjacent[vertex], i);
            moveNext(tempList);
         }
      }
   }
   return tempGraph;
}
// Returns copy a graph
Graph copyGraph(Graph G) {
   Graph graphCopy = newGraph(getOrder(G));
   int length = getOrder(G);
   for (int i = 1; i <= length; i++) {
      List adjacencyList = G->adjacent[i];
      moveFront(adjacencyList);
      while(index(adjacencyList)>-1) {
         append(graphCopy->adjacent[i], get(adjacencyList));
         moveNext(adjacencyList);
      }
   }
   return graphCopy;
}
// Returns the size of the Graph
int getSize(Graph G) {
    return G->size;
}
// Returns source vertex most recently used
// int getSource(Graph G) {
//     return G->lastVertex;
// }
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
// Returns the distance from the most recent BFS source to the vertex
// Precondition: 1<=vertex<=getOrder(G)
// int getDist(Graph G, int vertex) {
//     if (vertex < 1 || vertex > getOrder(G)) {
//         fprintf(stderr,
//         "getDist() must be passed a valid vertex in Graph.c\n");
//         exit(EXIT_FAILURE);
//     }
//     if (G->distance[vertex]!=NIL) {
//         return G->distance[vertex];
//     }
//     else {
//         return NIL;
//     }
// }
// Appends to the List the vertices of the shortest path in G from the
// source to the vertex
// Precondition: getSource(G)!=NIL
// void getPath(List L, Graph G, int terminus) {
//     if (terminus < 1 || terminus > getOrder(G)) {
//         fprintf(stderr,
//         "getPath() must be passed a valid vertex in Graph.c\n");
//         exit(EXIT_FAILURE);
//     }
//     if (getSource(G)==NIL) {
//         fprintf(stderr,
//         "getSource() must be called before getPath() in Graph.c\n");
//         exit(EXIT_FAILURE);
//     }
//     int vertex = G->lastVertex;
//     // If the vertex we are at is the one we were trying to reach
//     if (vertex==terminus) {
//         prepend(L,terminus);
//     }
//     // If the vertex we are trying to reach has no parent, it is unreachable
//     // and therefore the PATH is NIL
//     else if (G->parent[terminus]==NIL) {
//         append(L,NIL);
//     }
//     // If the vertex we are at is along the path to the terminus add it to the
//     // list and then search the parent vertex
//     else {
//         prepend(L,terminus);
//         getPath(L, G, G->parent[terminus]);
//     }
// }
//
// /*** Manipulation procedures ***/
// void makeNull(Graph G) {
//     // Clear each adjacency list
//     for (int i = 1; i<getOrder(G)+1; i++) {
//         clear(G->adjacent[i]);
//     }
//     // Set the number of edges to zero
//     G->size = 0;
// }
