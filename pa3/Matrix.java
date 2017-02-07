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
         this.column = column;
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
      return this.rows.length()-1;
   }

   // Returns the number of non-zero entries in this Matrix
   int getNNZ() {
      return numNonZero;
   }

   // overrides Object's equals() method
   public boolean equals(Object other) {
      // check num rows and the checks list
      boolean equal = false;
      Entry that;
      if(other instanceof Entry){
         that = (Entry) other;
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
               if (!this.rows[i+1].equals(that.rows[i+1]) {
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
      // Case 2
      // Move to the correct position
      this.rows[rowNum].moveFront();
      for (int i = 1; i < colNum; i++) {
         this.rows[rowNum].moveNext();
      }

      Entry temp = (Entry) this.rows[rowNum].get()
      int valueAtPosition = temp.value;

      // Case 2
      if (insertValue==0 && valueAtPosition!=0) {
         // Delete the Node at the correct position
         this.rows[rowNum].delete();
         this.numNonZero--;
      }
      else if (insertValue!=0) {
         if (valueAtPosition==0) {
            Entry tempEntry = new Entry(rowNum,colNum,insertValue);
            this.rows[rowNum].insert(tempEntry);
         }
         else {
            this.rows[rowNum].get().value = insertValue;
         }

      }



      // Case 3
      if (value!=0 && ) {

      }
   }

   // returns a new Matrix that is the scalar product of this Matrix with x
   Matrix scalarMult(double x) {

   }

   // returns a new Matrix that is the sum of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix add(Matrix M) {
   }

   // returns a new Matrix that is the difference of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix sub(Matrix M) {
   }

   // returns a new Matrix that is the transpose of this Matrix
   Matrix transpose() {

   }

   // returns a new Matrix that is the product of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix mult(Matrix M) {

   }

   // Other functions
   // overrides Object's toString() method
   public String toString() {

   }

}
