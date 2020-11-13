import java.util.*;
import java.io.*;
import java.math.*;

public class primeSum {

   private static final int MAX = 2000000;

   public static boolean isPrime(long n) {
      for (long i = 2; i < n/2; i++) {
         if (n % i == 0) return false;
      }
      return true;
   }

   public static long primeSum() {
      long sum = 0;
      for (long i = 2; i < MAX; i++) {
        if (i % 2 == 0 || i % 3 == 0 || i % 4 == 0 || i % 5 == 0 || 
              i % 6 == 0 || i % 7 == 0 || i % 8 == 0 || i % 9 == 0) {} 
        else if (isPrime(i)) {
            System.out.println("Found prime " + i);
            sum += i;
        }
        else {}
      }
      return sum;
   }

   public static void main(String[] args) {
      System.out.print("Sum of all primes below 2 million: " + primeSum());
   }
}
