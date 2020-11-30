// This import statement must appear outside and before the class.
import java.util.Scanner;

/****
 * This is a test driver for the Greeter class.
 */
public class GreeterTest {

    /**
     * Construct a Scanner and use it to input a name.  Then construct a
     * Greeter class and send it the name that was input.  Call the greet
     * method of the greeter class to build a greeting string.  Print that
     * string out.
     */
    public static void main(String[] args) {

       /*
        * Declare a Scanner reference and initialize it by constructing a
        * Scanner object that will read from the command-line.  This is an
        * example of a Java constructor call, which is used everywhere in
        * object-oriented languages like Java.
        */
       Scanner scanner = new Scanner(System.in);

       /*
        * Prompt the user for a name.  This is an example of how you print to
        * the command line in Java.
        */
        System.out.print("What is your name? ");

       /*
        * Declare a String reference and initialize it with the name that the
        * user typed in response to the prompt.  This is an example of how to
        * call a method in Java.
        */
        String name = scanner.nextLine();

       /*
        *  Construct a Greeter object.  This is a class you will write.
        */
       Greeter greeter = new Greeter(name);

       /*
        * Declare another String reference and initialize it with the greeting
        * returned by a call to the Greeter class's greet method.
        */
        String greeting = greeter.greet();

       /*
        * Display the greeting to the command-line.
        */
        System.out.println(greeting);
    }
}

