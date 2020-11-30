/*Class FractionTest contains numerous testing methods which serve to call the methods from class Fraction and test them to make sure they work properly.

* @author Jared Spadaro jaspadar */

public class FractionTest {

    private static void testDefaultConstructor() {
        Fraction f = new Fraction();
		int n = f.getNumerator();
		int d = f.getDenominator();
		if (n!=0 || d!=1) {
		    System.out.println("Got " + n + "/" + d + ", expected 0/1");
	    }
    }

    private static void testNumeratorConstructor() {
		test1(5,5);
		test1(121,121);
        test1(0,0);
    }
	
	private static void test1(int n_in,int n_expected) {
		Fraction f = new Fraction(n_in);
     	int n = f.getNumerator();
		int d = f.getDenominator();
		if(n!=n_expected || d!=1) {
			System.out.println("Got " + n + "/" + d + ", expected " + n_expected + "/1");
		}
	}

    
    private static void testNumeratorDenominatorConstructor() {
        
    }
	
	private static void test2(int n_in, int d_in,
	int n_expected, int d_expected) {
	    Fraction f = new Fraction(n_in,d_in);
		int n = f.getNumerator();
		int d = f.getDenominator();
		if(n!=n_expected || d!=d_expected) {
		    System.out.println("Got " + n + "/" + d + ", expected " + n_expected + "/" + d_expected);
		}
	}

    private static void testToString() {

    }

    private static void testEquals() {

    }

    private static void testAdd() {

    }

    private static void testSub() {

    }

    private static void testMul() {

    }

    private static void testDiv() {

    }

    public static void main (String args[]) {
       testDefaultConstructor();
       testNumeratorConstructor();
       testNumeratorDenominatorConstructor();
       testToString();
       testEquals();
       testAdd();
       testSub();
       testMul();
       testDiv();
    }
}  
