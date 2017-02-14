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
      // Creates array of empty List elements
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
         // If the matrices don't have the same size or number
         // of elements then return false
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
   // Sets this Matrix to the zero state
   void makeZero() {
      this.size = 0;
      for(int i = 0; i < this.getSize()+1; i++) {
         this.rows[i+1].clear();
      }
      this.numNonZero = 0;
   }

   // Returns a new Matrix having the same entries as this Matrix
   // Must use changeEntry()
   Matrix copy() {
      Matrix resultMatrix = new Matrix(this.getSize());
      for (int i = 1; i < this.getSize(); i++) {
          this.rows[i].moveFront();
          for (int j = 0; j < this.rows[i].length(); j++) {
              Entry temp = (Entry) this.rows[i].get();
              resultMatrix.changeEntry(i, temp.column, temp.value);
              this.rows[i].moveNext();
          }

      }
      return resultMatrix;
   }

   // Changes ith row, jth column of this Matrix to x
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
      // If the row doesn't have any elements we don't have to do anything
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

         // If the columns are equal we just change the data value
         if (columnAtPosition==colNum) {
            // Delete the Node if it is in the correct position and the
            // value to be inserted is 0
            if (insertValue==0 && valueAtPosition!=0) {
               this.rows[rowNum].delete();
               this.numNonZero--;
            }
            // Change the value of the Node if it has the same colNum
            if (insertValue!=0 && valueAtPosition!=0) {
               temp.value = insertValue;
            }
         }
         else {
            // If the value to be inserted isn't 0
            if (insertValue!=0) {
                Entry insertEntry = new Entry(colNum, insertValue);
                this.rows[rowNum].insertAfter(insertEntry);
                this.numNonZero++;
            }
         }
      }
      // List at row is empty
      else {
         // Insert the entry is the value isn't zero
         if (insertValue!=0) {
            Entry insertEntry = new Entry(colNum, insertValue);
            this.rows[rowNum].prepend(insertEntry);
            this.numNonZero++;
         }
      }
   }

   // Returns a new Matrix that is the scalar product of this Matrix with x
   Matrix scalarMult(double scalar) {
      Matrix tempMatrix = new Matrix(this.getSize());
      for (int i = 1; i <= this.getSize(); i++) {
         List currentList = this.rows[i];
         // Only look as lists that aren't empty
         if (currentList.length()>0) {
            currentList.moveFront();
            // Loop that iterates through each list
            for (int j = 0; j < currentList.length(); j++) {
               Entry currentEntry = (Entry) currentList.get();
               tempMatrix.changeEntry(i,j+1,scalar*currentEntry.value);
               currentList.moveNext();
            }
         }
      }
      return tempMatrix;
   }

   List addList(List list, List secondList) {
       int totalElements = list.length()+secondList.length();
       List newList = new List();
       if (totalElements > 0) {
           // Create a copy of the list just in case the two lists are
           // actually the same list
           List firstList = list.copy();
           int counter = 0;
           firstList.moveFront();
           secondList.moveFront();
           // Runs until one or both lists have no elements left
           while (firstList.index()!=-1 && secondList.index()!=-1) {
               Entry entryOne = (Entry) firstList.get();
               Entry entryTwo = (Entry) secondList.get();
               // If the columns are equal we add the values
               if (entryOne.column==entryTwo.column) {
                  double newValue = entryOne.value+entryTwo.value;
                  Entry newEntry = new Entry(entryOne.column, newValue);
                  newList.append(newEntry);
                  firstList.moveNext();
                  secondList.moveNext();
              }
              // If the first entry has a lower column than the second entry
              // we add it to our new list
              else if (entryOne.column < entryTwo.column) {
                 Entry newEntry = new Entry(entryOne.column, entryOne.value);
                 newList.append(newEntry);
                 firstList.moveNext();
             }
             // If the second entry has a lower column than the first entry
             // we add it to our new list
             else {
                 Entry newEntry = new Entry(entryTwo.column, entryTwo.value);
                 newList.append(newEntry);
                 secondList.moveNext();
             }
           }
           // At this point one list will have no elements left
           while (firstList.index()!=-1 || secondList.index()!=-1) {
               // If the second list still has elements
               if (secondList.index()!=-1) {
                    Entry entryTwo = (Entry) secondList.get();
                    Entry newEntry = new Entry(entryTwo.column, entryTwo.value);
                    newList.append(newEntry);
                    secondList.moveNext();
               }
               // If the first list still has elements
               else {
                    Entry entryOne = (Entry) firstList.get();
                    Entry newEntry = new Entry(entryOne.column, entryOne.value);
                    newList.append(newEntry);
                    firstList.moveNext();
               }
           }
       }
       return newList;
   }
   // returns a new Matrix that is the sum of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix add(Matrix M) {
      if (this.getSize()!=M.getSize()) {
         throw new RuntimeException("Sizes must match in add() in Matrix.java");
      }
      Matrix resultMatrix = new Matrix(this.getSize());
      for (int i = 1; i < this.getSize()+1; i++) {
          List thisList = this.rows[i];
          List otherList = M.rows[i];
          List resultList = addList(thisList, otherList);
          resultList.moveFront();
          // Loops through the new list and adds the values to the new matrix
          for (int j = 0; j < resultList.length(); j++) {
              Entry temp = (Entry) resultList.get();
              resultMatrix.changeEntry(i, temp.column, temp.value);
              resultList.moveNext();
          }
      }
      return resultMatrix;
   }

   // returns a new Matrix that is the difference of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix sub(Matrix M) {
       if (this.getSize()!=M.getSize()) {
          throw new RuntimeException("Sizes must match in sub() in Matrix.java");
       }
       Matrix resultMatrix = this.add(M.scalarMult(-1.0));
       return resultMatrix;
   }

   // returns a new Matrix that is the transpose of this Matrix
   Matrix transpose() {
       Matrix resultMatrix = new Matrix(this.getSize());
       for (int i = 1; i <= this.getSize(); i++) {
           this.rows[i].moveFront();
           for (int j = 0; j < this.rows[i].length(); j++) {
               Entry temp = (Entry) this.rows[i].get();
               resultMatrix.changeEntry(temp.column, i, temp.value);
               this.rows[i].moveNext();
           }
       }
       return resultMatrix;
   }

   // Returns a double that is the dot product of the row in this Matrix
   // with the correct column number in the other Matrix
   double dot(List firstList, List secondList) {
      double sum = 0.0;
      firstList.moveFront();
      secondList.moveFront();
      // Only runs while both lists have elements
      while (firstList.index()!=-1 && secondList.index()!=-1) {
          Entry entryOne = (Entry) firstList.get();
          Entry entryTwo = (Entry) secondList.get();
          // If the column's of the entries are equal multiply them
          // and add them to the sum
          if (entryOne.column==entryTwo.column) {
             sum += entryOne.value*entryTwo.value;
             firstList.moveNext();
             secondList.moveNext();
         }
         else if (entryOne.column < entryTwo.column) {
            firstList.moveNext();        }
        else {
            secondList.moveNext();
        }
      }
      return sum;
   }

   // returns a new Matrix that is the product of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix mult(Matrix M) {
      if (this.getSize()!=M.getSize()) {
         throw new RuntimeException("Sizes must match in mult() in Matrix.java");
      }
      Matrix resultMatrix = new Matrix(this.getSize());
      Matrix transposed = M.transpose();
      // Loop that runs through the columns of the first matrix
      for (int i = 1; i <= this.getSize(); i++) {
         // Only looks through the the list if the length > 0
         if (this.rows[i].length()>0) {
            for (int j = 1; j <= transposed.getSize(); j++) {
               int listOneSize = this.rows[i].length();
               int listTwoSize = transposed.rows[j].length();
               // If both lists have elements take the dot product and
               // enter it into the correct place
               if (listOneSize>0 && listTwoSize>0) {
                  double newValue = dot(this.rows[i],transposed.rows[j]);
                  resultMatrix.changeEntry(i, j, newValue);
               }
            }
         }
      }
      return resultMatrix;
   }

   // Other functions
   // overrides Object's toString() method
   public String toString() {
      String output = "";
      for (int i = 1; i < this.getSize()+1; i++) {
         if (this.rows[i].length()>0) {
            output+=i+": "+this.rows[i].toString()+"\n";
         }
      }
      return output;
   }
}
