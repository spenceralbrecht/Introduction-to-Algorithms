//-----------------------------------------------------------------------------
// Spencer Albrecht
// salbrech
// PA1 CS101
// Lex.java
// Sort words in files alphabetically
//-----------------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;
class Lex {
    public static void main(String[] args) throws IOException {
        if(args.length!=2) {
            System.err.println("Usage: Lex infile outfile");
            System.exit(1);
        }
        // Fields
        Scanner fileIn = null;
        PrintWriter fileOut = null;
        String line = null;
        String[] fileLines = null;
        int x, lineNumber = 0;

        fileIn = new Scanner(new File(args[0]));
        fileOut = new PrintWriter(new FileWriter(args[1]));

        // Count the number of lines in the file
        while( fileIn.hasNextLine() ){
            lineNumber++;
            fileIn.nextLine();
        }

        // Close the file and open it again to read the
        // actual content
        fileIn.close();
        fileIn = new Scanner(new File(args[0]));

        // Read in the lines of the file
        fileLines = new String[lineNumber];
        for (int i = 0; i < lineNumber; i++) {
            fileLines[i] = fileIn.nextLine();
        }

        // Correctly insert indices into tempList
        List tempList = new List();
        for (int i = 0; i < lineNumber; i++) {
            // Add the first element to the list without any
            // comparison needed
            if (i==0) {
                // Add the first element and put the cursor on it
                tempList.prepend(i);
            }
            else {
                int j = i-1;
                // Move the cursor to the back for start of comparisons
                tempList.moveBack();
                // Compares the words in the file to the indices of tempList
                while(j>=0 && fileLines[i].compareTo(fileLines[tempList.get()])<0) {
                    tempList.movePrev();
                    j--;
                }

                tempList.moveFront();
                // If we are supposed to insert before the first element
                if (j==-1) {
                    tempList.insertBefore(i);
                }
                else {
                    // Move the cursor to the correct spot for insertion
                    for (int k = 0; k<j; k++) {
                        tempList.moveNext();
                    }
                    tempList.insertAfter(i);
                }
            }

        }

        // Prints the correct output to the file based on the list
        tempList.moveFront();
        while(tempList.index()>=0){
            x = tempList.get();
            // Prints the correct array element
            // based on the sorted List
            fileOut.println(fileLines[x]);
            tempList.moveNext();
        }

        fileIn.close();
        fileOut.close();
    }
}
