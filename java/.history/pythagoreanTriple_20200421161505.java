import java.util.*;
import java.io.*;
import java.math.*;

public class pythagoreanTriple {

   public static double find() {
      double a = 3, b = 4, c, sum, sum2;
      //loop until we find the answer
      while (b < 500) {
         while (a < 500) {
            sum = Math.pow(a,2) + Math.pow(b,2);
            //check if sum is perfect square
            if (Math.sqrt(sum) - Math.floor(Math.sqrt(sum)) == 0) {
               System.out.println("Found perfect square sum (" + sum + ")");
               //get c
               c = Math.sqrt(sum);
               sum2 = a + b + c;
               System.out.println("a = " + a + ", b = " + b + ", c = " + c + ", sum = " + sum2);
               //check if sum of a,b,c is 1000
               if (a + b + c == 1000) {
                  return a * b * c;
               }
            }
            a++;
         }
         a = 3;
         b++;
      }
      return 0;
   }

   public static void main(String[] args) {
      System.out.println("The produc abc such that a + b + c = 1000 and a^2 + b^2 = c^2 is " + find() + ".");
   }
}
