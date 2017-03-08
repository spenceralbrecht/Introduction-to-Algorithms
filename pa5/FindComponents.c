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
   fprintf(fileOut,"Adjacency list representation of G:\n");
   printGraph(fileOut, testGraph);
   fprintf(fileOut,"\n");

   List vertexOrder = newList();
   // Initialize the vertexOrder to the convention for the first DFS call
   for (int i = 1; i <= getOrder(testGraph); i++) {
      append(vertexOrder, i);
   }
   //printf("list = ");
   //printList(stdout, vertexOrder);
   //printf("list size = %d\n", length(vertexOrder));
   DFS(testGraph, vertexOrder);
   //printf("list size = %d\n", length(vertexOrder));
   Graph transposeGraph = transpose(testGraph);
   DFS(transposeGraph, vertexOrder);
   //printf("line 65\n");


   //fprintf(fileOut, "\n");
   moveFront(vertexOrder);
   //printf("line 72\n");
   int SCCcount = 0;
   //printf("line 74\n");
   while (index(vertexOrder)>-1) {
      //printf("\nline 76\n");
      int vertex = get(vertexOrder);
      //printf("line 78\n");
      if (getParent(transposeGraph, vertex)==NIL) {
         //printf("line 80\n");
         SCCcount++;
      }
      //printf("line 83\n");
      moveNext(vertexOrder);
   }
   fprintf(fileOut, "G contains %d strongly connected components:\n", SCCcount);
   //fprintf(fileOut, "Vertex Order List = ");
   //printList(fileOut, vertexOrder);

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
      fprintf(fileOut,"\n");
      //fprintf(fileOut,"after list\n");
      movePrev(vertexOrder);
      counter++;
   }
}
