//-----------------------------------------------------------------------------
// List.java
// An integer list ADT
// PA1
// Spencer Albrecht
// salbrech@ucsc.edu
//-----------------------------------------------------------------------------

class List {
   private class Node{
      // Fields
      int data;
      Node next;
      Node last;

      // Constructor
      Node(int data) {
         this.data = data;
         next = null;
         last = null;
      }

      // toString():  overrides Object's toString() method
      public String toString() {
         return String.valueOf(data);
      }

      // equals(): overrides Object's equals() method
      public boolean equals(Object other){
         boolean equal = false;
         Node that;
         if(other instanceof Node){
            that = (Node) other;
            equal = (this.data==that.data);
         }
         return equal;
      }
   }

   // Fields
   private int length;
   private int cursor;
   private Node front;
   private Node back;

   // Constructor
   List() {    // Creates a new empty list
      length = 0;
      front = back = cursor = null;
   }
   // Access functions
   // Returns the number of elements in this List.
   int length() {
      return length;
   }
   // If cursor is defined, returns the index of the cursor element,
   // otherwise returns -1.
   int index() {
      if (cursor) {
         return cursor;
      } else {
         return -1;
      }
   }
   // Returns front element. Pre: length()>0
   int front() {
      if (length>0) {
         return front;
      } else {
         return -1;
      }
   }
   // Returns back element. Pre: length()>0
   int back() {
      if (length>0) {
         return back;
      } else {
         return -1;
      }
   }
   // Returns cursor element. Pre: length()>0, index()>=0
   int get() {
      if (length>0 && cursor>=0) {
         return cursor;
      }
   }
   // Returns true if this List and L are the same integer
   // sequence. The cursor is ignored in both lists.
   boolean equals(List L) {
      Node tracerA = front;
      Node tracerB = L.front;
      while (tracerA) {
         if (tracerA.data==tracerB.data) {
            tracerA = tracerA.next;
            tracerB = tracerB.next;
         }
         else {
            return false;
         }
      }
      return true;
   }

   // Manipulation procedures
   // Resets this List to its original empty state.
   void clear() {
      front = back = null;
      length = 0;
   }
   // If List is non-empty, places the cursor under the front element,
   // otherwise does nothing.
   void moveFront() {
      if (length>0) {
         cursor = 0;
      }
   }
   // If List is non-empty, places the cursor under the back element,
   // otherwise does nothing.
   void moveBack() {
      if (length>0) {
         cursor = length-1;
      }
   }
   // If cursor is defined and not at front, moves cursor one step toward
   // front of this List, if cursor is defined and at front, cursor becomes
   // undefined, if cursor is undefined does nothing.
   void movePrev() {
      if (cursor) {
         if (cursor!=0) {
            cursor--;
         }
         else {
            cursor = null;
         }
      }
   }
   // If cursor is defined and not at back, moves cursor one step toward
   // back of this List, if cursor is defined and at back, cursor becomes
   // undefined, if cursor is undefined does nothing.
   void moveNext() {
      if (cursor) {
         if (cursor!=length-1) {
            cursor++;
         }
         else {
            cursor = null;
         }
      }
   }
   // Insert new element into this List. If List is non-empty,
   // insertion takes place before front element.
   void prepend(int data) {
      Node temp = new Node(data);
      if (length==0) {
         front = back = temp;
      }
      else {
         temp.next = front;
         front = temp;
      }
      length++;
   }
   // Insert new element into this List. If List is non-empty,
   // insertion takes place after back element.
   void append(int data) {
      Node temp = new Node(data);
      if (length==0) {
         front = back = temp;
      }
      else {
         temp.last = back;
         back = temp;
      }
      length++;
   }
   // Insert new element before cursor.
   // Pre: length()>0, index()>=0
   void insertBefore(int data) {
      if (cursor && length>cursor) {
         Node temp = new Node(data);
         Node tracer = front;
         // Jump to correct position
         for (int i = 0; i < cursor; i++) {
            tracer = tracer.next;
         }
         if (cursor == 0) {
            temp.next = front;
            front = temp;
         }
         else {
            // Set up correct links for Node
            // to be inserted
            temp.last = tracer.last;
            temp.next = tracer;
            // Set up correct links in current
            // list to add new Node
            temp.last.next = temp;
            temp.next.last = temp;
         }
      }
   }
   // Inserts new element after cursor.
   // Pre: length()>0, index()>=0
   void insertAfter(int data) {
      if (cursor && length>cursor) {
         Node temp = new Node(data);
         Node tracer = front;
         // Jump to correct position
         for (int i = 0; i < cursor; i++) {
            tracer = tracer.next;
         }
         if (cursor == length-1) {
            temp.last = back;
            back = temp;
         }
         else {
            // Set up correct links for Node
            // to be inserted
            temp.last = tracer;
            temp.next = tracer.next;
            // Set up correct links in current
            // list to add new Node
            temp.last.next = temp;
            temp.next.last = temp;
         }
      }
   }
   // Deletes the front element. Pre: length()>0
   void deleteFront() {
      if (length>0) {
         front = front.next;
         front.last = null;
      }
   }
   // Deletes the back element. Pre: length()>0
   void deleteBack() {
      if (length>0) {
         back = back.last;
         back.next = null;
      }
   }
   // Deletes cursor element, making cursor undefined.
   // Pre: length()>0, index()>=0
   void delete() {
      if (length>0 && cursor>=0) {
         cursor = null;
      }
   }

   // Other methods
   // Overrides Object's toString method. Returns a String
   // representation of this List consisting of a space
   // separated sequence of integers, with front on left.
   public String toString() {
      Node temp = front;
      while(tracer) {
         System.out.println(tracer.data+" ");
         tracer = tracer.next;
      }
   }
   // Returns a new List representing the same integer sequence as this
   // List. The cursor in the new list is undefined, regardless of the
   // state of the cursor in this List. This List is unchanged.
   List copy() {
      List newList = new List();
      Node tracer = front;
      while (tracer) {
         Node temp = new Node(tracer.data);
         newList.append(temp);
         tracer = tracer.next;
      }
   }
   // Returns a new List which is the concatenation of
   // this list followed by L. The cursor in the new List
   // is undefined, regardless of the states of the cursors
   // in this List and L. The states of this List and L are
   // unchanged.
   //List concat(List L) {}
}
