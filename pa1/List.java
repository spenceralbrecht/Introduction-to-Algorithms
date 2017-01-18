//-----------------------------------------------------------------------------
// Spencer Albrecht
// salbrech
// PA1 CS101
// List.java
// An integer list ADT
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
    private int index;
    private Node front;
    private Node back;
    private Node cursor;

    // Constructor
    List() {    // Creates a new empty list
        length = 0;
        index = -1;
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
        if (cursor!=null) {
            return index;
        } else {
            return -1;
        }
    }
    // Returns front element. Pre: length()>0
    int front() {
        if (length<=0) {
            throw new RuntimeException("Length must be greater than 0 in front() in List.java");
        }
        return front.data;

    }
    // Returns back element. Pre: length()>0
    int back() {
        if (length<=0) {
            throw new RuntimeException("Length must be greater than 0 in back() in List.java");
        }
        return back.data;
    }
    // Returns cursor element. Pre: length()>0, index()>=0
    int get() {
        if (length<=0) {
            throw new RuntimeException("Length must be greater than 0 in get() in List.java");
        }
        if (index<0) {
            throw new RuntimeException("Index must be greater than 0 in get() in List.java");
        }
        return cursor.data;
    }
    // Returns true if this List and L are the same integer
    // sequence. The cursor is ignored in both lists.
    boolean equals(List L) {
        Node tracerA = front;
        Node tracerB = L.front;
        while (tracerA!=null) {
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
        front = back = cursor = null;
        index = -1;
        length = 0;
    }
    // If List is non-empty, places the cursor under the front element,
    // otherwise does nothing.
    void moveFront() {
        if (length>0) {
            index = 0;
            cursor = front;
        }
    }
    // If List is non-empty, places the cursor under the back element,
    // otherwise does nothing.
    void moveBack() {
        if (length>0) {
            index = length-1;
            cursor = back;
        }
    }
    // If cursor is defined and not at front, moves cursor one step toward
    // front of this List, if cursor is defined and at front, cursor becomes
    // undefined, if cursor is undefined does nothing.
    void movePrev() {
        if (cursor!=null) {
            if (index>0) {
                cursor = cursor.last;
                index--;
            }
            // Cursor becomes undefined if at the front of the list
            else {
                cursor = null;
                index = -1;
            }
        }
    }
    // If cursor is defined and not at back, moves cursor one step toward
    // back of this List, if cursor is defined and at back, cursor becomes
    // undefined, if cursor is undefined does nothing.
    void moveNext() {
        if (cursor!=null) {
            if (index!=length-1) {
                index++;
                cursor = cursor.next;
            }
            // Cursor becomes undefined if at back of the list
            else {
                cursor = null;
                index = -1;
            }
        }
    }
    // Insert new element into this List. If List is non-empty,
    // insertion takes place before front element.
    void prepend(int data) {
        Node temp = new Node(data);
        // Inserting into an empty list
        if (length==0) {
            front = back = temp;
        }
        else {
            temp.next = front;
            front.last = temp;
            front = temp;
            if (index!=-1) {
                index++;
            }
        }
        length++;
    }
    // Insert new element into this List. If List is non-empty,
    // insertion takes place after back element.
    void append(int data) {
        Node temp = new Node(data);
        // Appending to an empty list
        if (length==0) {
            front = back = temp;
        }
        else {
            temp.last = back;
            back.next = temp;
            back = temp;
        }
        length++;
    }
    // Insert new element before cursor.
    // Pre: length()>0, index()>=0
    void insertBefore(int data) {
        if (length<1) {
            throw new RuntimeException("Length must be greater than 0 in insertBefore() in List.java");
        }
        if (index<0) {
            throw new RuntimeException("Cursor must be defined in insertBefore() in List.java");
        }

        Node temp = new Node(data);
        Node tracer = front;
        // If inserting before the first element
        if (index == 0) {
            temp.next = front;
            front.last = temp;
            front = temp;
        }
        else {
            // Jump to correct position
            for (int i = 0; i < index; i++) {
                tracer = tracer.next;
            }
            // Set up correct links for Node to be inserted
            temp.last = tracer.last;
            temp.next = tracer;
            // Set up correct links in current list to add new Node
            temp.last.next = temp;
            temp.next.last = temp;
        }
        index++;
        length++;

    }
    // Inserts new element after cursor.
    // Pre: length()>0, index()>=0
    void insertAfter(int data) {
        if (length<1) {
            throw new RuntimeException("Length must be greater than 0 in insertAfter() in List.java");
        }
        if (index<0) {
            throw new RuntimeException("Cursor must be defined in insertAfter() in List.java");
        }
        Node temp = new Node(data);
        Node tracer = front;
        // Jump to correct position
        for (int i = 0; i < index; i++) {
            tracer = tracer.next;
        }
        // If inserting after the last element
        if (index == length-1) {
            temp.last = back;
            back.next = temp;
            back = temp;
        }
        else {
            // Set up correct links for Node to be inserted
            temp.last = tracer;
            temp.next = tracer.next;
            // Set up correct links in current list to add new Node
            tracer.next.last = temp;
            tracer.next = temp;
        }
        length++;
    }
    // Deletes the front element. Pre: length()>0
    void deleteFront() {
        if (length<1) {
            throw new RuntimeException("length must be greater than 0 in deleteFront() in List.java");
        }
        front = front.next;
        front.last = null;
        length--;
        // Deletes the cursor if it was the front element
        if (index!=-1) {
            if (index==0) {
                cursor = null;
                index = -1;
            }
            index--;
        }
    }
    // Deletes the back element. Pre: length()>0
    void deleteBack() {
        if (length<1) {
            throw new RuntimeException("length must be greater than 0 in deleteBack() in List.java");
        }
        back = back.last;
        back.next = null;
        length--;
        // Delete the cursor if it was the last element
        if (index == length-1) {
            cursor = null;
            index = -1;
        }
    }
    // Deletes cursor element, making cursor undefined.
    // Pre: length()>0, index()>=0
    void delete() {
        if (length<1) {
            throw new RuntimeException("Length must be greater than 0 in delete() in List.java");
        }
        if (index<0) {
            throw new RuntimeException("Cursor must be defined in delete() in List.java");
        }
        cursor = null;
        index = -1;
        length--;
    }

    // Other methods
    // Overrides Object's toString method. Returns a String
    // representation of this List consisting of a space
    // separated sequence of integers, with front on left.
    public String toString() {
        Node tracer = front;
        String temp = "";
        while(tracer!=null) {
            temp+=tracer.data+" ";
            tracer = tracer.next;
        }
        return temp;
    }
    // Returns a new List representing the same integer sequence as this
    // List. The cursor in the new list is undefined, regardless of the
    // state of the cursor in this List. This List is unchanged.
    List copy() {
        List newList = new List();
        Node tracer = front;
        while (tracer!=null) {
            Node temp = new Node(tracer.data);
            newList.append(temp.data);
            tracer = tracer.next;
        }
        return newList;
    }
    // Returns a new List which is the concatenation of
    // this list followed by L. The cursor in the new List
    // is undefined, regardless of the states of the cursors
    // in this List and L. The states of this List and L are
    // unchanged.
    //List concat(List L) {}
}
