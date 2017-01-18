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
            if (i==0) {
                // Add the first element and put the cursor on it
                tempList.prepend(i);
                tempList.moveFront();
            }
            else {
                int j = i-1;
                // If it comes before fileLines[i-1]
                while(j>= 0 && fileLines[i].compareTo(fileLines[j])<0) {
                    j--;
                    tempList.movePrev();
                }
                if (j==-1) {
                    tempList.prepend(i);
                }
                else {
                    tempList.insertAfter(i);
                }
                tempList.moveNext();
            }

        }

        // Prints the correct output to the file
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
