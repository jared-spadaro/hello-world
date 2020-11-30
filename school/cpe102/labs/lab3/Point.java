/****
 *
 * Class Point has an integer x and y value, to represent a geometric point in
 * in X/Y coordinate space.  CSC 102 Lab 3 asks some questions about this class.
 * Put your answsers to each question in this class comment, in the places
 * indicated.
 *
 * ANSWER TO LAB QUESTION 1:
 *  The first statement prints the toString of p1 because 
 *  the print command defaults to toString if no other command
 *  is given.
 *  
 * ANSWER TO LAB QUESTION 2:
 *  The second statement prints the toString of the object p1;
 *  it is essentially the same command as the first statement, 
 *  therefore they output the same thing.
 *
 * ANSWER TO LAB QUESTION 3:
 *  The third statement printed false because although the objects have the 
 *  "same values," they point to different things.
 *  
 *
 *  ANSWER TO LAB QUESTION 4:
 *  They come from the Object class.
 *
 *
 */
public class Point {

    /** X coordinate of the point. */
    private int x;

    /** X coordinate of the point. */
    private int y;
	
    Point (int x, int y) {
       this.x = x;
       this.y = y;
    }
	
    public boolean equals (Point p) {
       return x == p.x && y == p.y;
    }
	
    public java.lang.String toString () {
       return "x = " + x + ", y = " + y;
    } 

    public static void main(String args[]) {

        // Before you add any code of your own, answer lab questions 1 through
        // 4 about the following five lines of code.
        Point p1 = new Point(4,5);
        Point p2 = new Point(4,5);
        Point p3 = new Point(7,2);
	Point p4 = new Point(1,8);
        System.out.println(p1);
        System.out.println(p1.toString());
		
	//Test for contructor
	System.out.println("Constructor Test:");
	System.out.println("x value = " + p1.x + ", y value = " + p1.y);
		
	// Tests for equals
	System.out.println("Equals Test:");
        System.out.println(p1.equals(p2));
	System.out.println(p3.equals(p4));
		
	//Test for toString
	System.out.println("toString Test:");
	System.out.println(p1.toString());
	System.out.println(p3.toString());
	System.out.println(p4.toString());
		
    }

    // Add a public initializing constructor and equals method to this Point
    // class.  Then add some print statements to main to test these methods.
    //
    // The toString method should provide output of the form
    //      "x = <value of x>, y = <value of y>"
    // For example, of x = 10, and y = 20, then toString outputs
    //      "x = 10, y = 20"
    //
    // The equals method should return true if both x and y values of two
    // points are equal, false otherwise.

}
