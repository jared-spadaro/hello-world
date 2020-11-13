import java.io.*;
import java.lang.*;
import java.math.*;

public class multThreeFive {

   private static final int MAX = 1000;
   
   public static int sum() {
      int i, divByThree = 0, divByFive = 0;
      for (i = 0; i < MAX; i++) {
         if (i % 3 == 0) divByThree += i;
         if (i % 5 == 0) divByFive += i;
      }
      return divByThree + divByFive;
   }

   public static void main(String[] args) {
      System.out.println("The answer is " + sum());
   }
}
