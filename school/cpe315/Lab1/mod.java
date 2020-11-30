import java.util.*;

public class mod {
   
   public static int mod(int num, int div) {
      return num & div-1;
   }

   public static int parity(int num) {
      int parity = 1;

      while (num != 0) {
         parity = parity ^ (num & 1);
         num >>= 1;
      }

      return parity; 
   }

   public static void main(String[] args) {
      int remainder, num, div;
      Scanner input;

      input = new Scanner(System.in);
      System.out.println("Input a number, then a divisor");
      num = input.nextInt();      
      div = input.nextInt();

      System.out.println("Result = " + mod(num, div));

      System.out.println("Input a number");
      num = input.nextInt();
      
      System.out.println("Result = " + parity(num));
   }
}
