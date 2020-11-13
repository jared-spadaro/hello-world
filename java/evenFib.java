import java.util.*;
import java.io.*;
import java.math.*;

public class evenFib {

   private static final int MAX = 4000000;
   private static int sum = 0;

   public static int fib(int n) {
      if (n == 1 || n ==2) return n;
      return fib(n-1) + fib(n-2);
   }

   public static void main(String[] args) {
      int n = 1;
      int res = fib(n);
      while (res <= MAX) {
         if (res % 2 == 0) sum += res;
         res = fib(n);
         n++;    
      }
      System.out.println("Sum = " + sum);
   }
}
