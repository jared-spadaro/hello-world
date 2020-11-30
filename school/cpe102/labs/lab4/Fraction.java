/*Class Fraction performs arithmetic computations on the fractional representation of numbers. 
*The class provides methods to add, subtract, multiply, and divide fractions.
*It also provides methods to access fractional components, test fractions for equality, 
*compute the real-number value of a fraction, and generate the string representation of the fraction.
*
*As fractions are constructed and operated upon, they are maintained in reduced form. 
*The reduced form is obtained by dividing the numerator and denominator through by their greatest common divisor. 
*For example, 2/3 is the reduced form of 8/12.
*
* @author Jared Spadaro jaspadar */

public class Fraction {

    int numerator;
    int denominator;
  
    //Construct a fraction with numerator 0 and denominator 1
    public Fraction () {
        this.numerator = 0;
        this.denominator = 1;  
    }

    //Construct a fraction with the given numerator and a denominator of 1
    public Fraction (int numerator) {
        this.numerator = numerator;
        this.denominator = 1; 
    }

    //Construct a fraction with the given numerator and denominator
    public Fraction (int numerator, int denominator) {
        this.numerator = numerator;
        this.denominator = denominator; 
		
    }
	
	private void GCD () {
	    int n = numerator;
		int d = denominator;
		while(n!=d) {
	        if (n>d) {
			    n=n-d;
			}
			else {
			    d=d-n;
			}
		numerator = numerator / d;
		denominator = denominator / d;
	}
		

    /*Add the given fraction to this fraction and return the result as a
    third new fraction*/
    public Fraction add (Fraction f) {
       return new Fraction ();
    }

    /*Divide this fraction by the given fraction and return the result as a 
    third new fraction*/
    public Fraction div (Fraction f) {
       return new Fraction ();
    }
   
    /*Return true if this fraction equals the given fraction, i.e, the      	
	numerator and denominator of the two fractions are equal*/
    public boolean equals (Fraction f) {
       return true;
    }
  
    //Return the value of this fraction's denominator
    public int getDenominator () {
       return this.denominator;
    }
  
    //Return the value of this fraction's numerator
    public int getNumerator () {
       return this.numerator;
    }

    /*Multiply this fraction by the given fraction and return the
    result as a third new fraction*/
    public Fraction mul (Fraction f) {
       return new Fraction ();
    }
   
    /*Subtract the given fraction from this fraction and return the 
    result as a third new fraction*/
    public Fraction sub (Fraction f) {
       return new Fraction ();
    }
 
    /*Produce the string representation of this fraction, of the form
      "numerator / denominator," e.g., "1/2" or "3/4"*/
    public java.lang.String toString () {
       return "test";
    }

    //Return the value of this fraction as a real number
    public double value () {
       return 0;
    }
}



    
