/*Class FractionTest contains numerous testing methods which serve to call the methods from class Fraction and test them to make sure they work properly.

* @author Jared Spadaro jaspadar */



public class selfFractionTest {

    private static void testDefaultConstructor() {
        Fraction f = new Fraction();
		int n = f.getNumerator();
		int d = f.getDenominator();
		if (n!=0 || d!=1) {
		    System.out.println("Got " + n + "/" + d + ", expected 0/1");
	    }
    }

    private static void testNumeratorConstructor() {
		/*test1(5,5);
		test1(121,121);
        test1(0,0);*/
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
        //test2(1,0,1,0);
		//test2(0,0,0,0);
		/*test2(0,1,0,1);
		test2(1,2,1,2);
		test2(4,8,1,2);
		test2(77,132,7,12);
		test2(171,33,57,11);
		test2(567,1,567,1);*/
    }
	
	private static void test2(int n_in, int d_in, int n_expected, int d_expected) {
	    Fraction f = new Fraction(n_in,d_in);
		int n = f.getNumerator();
		int d = f.getDenominator();
		if(n!=n_expected || d!=d_expected) {
		    System.out.println("Got " + n + "/" + d + ", expected " + n_expected + "/" + d_expected);
		}
	}

    private static void testToString() {
        test3(4,5);
		/*test3(62,2460);
		//test3(5,0);
		test3(45,1);
		test3(1311,399);*/
    }
	
	private static void test3(int n_in, int d_in) {
        Fraction f = new Fraction(n_in,d_in);
		String expected = n_in + "/" + d_in;
		String actual = f.toString();
		/*if(actual.equals(expected)!=true) {
		    System.out.println("Error: can not divide by 0.");
		}*/
		System.out.println(f.toString());
		
	}
		
    private static void testEquals() {
        /*test4(5,10,45,90);
		test4(188,44,47,11);
		test4(5,7,6,8);
		test4(56,84,56,85);
		test4(56,84,57,84);
		test4(27,1,135,5);*/
		
    }
	
	private static void test4(int n1_in, int d1_in, int n2_in, int d2_in) {
	    Fraction f1 = new Fraction (n1_in,d1_in);
		Fraction f2 = new Fraction (n2_in,d2_in);
		System.out.println(f1.equals(f2));
	}

    private static void testAdd() {
        /*test5(1,2,1,2);
        test5(3,8,2,5); 
        test5(11,5,21,4); 
        test5(-65,1,43,1); 
        test5(39,243,-45,240);*/
        test5(5,6,5,6);
    }
	
	private static void test5 (int n1_in, int d1_in, int n2_in, int d2_in) {
	    Fraction f1 = new Fraction (n1_in,d1_in);
		Fraction f2 = new Fraction (n2_in,d2_in);
		System.out.println(f1.add(f2).toString());
	}

    private static void testSub() {
        /* test6(3,5,4,7);
		 test6(2,11,1,2);
		 test6(432,12,320,14);
		 test6(7,1,15,2);*/
    }

    private static void test6 (int n1_in, int d1_in, int n2_in, int d2_in) {
	    Fraction f1 = new Fraction (n1_in,d1_in);
		Fraction f2 = new Fraction (n2_in,d2_in);
		System.out.println(f1.sub(f2).toString());
	}

    private static void testMul() {
       /* test7(2,3,1,5);
		test7(1,24,24,1);
		test7(47,234,80,230);
		test7(0,6478,574563,3563456);*/
    }
	
	private static void test7 (int n1_in, int d1_in, int n2_in, int d2_in) {
	    Fraction f1 = new Fraction (n1_in,d1_in);
		Fraction f2 = new Fraction (n2_in,d2_in);
		System.out.println(f1.mul(f2).toString());
	}

    private static void testDiv() {
        /*test8(2,3,1,5);
		//test8(1,3,0,2);
		test8(0,4,5,9);
		test8(-4,-12,-6,-24);*/
    }
	
	private static void test8 (int n1_in, int d1_in, int n2_in, int d2_in) {
	    Fraction f1 = new Fraction (n1_in,d1_in);
		Fraction f2 = new Fraction (n2_in,d2_in);
		System.out.println(f1.div(f2).toString());
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
