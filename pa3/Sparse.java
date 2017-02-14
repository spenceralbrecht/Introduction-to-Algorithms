import java.util.Scanner;
import java.io.*;
class Sparse {
   public static void main(String[] args) throws IOException {
      if(args.length!=2) {
            System.err.println("Usage: Sparse infile outfile");
            System.exit(1);
        }
        // Fields
        Scanner fileIn = null;
        PrintWriter fileOut = null;
        String[] specifics = null;
        int size, numEntriesOne, numEntriesTwo;
        fileIn = new Scanner(new File(args[0]));
        fileOut = new PrintWriter(new FileWriter(args[1]));
        specifics = fileIn.nextLine().split(" ");
        // Store the results of the first line of the input file
        size = Integer.parseInt(specifics[0]);
        numEntriesOne = Integer.parseInt(specifics[1]);
        numEntriesTwo = Integer.parseInt(specifics[2]);
        // Skip a line
        fileIn.nextLine();
        Matrix A = new Matrix(size);
        Matrix B = new Matrix(size);
        // Loop that fills matrix A
        for (int i = 0; i < numEntriesOne; i++) {
           String[] input = fileIn.nextLine().split(" ");
           A.changeEntry(Integer.parseInt(input[0]), Integer.parseInt(input[1]), Double.parseDouble(input[2]));
        }
        fileIn.nextLine();
        // Loop that fills matrix B
        for (int i = 0; i < numEntriesTwo; i++) {
           String[] input = fileIn.nextLine().split(" ");
           B.changeEntry(Integer.parseInt(input[0]), Integer.parseInt(input[1]), Double.parseDouble(input[2]));
        }

       // Output for the matrix operations
       fileOut.println("A has "+A.getNNZ()+" non-zero entries:");
       fileOut.println(A);

       fileOut.println("B has "+B.getNNZ()+" non-zero entries:");
       fileOut.println(B);

       fileOut.println("(1.5)*A = ");
       Matrix C = A.scalarMult(1.5);
       fileOut.println(C);

       fileOut.println("A+B = ");
       fileOut.println(A.add(B));

       fileOut.println("A+A = ");
       fileOut.println(A.add(A));

       fileOut.println("B-A = ");
       fileOut.println(B.sub(A));

       fileOut.println("A-A = ");
       fileOut.println(A.sub(A));

       fileOut.println("Transpose(A) = ");
       fileOut.println(A.transpose());

       fileOut.println("A*B = ");
       fileOut.println(A.mult(B));

       fileOut.println("B*B = ");
       fileOut.println(B.mult(B));

       fileOut.close();
       fileIn.close();
   }
}
