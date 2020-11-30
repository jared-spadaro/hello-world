// Program by Jared Spadaro
// CPE 103 with Professor Buckalew
// 10/17/13

import java.util.Random;
import java.util.Arrays;

public class InsertionTest {

  
  //Linear Sort Method
  public static void sortLinear (Comparable[] x) {
   int i,j;
   Comparable temp;                     
   for(i=1;i<x.length;i++) {            //for each element 
     int position = linearSearch(x,i);  //position where the element is to be inserted
     if(position!=i) {                  //make sure that a shift is needed
        temp = x[i];         
        for(j=i;j>position;j--) {       //run loop from position of current element to its insertion spot
          x[j] = x[j-1];                //shift elements to the left
        }
        x[position] = temp;             //insert element 
      }
    }
  }

 

  //Binary Sort Method
  public static void sortBinary (Comparable[] x) {
    int i,j;
    Comparable temp;
    for(i=1;i<x.length;i++) {                   //for each element 
      int position = binarySearch(x,x[i],0,i);  //position where the element is to be placed
      if(position!=i) {                         //make sure that a shift is needed
        temp = x[i];
        for(j=i;j>position;j--) {               //run loop from position of current element to its insertion spot
          x[j] = x[j-1];                        //shift elements to the left
        }
        x[position] = temp;                     //insert element
      }
    }
  }

 

   //Linear Search Method
  public static int linearSearch (Comparable[] x, int begin) {
    for(int i=begin-1;i>=0;i--) {                   //from current element to beginning of list
      if (x[i].compareTo(x[begin])<=0) return i+1;  //if x[i] is less than current element, we want to insert after x[i]. so return i+1
    }                                                 
    return 0;                                       //if loop makes it to end, element must be smallest. so return 0 
  }

  

  //Binary Search Method (imperfect, noted in README file)
  public static int binarySearch (Comparable[] x, Comparable value, int left, int right) {
    while(left<right) {
      int mid = (left+right)/2;                            
      if(mid==0) {                                         //Case for if mid is on left edge
        if(x[mid].compareTo(value)>=0) return 0;           //If first element is greater than value, value must be smallest
        else return 1;  
      }
      else if(mid==x.length-1) {                           //Case for if mid is on right edge
        if(x[mid].compareTo(value)<=0) return x.length-1;  //If last element is smaller than value, value must be largest
        else return x.length-2; 
      }
      else {
        if(x[mid]==value) return mid;                      //If numbers are equal, insert value there
        else if(x[mid].compareTo(value)<0) {               //If value is larger than mid
          if(x[mid+1].compareTo(value)>=0) return mid+1;   //And value is smaller than mid+1...insert at mid+1
          left = mid+1;                                    //Otherwise, look in right half
        }
        else {                                             //If value is smaller than mid
          if(x[mid-1].compareTo(value)<=0) return mid+1;   //And value is larger than mid-1...insert at mid+1
          right = mid-1;                                   //Otherwise, look in left half                
        }
      }
    }
    return 0;                      
  }

 



}