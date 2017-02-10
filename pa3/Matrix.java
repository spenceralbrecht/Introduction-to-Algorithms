//-----------------------------------------------------------------------------
// Spencer Albrecht
// salbrech
// PA3 CS101
// Matrix.java
// An List Matrix ADT
//-----------------------------------------------------------------------------
public class Matrix {
   private class Entry {
      int column;
      double value;

      // Constructor
      Entry(int col, double val) {
         this.column = col;
         this.value = val;
      }

      public boolean equals(Object other) {
         boolean equal = false;
         Entry that;
         if(other instanceof Entry){
            that = (Entry) other;
            equal = (this.column==that.column) && (this.value==that.value);
         }
         return equal;
      }

      public String toString() {
         String returnString;
         returnString = "("+this.column+", "+this.value+")";
         return returnString;
      }
   }

   // Fields for the Matrix class
   //private int rows;
   private List[] rows;
   private int numNonZero;
   private int size;

   // Constructor
   // Makes a new n x n zero Matrix. pre: n>=1
   Matrix(int n) {
      if (n<1) {
         throw new RuntimeException("Size must be greater than 0 in Matrix Constructor in Matrix.java");
      }
      // Creates array of List elements
      this.rows = new List[n+1];
      this.size = n;
      this.numNonZero = 0;
      for (int i = 0; i < this.getSize(); i++) {
         this.rows[i+1]= new List();
      }
   }
   // Access functions
   // Returns n, the number of rows and columns of this Matrix
   int getSize() {
      return this.size;
   }

   // Returns the number of non-zero entries in this Matrix
   int getNNZ() {
      return numNonZero;
   }

   // overrides Object's equals() method
   public boolean equals(Object other) {
      // check num rows and the checks list
      boolean equal = false;
      Matrix that;
      if(other instanceof Matrix){
         that = (Matrix) other;
         if (this.getSize()!=that.getSize()) {
            return false;
         }
         else if (this.numNonZero!=that.numNonZero) {
            return false;
         }
         else {
            for (int i = 0; i < this.getSize(); i++) {
               // Adds one because we don't use the first row
               // Compares each List using List equals method
               if (!this.rows[i+1].equals(that.rows[i+1])) {
                  return false;
               }
            }
            equal = true;
         }
      }
      return equal;
   }

   // Manipulation procedures
   // sets this Matrix to the zero state
   void makeZero() {
      this.size = 0;
      for(int i = 0; i < this.getSize()+1; i++) {
         this.rows[i+1].clear();
      }
   }

   // returns a new Matrix having the same entries as this Matrix
   // Must use changeEntry()
   Matrix copy() {
      Matrix newMatrix = new Matrix(this.getSize());
      for(int i = 0; i < this.getSize()+1; i++) {
         List tempList = this.rows[i+1].copy();
         newMatrix.rows[i+1] = tempList;
      }
      return newMatrix;
   }

   // changes ith row, jth column of this Matrix to x
   // pre: 1<=i<=getSize(), 1<=j<=getSize()
   void changeEntry(int rowNum, int colNum, double insertValue) {
      if (rowNum<1) {
         throw new RuntimeException("Row number must be greater than 1 in changeEntry() in Matrix.java");
      }
      if (rowNum>this.getSize()) {
         throw new RuntimeException("Row number must be less than Matrix size in Matrix.java");
      }
      if (colNum<1) {
         throw new RuntimeException("Column number must be greater than 1 in changeEntry() in Matrix.java");
      }
      if (colNum>this.getSize()) {
         throw new RuntimeException("Column number must be less than Matrix size in Matrix.java");
      }

      if (this.rows[rowNum].length()>0) {
         this.rows[rowNum].moveFront();
         List currentList = this.rows[rowNum];
         // Move to correct column number
         while (colNum > ((Entry) currentList.get()).column) {
            currentList.moveNext();
            if (currentList.index()==-1) {
               currentList.moveBack();
               break;
            }

         }
         // Store the column number and value of the Node we are at
         Entry temp = (Entry) this.rows[rowNum].get();
         double valueAtPosition = temp.value;
         int columnAtPosition = temp.column;

         // Case 2
         if (columnAtPosition==colNum) {
            // Delete the Node if it is in the correct position
            if (insertValue==0 && valueAtPosition!=0) {
               // Delete the Node at the correct position
               this.rows[rowNum].delete();
               this.numNonZero--;
            }
            // Change the value of the Node if it has the same colNum
            if (insertValue!=0 && valueAtPosition!=0) {
               temp.value = insertValue;
            }
         }
         else {
            Entry insertEntry = new Entry(colNum, insertValue);
            this.rows[rowNum].insertAfter(insertEntry);
            this.numNonZero++;
         }
      }
      // List at row is empty
      else {
         // Insert the entry is the value isn't zero
         if (insertValue!=0) {
            Entry insertEntry = new Entry(colNum, insertValue);
            this.rows[rowNum].prepend(insertEntry);
         }
      }


   }

   // returns a new Matrix that is the scalar product of this Matrix with x
   // Matrix scalarMult(double x) {
   //
   // }
   //
   // // returns a new Matrix that is the sum of this Matrix with M
   // // pre: getSize()==M.getSize()
   // Matrix add(Matrix M) {
   // }
   //
   // // returns a new Matrix that is the difference of this Matrix with M
   // // pre: getSize()==M.getSize()
   // Matrix sub(Matrix M) {
   // }
   //
   // // returns a new Matrix that is the transpose of this Matrix
   // Matrix transpose() {
   //
   // }
   //
   // // returns a new Matrix that is the product of this Matrix with M
   // // pre: getSize()==M.getSize()
   // Matrix mult(Matrix M) {
   //
   // }

   // Other functions
   // overrides Object's toString() method
   public String toString() {
      String output = "";
      //int iterator = 1;
      for (int i = 1; i < this.getSize(); i++) {
         if (this.rows[i].length()>0) {
            output+=i+": "+this.rows[i].toString()+"\n";
         }
      }
      return output;
   }

}
