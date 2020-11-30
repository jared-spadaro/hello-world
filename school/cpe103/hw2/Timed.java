// Program by Jared Spadaro
// CPE 103 with Professor Buckalew
// 10/17/13

import java.util.Random;
import java.util.Arrays;

public class Timed {
  
  //This method calls Init_Array and runs time tests
  public static void TimeTest (int arraySize, String sortType, String arrayType) {
    long start,end;                                      //Variables for time tracking
    Comparable[] Small_Array;                            
    Comparable[] Medium_Array;
    Comparable[] Large_Array;
    if(sortType.equals("linear")) {                      //If method is called with linear
      if(arraySize==1000) {                              //If method is called with 1000 array size
        Small_Array = Init_Array(arraySize,arrayType);   //Initialize array
        start = System.currentTimeMillis();              //Take time at start
        InsertionTest.sortLinear(Small_Array);           //Sort array
        end = System.currentTimeMillis();                //Take time at end
        System.out.println("1000 Objects, " + arrayType + ", Linear Search: " + (end-start) + " milliseconds");
      }
      else if(arraySize==10000) {                   
        Medium_Array = Init_Array(arraySize,arrayType);
        start = System.currentTimeMillis();
        InsertionTest.sortLinear(Medium_Array);
        end = System.currentTimeMillis();
        System.out.println("10000 Objects, " + arrayType + ", Linear Search: " + (end-start) + " milliseconds");
      }
      else if(arraySize==100000) {
        Large_Array = Init_Array(arraySize,arrayType);
        start = System.currentTimeMillis();
        InsertionTest.sortLinear(Large_Array);
        end = System.currentTimeMillis();
        System.out.println("100000 Objects, " + arrayType + ", Linear Search: " + (end-start) + " milliseconds");
      }
    }
    else if(sortType.equals("binary")) {
      if(arraySize==1000) {
        Small_Array = Init_Array(arraySize,arrayType); 
        start = System.currentTimeMillis();
        InsertionTest.sortBinary(Small_Array);
        end = System.currentTimeMillis();
        System.out.println("1000 Objects, " + arrayType + ", Binary Search: " + (end-start) + " milliseconds");
      }
      else if(arraySize==10000) {
        Medium_Array = Init_Array(arraySize,arrayType);
        start = System.currentTimeMillis();
        InsertionTest.sortBinary(Medium_Array);
        end = System.currentTimeMillis();
        System.out.println("10000 Objects, " + arrayType + ", Binary Search: " + (end-start) + " milliseconds");
      }
      else if(arraySize==100000) {
        Large_Array = Init_Array(arraySize,arrayType);
        start = System.currentTimeMillis();
        InsertionTest.sortBinary(Large_Array);
        end = System.currentTimeMillis();
        System.out.println("100000 Objects, " + arrayType + ", Binary Search: " + (end-start) + " milliseconds");
      }
    }
  }


  public static Comparable[] Init_Array (int arraySize, String arrayType) {
    int i,j;
    Comparable[] Small_Array = new Comparable[1000];      //Initialize arrays
    Comparable[] Medium_Array = new Comparable[10000];
    Comparable[] Large_Array = new Comparable[100000];
    Random random = new Random();                         //Create new instance of random
    if(arraySize==1000) {                               
      if(arrayType.equals("Random Order")) {              //If method is called with Random Order
        for(i=0;i<arraySize;i++) {                        //Fill array with random numbers
          Small_Array[i] = random.nextInt();
        }
        return Small_Array;                               
      }
      else if(arrayType.equals("In Order")) {
        for(i=0;i<arraySize;i++) {                        //Fill array with numbers in order
          Small_Array[i] = new Integer(i);
        }
        return Small_Array;
      }
      else if(arrayType.equals("Reverse Order")) {        //Fill array with numbers in reverse order
        j=0;
        for(i=arraySize-1;i>=0;i--) {
          Small_Array[j] = new Integer(i);
          j++;                                            //Variable "j" is used to attain reverse order 
        }                                                 //(if "i" was used, would be in order)
        return Small_Array;
      }
    }
    else if(arraySize==10000) {
      if(arrayType.equals("Random Order")) {
        for(i=0;i<arraySize;i++) {
          Medium_Array[i] = random.nextInt();
        }
        return Medium_Array;
      }
      else if(arrayType.equals("In Order")) {
        for(i=0;i<arraySize;i++) {
          Medium_Array[i] = new Integer(i);
        }
        return Medium_Array;
      }
      else if(arrayType.equals("Reverse Order")) {
        j=0;
        for(i=arraySize-1;i>=0;i--) {
          Medium_Array[j] = new Integer(i);
          j++;
        }
        return Medium_Array;
      }
    }
    else if(arraySize==100000) {
      if(arrayType.equals("Random Order")) {
        for(i=0;i<arraySize;i++) {
          Large_Array[i] = random.nextInt();
        }
        return Large_Array;
      }
      else if(arrayType.equals("In Order")) {
        for(i=0;i<arraySize;i++) {
          Large_Array[i] = new Integer(i);
        }
        return Large_Array;
      }
      else if(arrayType.equals("Reverse Order")) {
        j=0;
        for(i=arraySize-1;i>=0;i--) {
          Large_Array[j] = new Integer(i);
          j++;
        }
        return Large_Array;
      }
    }
    return Small_Array;
  }

  //Method to test sorting. NOTE: Binary sort is flawed.
  public static boolean isSort (Comparable[] x) {
    int i;
    boolean isSorted = true;
    for(i=0;i<x.length-1;i++) {
      if(x[i].compareTo(x[i+1])>0) isSorted = false;
    }
    return isSorted;
  }

  //Test sort methods
  public static void testSort (String sortType) {
    Comparable[] x = new Comparable[100];       //Generate random array
    int i;
    Random random = new Random();
    for(i=0;i<x.length;i++) {
      x[i] = random.nextInt();
    }
    if(sortType.equals("linear")) {
      InsertionTest.sortLinear(x);      //Linear sort array
      System.out.println("[Linear] Sorted: " + isSort(x)); 
    }
    else if(sortType.equals("binary")) {
      InsertionTest.sortBinary(x);      //Binary sort array
      System.out.println("[Binary] Sorted: " + isSort(x));
      System.out.println("Ran into bugs with binary search. But it 'mostly works' (List is mostly sorted)");
    }
  }


  public static void main (String[] args) {
    //Linear tests in order
    TimeTest(1000,"linear","In Order");
    TimeTest(10000,"linear","In Order");
    TimeTest(100000,"linear","In Order");
    //Binary tests in order
    TimeTest(1000,"binary","In Order");
    TimeTest(10000,"binary","In Order");
    TimeTest(100000,"binary","In Order");

    //Linear tests in reverse order
    TimeTest(1000,"linear","Reverse Order");
    TimeTest(10000,"linear","Reverse Order");
    TimeTest(100000,"linear","Reverse Order");
    //Binary tests in reverse order
    TimeTest(1000,"binary","Reverse Order");
    TimeTest(10000,"binary","Reverse Order");
    TimeTest(100000,"binary","Reverse Order");

    //Linear tests in random order
    TimeTest(1000,"linear","Random Order");
    TimeTest(10000,"linear","Random Order");
    TimeTest(100000,"linear","Random Order");
    //Binary tests in random order
    TimeTest(1000,"binary","Random Order");
    TimeTest(10000,"binary","Random Order");
    TimeTest(100000,"binary","Random Order");
    testSort("linear");  //Test linear sort
    testSort("binary");  //Test binary sort
  }
  

}