import java.util.*;
import java.io.*;
import java.math.*;
import java.lang.*;


public class Palindrome {

   private final static int MAX = 999;

   public static String pal() { 
      //start with largest possible combination, and move downwards
      int arg1 = MAX, arg2 = MAX;
      for (int i = 0; i < MAX; i++) {
         arg2 = MAX;
         for (int j = 0; j < MAX; j++) {
            String product = Integer.toString(arg1 * arg2);
            StringBuilder sb = new StringBuilder(product);
            String reverseProduct = sb.reverse().toString();
            if (product.equals(reverseProduct)) {
               return product + " (" + arg1 + " * " + arg2 + ")";
            }
            if (arg2 == 900) break;
            arg2--;
         }
         arg1--;
      }   
      return null;
   }

   public static void main(String[] args) {
      System.out.println("Largest palindrome made from product of two 3-digit numbers = " + pal());
   }
}
