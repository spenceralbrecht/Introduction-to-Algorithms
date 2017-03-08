//-----------------------------------------------------------------------------
// Spencer Albrecht
// salbrech
// PA5 CS101
// FindComponents.c
// Finds the SCC's in a graph
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
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
      addArc(testGraph,vertexOne, vertexTwo);
   }

   // Print out the adjacency list of the graph
   fprintf(fileOut,"Adjacency list representation of G:\n");
   printGraph(fileOut, testGraph);
   fprintf(fileOut,"\n");

   List vertexOrder = newList();
   // Initialize the vertexOrder to the convention for the first DFS call
   for (int i = 1; i <= getOrder(testGraph); i++) {
      append(vertexOrder, i);
   }

   DFS(testGraph, vertexOrder);
   Graph transposeGraph = transpose(testGraph);
   DFS(transposeGraph, vertexOrder);

   moveFront(vertexOrder);
   int SCCcount = 0;
   // Count the number of SCC's based on the number of NIL's
   while (index(vertexOrder)>-1) {
      int vertex = get(vertexOrder);
      if (getParent(transposeGraph, vertex)==NIL) {
         SCCcount++;
      }
      moveNext(vertexOrder);
   }

   fprintf(fileOut, "G contains %d strongly connected components:\n", SCCcount);

   int counter = 1;
   moveBack(vertexOrder);
   while (index(vertexOrder)>-1) {
      int vertex = get(vertexOrder);
      List tempList = newList();
      //printf("line 93\n");
      if (index(vertexOrder)>-1) {
         if (getParent(transposeGraph, vertex)==NIL) {
            append(tempList, vertex);
         }
         else {
            while (index(vertexOrder)>-1 && getParent(transposeGraph, get(vertexOrder))!=NIL) {
               prepend(tempList,vertex);
               movePrev(vertexOrder);
               vertex = get(vertexOrder);
            }
            // Add the first vertex of the SCC to the front of the list
            prepend(tempList, vertex);
         }
      }
      // Print out the list of the SCC vertices
      fprintf(fileOut, "Component %d: ", counter);
      printList(fileOut, tempList);
      freeList(&tempList);
      fprintf(fileOut,"\n");
      movePrev(vertexOrder);
      counter++;
   }
   freeList(&vertexOrder);
   freeGraph(&testGraph);
   freeGraph(&transposeGraph);

   fclose(fileIn);
   fclose(fileOut);
}
