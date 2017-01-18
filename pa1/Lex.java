//-----------------------------------------------------------------------------
// Spencer Albrecht
// salbrech
// PA1
// Lex.java
// Sort words in files alphabetically
//-----------------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;
class Lex {
    public static void main(String[] args) throws IOException {
        if(args.length!=2) {
            //throw new RuntimeException("Usage: Lex file1 file2");
            System.err.println("Usage: Lex infile outfile");
            System.exit(1);
        }
        Scanner fileIn = null;
        PrintWriter fileOut = null;
        String line = null;
        String[] fileLines = null;
        int x, lineNumber = 0;

        fileIn = new Scanner(new File(args[0]));
        fileOut = new PrintWriter(new FileWriter(args[1]));

        while( fileIn.hasNextLine() ){
            lineNumber++;
            fileIn.nextLine();
            // line = in.nextLine()+" ";    // add extra space so split works right
            // token = line.split("\\s+");  // split line around white space
            // n = token.length;
            // out.println("Line "+lineNumber+" contains "+n+" token"+(n==1?"":"s")+":");
            // for(i=0; i<n; i++){
            //     out.println(token[i]);
            // }
            // out.println();
        }

        fileIn.close();
        fileIn = new Scanner(new File(args[0]));

        fileLines = new String[lineNumber];
        for (int i = 0; i < lineNumber; i++) {
            fileLines[i] = fileIn.nextLine();
            //System.out.println(fileLines[i]);
        }

        List tempList = new List();
        for (int i = 0; i < lineNumber; i++) {
            // Add the first element to the list without any
            // comparison needed
            if (i==0) {
                // Add the first element and put the cursor on it
                tempList.prepend(i);
                //System.out.println("line 55 ran");
                System.out.print("tempList length = ");
                System.out.println(tempList.length());
                //tempList.moveFront();
                System.out.println("index ==$== "+tempList.index());
            }
            else {
                int j = i-1;
                // Move the cursor to the back for the comparisons
                tempList.moveBack();
                System.out.println("i ====== "+i);
                System.out.println("j ====== "+j);
                // If it comes before fileLines[i-1]
                System.out.println("fileLines[i] = "+fileLines[i]);
                System.out.println("fileLines[j] = "+fileLines[j]);
                // We need to compare to tempList[i]
                // Move the cursor to the right spot
                while(j>=0 && fileLines[i].compareTo(fileLines[tempList.get()])<0) {
                    System.out.println("i = "+i);
                    System.out.println("j = "+j);
                    // System.out.println("fileLines[i] inside loop = "+fileLines[i]);
                    // System.out.println("fileLines[j] inside loop = "+fileLines[j]);

                    tempList.movePrev();


                    j--;
                    System.out.println("j after decrementing = "+j);
                }
                // System.out.println("fileLines[i] outside loop = "+fileLines[i]);
                // System.out.println("fileLines[j] outside loop = "+fileLines[j]);
                // j is now at the correct spot to insertAfter
                // Make sure the cursor is at the front and then move
                // the cursor to the correct spot for insertion
                tempList.moveFront();
                // If we are supposed to insert at the beginning
                if (j==-1) {
                    tempList.insertBefore(i);
                }
                else {
                    for (int k = 0; k<j; k++) {
                        tempList.moveNext();
                    }
                    tempList.insertAfter(i);
                }

                // if (j==-1) {
                //     tempList.prepend(i);
                //     System.out.println("Line 66 ran");
                //     //System.out.print("tempList length = ");
                //     //System.out.println(tempList.length());
                // }
                // else {
                //     tempList.insertAfter(i);
                //     System.out.println("Line 70 ran");
                //     System.out.print("tempList length = ");
                //     System.out.println(tempList.length());
                // }
                // for (int k = 0; k < i; k++) {
                //
                // }
                // tempList.moveNext();
                // System.out.println("index ==== "+tempList.index());
            }

        }

        // Prints the correct output to the file
        tempList.moveFront();
        System.out.println(tempList.length());
        while(tempList.index()>=0){
            //System.out.println("line 80 ran");
            x = tempList.get();
            // Prints the correct array element
            // based on the sorted List
            fileOut.println(fileLines[x]);
            tempList.moveNext();
            //System.out.print("tempList index is ");
            //System.out.println(tempList.index());
        }

        fileIn.close();
        fileOut.close();
    }
}
