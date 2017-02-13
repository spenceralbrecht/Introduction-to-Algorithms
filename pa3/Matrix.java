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
            this.numNonZero++;
         }
      }


   }

   // returns a new Matrix that is the scalar product of this Matrix with x
   Matrix scalarMult(double scalar) {
      Matrix tempMatrix = new Matrix(this.getSize());
      for (int i = 1; i < this.getSize(); i++) {
         List currentList = this.rows[i];
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
           //System.out.println("total elements = "+totalElements);
           //System.out.println("first list = "+firstList.toString());
           //System.out.println("second list = "+secondList.toString());
           int counter = 0;
           firstList.moveFront();
           secondList.moveFront();
           // Runs until one or both lists have no elements left
           while (firstList.index()!=-1 && secondList.index()!=-1) {
               Entry entryOne = (Entry) firstList.get();
               Entry entryTwo = (Entry) secondList.get();
               //System.out.println("index for both lists = "+firstList.index());
               if (entryOne.column==entryTwo.column) {
                  double newValue = entryOne.value+entryTwo.value;
                  Entry newEntry = new Entry(entryOne.column, newValue);
                  newList.append(newEntry);
                  firstList.moveNext();
                  secondList.moveNext();
              }
              else if (entryOne.column < entryTwo.column) {
                 //System.out.println("line 222");
                 Entry newEntry = new Entry(entryOne.column, entryOne.value);
                 newList.append(newEntry);
                 firstList.moveNext();
                 //counter++;
             }
             else {
                 //System.out.println("line 229");
                 Entry newEntry = new Entry(entryTwo.column, entryTwo.value);
                 newList.append(newEntry);
                 secondList.moveNext();
                 //counter++;
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
           //System.out.println("new list = "+newList.toString());
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
          //System.out.println("this list = "+thisList.toString());
          //System.out.println("other list = "+otherList.toString());
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
