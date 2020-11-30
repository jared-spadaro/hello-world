import java.util.*;

public class exp {

   public static int power (int x, int y) {
      int i = x, j = y-1, result = 0, temp = x, z = x;
      while (j-- > 0) {
         temp = z;
         i = x;
         result = 0;
       	 while (i-- > 0) {
            result += temp;
            z = result;
         }
         //i = x;
         //temp = result;
      }
      
      return result;
   }

   public static void main (String[] args) {
      System.out.println("Result = " + power(2,10));
   }

}
