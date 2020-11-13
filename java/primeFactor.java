import java.util.*;
import java.io.*;
import java.math.*;

public class primeFactor {

   public static boolean isPrime(long n) {
      for (long i = 2; i < n/2; i++) {
         if (n % i == 0) return false;
      }
      return true;
   }

   public static ArrayList<Long> findFactors(long n) {
      ArrayList<Long> factors = new ArrayList<Long>();
      for (long i = 2; i < n/2; i++) {
         if (n % i == 0) factors.add(i);
      }
      return factors;
   }

   public static long largestPrimeFactor(long n) {
      long res = 0;
      ArrayList<Long> factors = findFactors(n);
      for (long i = 0; i < factors.size(); i++) {
         if (isPrime(factors.get((int)i)) && factors.get((int)i) > res) {
            res = factors.get((int)i);
         }
      }
      return res;
   }

   public static void main(String[] args) {
      Scanner sc = new Scanner(System.in);
      System.out.print("Enter number to find largest prime factor: ");
      long in = sc.nextLong();
      System.out.println("Largest prime factor of " + in + " is " + largestPrimeFactor(in) + ".");
   }
}
