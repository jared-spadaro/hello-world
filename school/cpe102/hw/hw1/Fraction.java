/*Class Fraction performs arithmetic computations on the fractional representation of numbers. 
 *The class provides methods to add, subtract, multiply, and divide fractions.
 *It also provides methods to access fractional components, test fractions for equality, 
 *compute the real-number value of a fraction, and generate the string representation of the fraction.
 *
 *As fractions are constructed and operated upon, they are maintained in reduced form. 
 *The reduced form is obtained by dividing the numerator and denominator through by their greatest common divisor. 
 *For example, 2/3 is the reduced form of 8/12.
 *
 * @author Jared Spadaro (jaspadar@calpoly.edu)    */

public class Fraction {

    private int numerator;     //Represents the numerator of the fraction
    private int denominator;   //Represents the denominator of the fraction
  
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
	    if(this.numerator == 0) {
	        this.denominator = 1;
	    }
	    if(this.denominator <= 0) {
	        throw new IllegalArgumentException();
	    }
        GCF();
    }
	
    //Find the greatest common factor of the numerator and denominator, 
    //then divide the numerator and denominator by the GCF
    private void GCF () {
        int n = numerator;       //Variable to represent the numerator without directly altering it
	int d = denominator;     //Variable to represent the denominator without direclty altering it
	if(n!=0 && d!=0) {
            while(Math.abs(n)!=Math.abs(d)) {
	        if (Math.abs(n)>Math.abs(d)) {
	            n=Math.abs(n)-Math.abs(d);
	        }
	        else {
	            d=Math.abs(d)-Math.abs(n);
	        }
	    }
	    numerator = numerator / d;
	    denominator = denominator / d;
	}
    } 
	
    //Return the value of this fraction's numerator
    public int getNumerator () {
        return this.numerator;
    }
	
    //Return the value of this fraction's denominator
    public int getDenominator () {
        return this.denominator;
    }
  
    //Return the value of this fraction as a real number
    public double value () {
        return (double)numerator / denominator;
    }
	
    //Produce the string representation of this fraction, of the form
    //"numerator / denominator," e.g., "1/2" or "3/4"
    public String toString () {
	if(numerator == 0) {
	    return "0";
	}
	if(denominator == 1) {
            return numerator + "";
	}
	else {
            return numerator + "/" + denominator;
        }
    }
	
    //Return true if this fraction equals the given fraction, i.e, the      	
    //numerator and denominator of the two fractions are equal
    public boolean equals (Fraction f) {
        return numerator == f.numerator && denominator == f.denominator;
    }

    //Add the given fraction to this fraction and return the result as a
    //third new fraction
    public Fraction add (Fraction f) {
	int new_denominator = denominator * f.denominator;    
        int new_numerator = (numerator * f.denominator + f.numerator * denominator); 
	return new Fraction(new_numerator,new_denominator);
    }
	
    //Subtract the given fraction from this fraction and return the 
    //result as a third new fraction
    public Fraction sub (Fraction f) {
        int new_denominator = denominator * f.denominator;
	int new_numerator = (numerator * f.denominator - f.numerator * denominator);
	return new Fraction(new_numerator,new_denominator);
    }
	
    //Multiply this fraction by the given fraction and return the
    //result as a third new fraction
    public Fraction mul (Fraction f) {
        return new Fraction (numerator * f.numerator,denominator * f.denominator);
    }

    //Divide this fraction by the given fraction and return the result as a 
    //third new fraction
    public Fraction div (Fraction f) {
	int new_numerator = numerator * f.denominator;
	int new_denominator = denominator * f.numerator;
	if(new_denominator < 0) {                  //Conditional to deal with an argument fraction with a negative
	    new_denominator = -new_denominator;    //numerator that causes the quotient denominator to be negative
            new_numerator = -new_numerator;        
	}
        return new Fraction (new_numerator,new_denominator);
    }
}



    
