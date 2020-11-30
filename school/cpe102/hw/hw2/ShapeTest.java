import java.awt.Point;
import java.awt.Color;

public class ShapeTest {

    //Circle tests

    private static void getAreaTest () {
	    Point p = new Point (2,5);
		//Color blue = new Color (0,0,255);
	    Circle c = new Circle (4.0,p,Color.blue,true);
		System.out.println("Area = " + c.getArea());
	}
	
	private static void getColorTest () {
	    Point p = new Point (1,3);
		Circle c = new Circle (5,p,Color.green,true);
		System.out.println("Color = " + c.getColor());
	}
	
	private static void setColorTest () {
	   // Point p = new Point (1,3);
		Circle c = new Circle (2,new Point (1,3),Color.red,true);
		System.out.println("Old color = " + c.getColor());
		c.setColor(Color.white);
		System.out.println("New color = " + c.getColor());
	}
	
	private static void moveTest () {
	    Circle c = new Circle (5,new Point (0,0),Color.white,false);
		Circle c2 = new Circle (4,new Point (5,4),Color.black,false);
		Point delta = new Point (2,-3);
		Point delta2 = new Point (-5,-7);
		System.out.println ("Old center [1] = " + c.getPosition());
		c.move(delta);
		System.out.println ("New center [1] = " + c.getPosition());
		System.out.println ("Old center [2] = " + c2.getPosition());
		c2.move(delta2);
		System.out.println ("New center [2] = " + c2.getPosition());
	}
	
	private static void equalsTest () {
	    Circle c = new Circle (3,new Point(2,5),Color.cyan,true);
		Circle c1 = new Circle (3,new Point(2,5),Color.cyan,true);
		Circle c2 = new Circle (3,new Point(2,5),Color.cyan,false);
		System.out.println(c.equals(c1));
		System.out.println(c.equals(c2));
	}
	
	//Convext Polygon Tests
	
	private static void PolygonAreaTest () {
	
	}
	
	
	

    public static void main (String args[]) {
	    //Circle tests
		getAreaTest();
		getColorTest();
		setColorTest();
		moveTest();
		equalsTest();
	}
	
}