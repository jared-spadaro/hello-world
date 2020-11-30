import java.util.Scanner;

public class ArrayListDriver {

    public static void main (String[] args) {
	    System.out.println("Enter values: ");
		String s = "quit";
		//Scanner scanner = new Scanner (System.in);
		int x = 0;
		Array_list list = new Array_list();
		while(x==0) {
		    Scanner scanner = new Scanner (System.in);
			
			    if(s.equals(scanner.next())==true) {
			        x=1;
				}
			
				list.get_strings().add(scanner.next());
				
			    list.get_integers().add(scanner.nextInt());
                
            
                list.get_doubles().add(scanner.nextDouble());
                
            
            
                list.get_booleans().add(scanner.nextBoolean());
                
            
            
        }

        //System.out.println ("Minimum integer: " + list.minimumInt());
        System.out.println ("Average of doubles: " + list.averageDouble());
        System.out.println ("Number of true values: " + list.numberofTrues());
        System.out.println ("Number of strings: " + list.numberofStrings());    
		
		
		
		
		
	}		
}
    