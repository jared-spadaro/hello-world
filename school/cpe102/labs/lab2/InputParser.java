import java.util.Scanner;


public class InputParser {
   
   public static void main (String[] args)
   {
      System.out.print("How many values would you like to parse? ");
	  Scanner sc = new Scanner (System.in);
	  int num_args = sc.nextInt();
	  System.out.print("Please enter your values now. ");
	  Scanner s = new Scanner (System.in);
	  int num_ints = 0;
	  while (s.hasNextInt())
	  {
	     System.out.print(s.nextInt() + " ");
		 num_ints++; 
	  }
	  System.out.println("Sum of ints: " /*+ ScanSum(s)*/);
	  s.close();
	  
	  int num_doubles = 0;
	  while (s.hasNextDouble())
	  {
	      System.out.print(s.nextDouble() + " ");
		  num_doubles++;
	  }
	  System.out.println("Sum of doubles: " /*+ ScanSum(s)*/);
	  s.close();
	  
   }
}


