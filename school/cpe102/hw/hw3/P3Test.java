import java.awt.Point;
import java.awt.Color;

public class P3Test {
    //shape tests
	
	private static void compareToConvexPolygon () {
	    boolean filled = true;
	    ConvexPolygon cp1 = new ConvexPolygon (new Point[] {new Point(7,7),new Point (0,9),
		new Point (6,2)},Color.blue,filled);
		ConvexPolygon cp2 = new ConvexPolygon (new Point[] {new Point(7,7),new Point (0,9),
		new Point (-3,-5),new Point(2,-6), new Point(1257,0)},Color.blue,filled);
		System.out.println("Area = " + cp2.getArea());
		System.out.println (cp1.compareTo(cp2));
	}
	
	private static void RectConstruct () {
	    boolean filled = true;
	    Rectangle r = new Rectangle (4,2,new Point(0,0),Color.black,filled);
		System.out.println(r.getVertex(0));
		System.out.println("Area = " + r.getArea());
		r.setHeight(5);
		System.out.println("Height = " + r.getVertex(2));
	}
	
	private static void TriConstruct () {
	    boolean filled = true;
		Triangle t = new Triangle (new Point(0,0),new Point(5,0),new Point(0,5),Color.white,filled);
		System.out.println(t.getVertex(0));
		System.out.println(t.getVertex(1));
		System.out.println(t.getVertex(2));
		System.out.println(t.getArea());
	}

	
	public static void main (String args[]) {
	    compareToConvexPolygon();
		RectConstruct();
		TriConstruct();
	}
	
	
}
        