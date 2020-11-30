import java.util.Scanner;
import java.lang.reflect.*;

/****
 *
 * FractionTest is the test driver for program 1.  To compile and run the
 * tests, execute the following commands:
 *                                                                         <pre>
 *     javac FractionTest.java Fraction.java
 *     java FractionTest
 *                                                                        </pre>
 *
 * The driver will output a heading for each testing category, a message for
 * each failed test, and summary of the testing run at the end.  There are only
 * two possible execution scores on the program -- 100% if you pass all the
 * tests or 0% if you do not pass them all.
 *                                                                           <p>
 * The comments in this file describe the purpose of each test.  Throughout the
 * quarter we'll be discussing principles of good program testing, and use some
 * concrete examples from this and other testing classes during the discussions.
 *                                                                           <p>
 * @author Kurt Mammen, with updates from Gene Fisher (kmannen@calpoly.edu,
 *         gfisher@calpoly.edu).
 */
public class FractionTest {
    /** String to be printed for the header of the output. */
    private static final String RESULTS_FOR = "Results for Program 1";

    /** Value used to deal with real number rounding inaccuracy. */
    private static final double EPSILON = 0.000000000000001;

    /**
     * Print the testing header then run each of the test phases.
     */
    public static void main(String[] args) {

        boolean pass = true;    // Variable that indicates if tests pass.

        printHeader(args);

        // Call the architecture tests first, and do no further testing if they
        // fail.
        pass &= testArchitecture();

        // Call the functional tests
        if (pass) {
            pass &= testDefaultConstructor();
            pass &= testNumeratorConstructor();
            pass &= testNumeratorDenominatorConstructor();
            pass &= testToString();
            pass &= testEquals();
            pass &= testAdd();
            pass &= testSub();
            pass &= testMul();
            pass &= testDiv();
        }

        // Print out the results of the testing run.
        printResults(pass);

        // Return a value of -1 if the tests do not all pass, 0 if they do.
        // These values are consistent with UNIX conventions for program return
        // values.
        if (!pass) {
            System.exit(-1);
        }
        System.exit(0);
     }

    /**
     * Test the default constructor.  Since it takes no input parameters, one
     * test case will do.
     */
    private static boolean testDefaultConstructor() {
         boolean pass = true;
         System.out.println("   Testing default constructor - Fraction()...");

         pass &= test(new Fraction(), 0, 1);

         return pass;
     }

    /**
     * Test the numerator constructor with this unit test plan:
     *                                                                    <pre>
     * Test                 Expected
     * Case    Input         Output         Description
     * ======================================================================
     *  1       100         100 / 1         Positive numerator value
     *  2      -100        -100 / 1         Negative numerator value
     *  3       0             0 / 1         Zero numerator
     *                                                                   </pre>
     */
    private static boolean testNumeratorConstructor() {
         boolean pass = true;
         System.out.println("   Testing constructor - Fraction(int)...");
         String msg = "      FAILED: ";

         pass &= test(new Fraction(100), 100, 1);
         pass &= test(new Fraction(-100), -100, 1);
         pass &= test(new Fraction(0), 0, 1);

         return pass;
     }

    /**
     * Test the constructor that takes both numerator and denominator values.
     * Test plan details are in the code comments.
     */
    private static boolean testNumeratorDenominatorConstructor() {
         boolean pass = true;
         System.out.println("   Testing constructor - Fraction(int, int)...");

        // Test with values 1,2 and 2,1.  In both cases, expect no reductions
        // of the values, since the GCD of the values is 1.
        pass &= test(new Fraction(1, 2), 1, 2);
        pass &= test(new Fraction(2, 1), 2, 1);

        // Test with values 4,8 and 8,4.  Expect reduction to 1,2 and 2,1
        // since the GCD of the inputs is 4.
        pass &= test(new Fraction(4, 8), 1, 2);
        pass &= test(new Fraction(8, 4), 2, 1);

        // Test with values 15,75 and 75,15.  Expect reduction to 1,5 and 5,1,
        // since the GCD of the inputs is 15.
        pass &= test(new Fraction(15, 75), 1, 5);
        pass &= test(new Fraction(75, 15), 5, 1);

        // Test with negative and zero valued numerator.
        pass &= test(new Fraction(-6, 9), -2, 3);
        pass &= test(new Fraction(0, 3), 0, 1);

        // Test with large values for nuerator and denominator, with a GCD
        // value that is substntially smaller than these values.
        pass &= test(new Fraction(255255, 1616615), 3, 19);


        // Test that exceptions are properly caught.
        boolean caught = false;
        try {
            // Test that exception thrown with negative denominator.
            new Fraction(9, -6);
        }
        catch (IllegalArgumentException e) {
            caught = true;
        }
        pass &= test(caught,
            "      FAILED: IllegalArgumentExcpetion not thrown");

        caught = false;
        try {
            // Test that exception thrown with zero valued denominator.
            new Fraction(3, 0);
        }
        catch(IllegalArgumentException e) {
            caught = true;
        }
        pass &= test(caught,
            "      FAILED: IllegalArgumentExcpetion not thrown");

        return pass;
     }

    /**
     * Test the toString method.
     */
    private static boolean testToString() {
        boolean pass = true;
        String msg = "      FAILED: ";
        System.out.println("   Testing toString()...");

        // Test with a combination of values, that include further tests
        // of fraction contruction and reduction.
        Fraction f = new Fraction(5, 6);
        pass &= test(f.toString().equals("5/6"), msg +
           "toString() is " + f.toString() + ", expected 5/6");

        f = new Fraction(-5, 6);
        pass &= test(f.toString().equals("-5/6"), msg +
           "toString() is " + f.toString() + ", expected 5/6");

        f = new Fraction(49, 56);
        pass &= test(f.toString().equals("7/8"), msg +
           "toString() is " + f.toString() + ", expected 7/8");

        f = new Fraction(13, 5);
        pass &= test(f.toString().equals("13/5"), msg +
           "toString() is " + f.toString() + ", expected 13/5");

        f = new Fraction(-139, 1);
        pass &= test(f.toString().equals("-139"), msg +
           "toString() is " + f.toString() + ", expected -139");

        f = new Fraction(5139, 1);
        pass &= test(f.toString().equals("5139"), msg +
           "toString() is " + f.toString() + ", expected 5139");

        return pass;
     }

    /**
     * Test the equals method.
     */
    private static boolean testEquals() {
         boolean pass = true;
         String msg = "      FAILED: ";
         System.out.println("   Testing equals(Fraction)...");

         Fraction f1 = new Fraction(5, 6);
         Fraction f2 = new Fraction(10, 12);
         Fraction f3 = new Fraction(1, 2);

         pass &= test(f1.equals(f1),
             msg + "equals() is true, expected false");
         pass &= test(f1.equals(f2),
             msg + "equals() is true, expected false");
         pass &= test(!f2.equals(f3),
             msg + "equals() is false, expected true");

         return pass;
     }

    /**
     * Test the add method.  Details of the test plan are in code comments.
     */
    private static boolean testAdd() {
        boolean pass = true;
        String msg = "      FAILED: ";
        System.out.println("   Testing add(Fraction)...");

        // Create a number of fractions for use in the tests.
        Fraction f1 = new Fraction(5, 6);
        Fraction f2 = new Fraction(25, 30);
        Fraction f3 = new Fraction(1, 2);
        Fraction f4 = new Fraction(5, 10);
        Fraction f5 = new Fraction(-3, 4);

        //
        // All of the test cases that follow confirm no modification to the
        // operand fractions.

        // Add fraction to itself, confirm no modification to operands.
        pass &= test(f1.add(f1), 5, 3);
        pass &= test(f1, 5, 6);

        // Add fractions with some simple reduction required.
        pass &= test(f1.add(f2), 5, 3);
        pass &= test(f1, 5, 6);
        pass &= test(f2, 5, 6);

        pass &= test(f1.add(f3), 4, 3);
        pass &= test(f1, 5, 6);
        pass &= test(f3, 1, 2);

        pass &= test(f1.add(f4), 4, 3);
        pass &= test(f1, 5, 6);
        pass &= test(f4, 1, 2);

        pass &= test(f3.add(f4), 1, 1);
        pass &= test(f3, 1, 2);
        pass &= test(f4, 1, 2);

        // Add with negative numerators.
        pass &= test(f4.add(f5), -1, 4);
        pass &= test(f4, 1, 2);
        pass &= test(f5, -3, 4);

        pass &= test(f5.add(f4), -1, 4);
        pass &= test(f4, 1, 2);
        pass &= test(f5, -3, 4);

        return pass;
     }

    /**
     * Test the sub method.  Use same test cases as for testAdd.
     */
    private static boolean testSub() {
        boolean pass = true;
        String msg = "      FAILED: ";
        System.out.println("   Testing sub(Fraction)...");

        Fraction f1 = new Fraction(5, 6);
        Fraction f2 = new Fraction(25, 30);
        Fraction f3 = new Fraction(1, 2);
        Fraction f4 = new Fraction(5, 10);
        Fraction f5 = new Fraction(-3, 4);

        pass &= test(f1.sub(f1), 0, 1);
        pass &= test(f1, 5, 6);

        pass &= test(f1.sub(f2), 0, 1);
        pass &= test(f1, 5, 6);
        pass &= test(f2, 5, 6);

        pass &= test(f1.sub(f3), 1, 3);
        pass &= test(f1, 5, 6);
        pass &= test(f3, 1, 2);

        pass &= test(f1.sub(f4), 1, 3);
        pass &= test(f1, 5, 6);
        pass &= test(f4, 1, 2);

        pass &= test(f3.sub(f4), 0, 1);
        pass &= test(f3, 1, 2);
        pass &= test(f4, 1, 2);

        pass &= test(f4.sub(f5), 5, 4);
        pass &= test(f4, 1, 2);
        pass &= test(f5, -3, 4);

        pass &= test(f5.sub(f4), -5, 4);
        pass &= test(f4, 1, 2);
        pass &= test(f5, -3, 4);

        return pass;
     }

    /**
     * Test the mul method.  Use test cases from testAdd, plus some additional
     * test cases to test particular of the multiplication implementation.
     */
    private static boolean testMul() {
        boolean pass = true;
        String msg = "      FAILED: ";
        System.out.println("   Testing mul(Fraction)...");

        Fraction f1 = new Fraction(5, 6);
        Fraction f2 = new Fraction(25, 30);
        Fraction f3 = new Fraction(1, 2);
        Fraction f4 = new Fraction(5, 10);
        Fraction f5 = new Fraction(1, 6);
        Fraction f6 = new Fraction(3, 1);
        Fraction f7 = new Fraction(-3, 2);

        pass &= test(f1.mul(f1), 25, 36);
        pass &= test(f1, 5, 6);

        pass &= test(f1.mul(f2), 25, 36);
        pass &= test(f1, 5, 6);
        pass &= test(f2, 5, 6);

        pass &= test(f1.mul(f3), 5, 12);
        pass &= test(f1, 5, 6);
        pass &= test(f3, 1, 2);

        pass &= test(f1.mul(f4), 5, 12);
        pass &= test(f1, 5, 6);
        pass &= test(f4, 1, 2);

        pass &= test(f3.mul(f4), 1, 4);
        pass &= test(f3, 1, 2);
        pass &= test(f4, 1, 2);

        pass &= test(f5.mul(f6), 1, 2);
        pass &= test(f5, 1, 6);
        pass &= test(f6, 3, 1);

        pass &= test(f1.mul(f7), -5, 4);
        pass &= test(f1, 5, 6);
        pass &= test(f7, -3, 2);

        pass &= test(f7.mul(f1), -5, 4);
        pass &= test(f1, 5, 6);
        pass &= test(f7, -3, 2);

        return pass;
    }

    /**
     * Test the div method.  Use tests from testAdd, plus some additional test
     * cases to test particulars of the division implementation.
     */
    private static boolean testDiv() {
        boolean pass = true;
        String msg = "      FAILED: ";
        System.out.println("   Testing div(Fraction)...");

//      NOTE: Using the next test value as a divisor opens a huge can of worms:
//         Fraction f0 = new Fraction();
        Fraction f1 = new Fraction(5, 6);
        Fraction f2 = new Fraction(25, 30);
        Fraction f3 = new Fraction(1, 2);
        Fraction f4 = new Fraction(5, 10);
        Fraction f5 = new Fraction(-3, 2);

//      Here's a test case with the squrimy worm critter we're not letting out
//      of the can:
//         pass &= test(f0.div(f0), 1, 1);
//         pass &= test(f0, 0, 1);

        pass &= test(f1.div(f1), 1, 1);
        pass &= test(f1, 5, 6);

        pass &= test(f1.div(f2), 1, 1);
        pass &= test(f1, 5, 6);
        pass &= test(f2, 5, 6);

        pass &= test(f1.div(f3), 5, 3);
        pass &= test(f1, 5, 6);
        pass &= test(f3, 1, 2);

        pass &= test(f1.div(f4), 5, 3);
        pass &= test(f1, 5, 6);
        pass &= test(f4, 1, 2);

        pass &= test(f3.div(f4), 1, 1);
        pass &= test(f3, 1, 2);
        pass &= test(f4, 1, 2);

        pass &= test(f1.div(f5), -5, 9);
        pass &= test(f1, 5, 6);
        pass &= test(f5, -3, 2);

        pass &= test(f5.div(f1), -9, 5);
        pass &= test(f1, 5, 6);
        pass &= test(f5, -3, 2);

        pass &= test(f5.div(f5), 1, 1);
        pass &= test(f5, -3, 2);

        return pass;
    }

    /**
     * Test the program architecture.
     */
    private static boolean testArchitecture() {
        boolean pass = true;
        String msg = "      FAILED: ";
        Fraction f;
        Class cl;
        Class[] temp;

        System.out.println("   Testing Fraction architecture...");

        f = new Fraction();

        cl = f.getClass();

        // Expect 3 constructors
        int cnt = cl.getConstructors().length;     
        pass &= test(cnt == 3,
            msg + cnt + " constructors, expected 3");

        // Expect 9 public methods
        cnt = countModifiers(cl.getDeclaredMethods(), Modifier.PUBLIC);     
        pass &= test(cnt == 9,
            msg + cnt + " public methods, expected 9");

        // Expect 0 public data fields
        cnt = cl.getFields().length;
        pass &= test(cnt == 0,
            msg + cnt + " public fields, expected 0");

        // Expect 0 protected data fields
        cnt = countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED);
        pass &= test(cnt == 0,
            msg + cnt + " protected fields, expected 0");

        // Expect 3 or fewer private data fields
        cnt = countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE);
        pass &= test(cnt <= 3,
            msg + cnt + " private fields, expected 3 or fewer");

        // Expect 0 package private data fields (i.e., no explicit private)
        cnt = countPackage(cl.getDeclaredFields());
        pass &= test(cnt == 0,
            msg + cnt + " package fields, expected 0");

        return pass;
    }

    /**
     * Print the header at the beginning of the test output.
     */
    private static void printHeader(String[] args) {
        if (args.length == 1) {
           System.out.println(args[0]);
        }

        System.out.println(RESULTS_FOR + "\n");
    }

    /**
     * Print out the results of the test run and how many points are scored.
     */
    private static void printResults(boolean pass) {
        String msg;

        if (pass) {
         msg = "\nCongratulations, you passed all the tests!\n\n"
            + "Your grade will be based on when you turn in your functionally\n"
            + "correct solution and any deductions for the quality of your\n"
            + "implementation.  Quality is based on, but not limited to,\n"
            + "coding style, documentation requirements, compiler warnings,\n"
            + "and the efficiency and elegance of your code.\n";
        }
        else {
            msg = "\nNot done yet - you failed one or more tests!\n";
        }

        System.out.print(msg);       
    }

    /**
     * Return true if Math.abs(a - b) < EPSILON, where EPSILON is the class
     * constant defined above.
     */
    private static boolean approx(double a, double b) {
       return Math.abs(a - b) < EPSILON;
    }

    /**
     * Print a failure message if the given Fraction f does not have the
     * expected numerator, denominator, and value.
     */
    private static boolean test(Fraction f, int n, int d) {
        boolean pass = true;
        String msg = "      FAILED: ";

        pass &= test(f.getNumerator() == n, msg +
           "Numerator is " + f.getNumerator() + ", expected " + n);

        pass &= test(f.getDenominator() == d, msg + 
           "Denominator is " + f.getDenominator() + ", expected " + d);

        pass &= test(approx(f.value(), (double)n/d), msg +
           "Value is " + f.value() + ", expected " + (double)n/d);

        return pass;     
    }

    /**
     * Print the given error message msg if the given boolean value for pass is
     * false.  This overload of the test method is used in the following
     * specific cases: (1) testing if exceptions are properly caught, (2)
     * testing the proper output of toString, (3) testing the proper output of
     * equals, and (4) checking that the architecture tests are correct.
     */
    private static boolean test(boolean pass, String msg) {
        if (!pass) {
            System.out.println(msg);
            (new Throwable()).printStackTrace();
        }
        return pass;
    }

    /**
     * Return the count for the number of data fields defined in the Fraction
     * class.
     */
    private static int countModifiers(Field[] fields, int modifier) {
        int count = 0;

        for (Field f : fields) {
           if (f.getModifiers() == modifier) {
              count++;
           }
        }

        return count;
    }

    /**
     * Return the count for the number of methods defined in the Fraction
     * class.
     */
    private static int countModifiers(Method[] methods, int modifier) {
       int count = 0;

       for (Method m : methods) {
          if (m.getModifiers() == modifier) {
             count++;
          }
       }

       return count;
    }

    /**
     * Return the number of package private data fields in the Fraction class.
     * These are data fields that are not declared explicitly as private.
     */
    private static int countPackage(Field[] fields) {
        int cnt = fields.length
                  - countModifiers(fields, Modifier.PRIVATE)
                  - countModifiers(fields, Modifier.PROTECTED)
                  - countModifiers(fields, Modifier.PUBLIC);

        // Adjust for students that have written assert statments in their code
        // The package field specified below gets added to the .class file when
        // assert statements are present in the source.
        //
        // NOTE: Don't worry about assert statements until we have discussed
        // them in class, which won't be for a few weeks.
        for (Field f : fields) {
            int mods = f.getModifiers();

            if (Modifier.isStatic(mods) &&
                    Modifier.isFinal(mods) &&
                    f.getName().equals("$assertionsDisabled")) {
               cnt--;
            }
        }

        return cnt;
    } 
}

