import java.util.*;
import java.io.*;
import java.math.*;

private static final MAX = 2000000;

public class primeSum {

   public static boolean isPrime(long n) {
      for (long i = 2; i < n/2; i++) {
         if (n % i == 0) return false;
      }
      return true;
   }

   public static long primeSum() {
      long sum = 0;
      for (long i = 2; i < MAX; i++) {
         if (isPrime(i)) {
             sum += i;
         }
      }
      return sum;
   }

   public static void main(String[] args) {
      System.out.print("Sum of all primes below 2 million: " + primeSum());
   }
}
