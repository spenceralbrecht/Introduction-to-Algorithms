//-----------------------------------------------------------------------------
// Spencer Albrecht
// salbrech
// PA1 CS101
// List.c
// Provides List ADT for client
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
// Private inner NodeObj struct, reference type Node, and constructor-
// destructor pair. Not exported.
typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* last;
} NodeObj;

typedef NodeObj* Node;

Node newNode(int data) {
    Node temp = (Node) malloc(sizeof(NodeObj));
    if (temp==NULL) {
        fprintf(stderr,
        "malloc() failed when trying to allocate for newNode\n");
        exit(EXIT_FAILURE);
    }
    temp->data = data;
    temp->next = NULL;
    temp->last = NULL;
    return(temp);
}

void freeNode(Node* pN) {
    if(pN!=NULL && *pN!=NULL){
        /* free all heap memory associated with *pN */
        free(*pN);
        *pN = NULL;
    }
}

typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int length;
    int cursorIndex;
} ListObj;

// Constructors-Destructors ---------------------------------------------------
List newList(void) {
    List temp = malloc(sizeof(ListObj));
    temp->front = temp->back = temp->cursor = NULL;
    temp->length = 0;
    temp->cursorIndex = -1;
    return temp;
}
void freeList(List* pL) {
    if(pL!=NULL && *pL!=NULL){
        /* free all heap memory associated with *pL */
        clear(*pL);
	free(*pL);
        *pL = NULL;
    }
}
// Access functions -----------------------------------------------------------
// Returns the number of elements in this List.
int length(List L) {
    return L->length;
}
// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1.
int index(List L) {
    return L->cursorIndex;
}
// Returns front element. Pre: length()>0
int front(List L) {
    return L->front->data;
}
// Returns back element. Pre: length()>0
int back(List L) {
    return L->back->data;
}
// Returns cursor element. Pre: length()>0, index()>=0
int get(List L) {
    return L->cursor->data;
}
// Returns true if this List and L are the same integer
// sequence. The cursor is ignored in both lists.
int equals(List A, List B) {
    Node tracerA = A->front;
    Node tracerB = B->front;
    while (tracerA!=NULL) {
        if (tracerA->data==tracerB->data) {
            tracerA = tracerA->next;
            tracerB = tracerB->next;
        }
        else {
            return 0;
        }
    }
    return 1;
}
// Manipulation procedures ----------------------------------------------------
// Resets this List to its original empty state.
void clear(List L) {
    //Node tracer = L->front;
    while(L->length>0) {
        // printf("Front data = %d\n", front(L));
        deleteFront(L);
        // printf("Length = %d\n",L->length);
    }
    L->front = L->back = L->cursor = NULL;
}
// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {
    if (L->length>0) {
        L->cursorIndex = 0;
        L->cursor = L->front;
    }
}
// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L) {
    if (L->length>0) {
        L->cursorIndex = L->length-1;
        L->cursor = L->back;
    }
}
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L) {
    if (L->cursor!=NULL) {
        if (L->cursorIndex>0) {
            L->cursor = L->cursor->last;
            L->cursorIndex--;
        }
        // Cursor becomes undefined if at the front of the list
        else {
            L->cursor = NULL;
            L->cursorIndex = -1;
        }
    }
}
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L) {
    if (L->cursor!=NULL) {
        if (L->cursorIndex!=L->length-1) {
            L->cursorIndex++;
            L->cursor = L->cursor->next;
        }
        // Cursor becomes undefined if at back of the list
        else {
            L->cursor = NULL;
            L->cursorIndex = -1;
        }
    }
}
// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data) {
    Node temp = newNode(data);
    // Inserting into an empty list
    if (L->length==0) {
        L->front = L->back = temp;
    }
    else {
        temp->next = L->front;
        L->front->last = temp;
        L->front = temp;
        if (L->cursorIndex!=-1) {
            L->cursorIndex++;
        }
    }
    L->length++;
}
// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data) {
    Node temp = newNode(data);
    // Appending to an empty list
    if (L->length==0) {
        L->front = L->back = temp;
    }
    else {
        temp->last = L->back;
        L->back->next = temp;
        L->back = temp;
    }
    L->length++;
}
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data) {
    Node temp = newNode(data);
    Node tracer = L->front;
    // If inserting before the first element
    if (L->cursorIndex == 0) {
        temp->next = L->front;
        L->front->last = temp;
        L->front = temp;
    }
    else {
        // Jump to correct position
        for (int i = 0; i < L->cursorIndex; i++) {
            tracer = tracer->next;
        }
        // Set up correct links for Node to be inserted
        temp->last = tracer->last;
        temp->next = tracer;
        // Set up correct links in current list to add new Node
        temp->last->next = temp;
        temp->next->last = temp;
    }
    L->cursorIndex++;
    L->length++;
}
// Inserts new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data) {
    Node temp = newNode(data);
    Node tracer = L->front;
    // Jump to correct position
    for (int i = 0; i < L->cursorIndex; i++) {
        tracer = tracer->next;
    }
    // If inserting after the last element
    if (L->cursorIndex == L->length-1) {
        temp->last = L->back;
        L->back->next = temp;
        L->back = temp;
    }
    else {
        // Set up correct links for Node to be inserted
        temp->last = tracer;
        temp->next = tracer->next;
        // Set up correct links in current list to add new Node
        tracer->next->last = temp;
        tracer->next = temp;
    }
    L->length++;
}
// Deletes the front element. Pre: length()>0
void deleteFront(List L) {
    if (L->length<1) {
        fprintf(stderr,
        "deleteFront() cannot be called on empty List\n");
        exit(EXIT_FAILURE);
    }
    Node temp = L->front;
    L->front = L->front->next;
    L->front->last = NULL;
    //temp->next = NULL;
    //temp->last = NULL;
    freeNode(&temp);
    //printf("%d ",L->length);
    //front.last = null;
    L->length--;
    // Deletes the cursor if it was the front element
    if (L->cursorIndex!=-1) {
        if (L->cursorIndex==0) {
            L->cursor = NULL;
            L->cursorIndex = -1;
        }
        L->cursorIndex--;
    }
}
// Deletes the back element. Pre: length()>0
void deleteBack(List L) {
    Node temp = L->back;
    L->back = L->back->last;
    temp->next = NULL;
    temp->last = NULL;
    freeNode(&temp);
    //back.next = null;
    L->length--;
    // Delete the cursor if it was the last element
    if (L->cursorIndex == L->length-1) {
        L->cursor = NULL;
        L->cursorIndex = -1;
    }
}
// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
    L->cursor->last->next = L->cursor->next;
    L->cursor->next->last = L->cursor->last;
    freeNode(&L->cursor);
    L->cursor = NULL;
    L->cursorIndex = -1;
    L->length--;
}
// Other operations -----------------------------------------------------------
void printList(FILE* out, List L) {
    //out = fopen(out, "w");// "w" means that we are going to write on this file
    Node tracer = L->front;
    while(tracer!=NULL) {
        fprintf(out, "%d ", tracer->data);
        tracer = tracer->next;
    }
}
// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L) {
    List tempList = newList();
    Node tracer = L->front;
    while (tracer!=NULL) {
        Node temp = newNode(tracer->data);
        append(tempList, temp->data);
        tracer = tracer->next;
    }
    return tempList;
}
// Returns a new List which is the concatenation of
// this list followed by L. The cursor in the new List
// is undefined, regardless of the states of the cursors
// in this List and L. The states of this List and L are
// unchanged.
//List concat(List L) {}
