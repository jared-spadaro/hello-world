import java.awt.Point;
import java.awt.Color;

public class Triangle extends ConvexPolygon {
	
    //Returns distance between two points
    private double distance (Point p1, Point p2) {
	return Math.sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
    }
	
    //Accessor method for vertex A
    public Point getVertexA () {
	return getVertex(0);
    }
	
    //Set vertex A to given parameter
    public void setVertexA (Point a) {
	setVertex(0,a);
    }

    //Accessor method for vertex B	
    public Point getVertexB () {
	return getVertex(1);
    }
	
    //Set vertex B to given parameter
    public void setVertexB (Point b) {
        setVertex(1,b);
    }
	
    //Accessor method for vertex C
    public Point getVertexC () {
	return getVertex(2);
    }
	
    //Set vertex C to given parameter
    public void setVertexC (Point c) {
	setVertex(2,c);
    }
	
    //Returns area of triangle
     public double getArea () {
	 double distAB = distance(getVertex(0),getVertex(1)); //Distance between points a and b
	 double distBC = distance(getVertex(1),getVertex(2)); //Distance between points b and c
	 double distAC = distance(getVertex(0),getVertex(2)); //Distance between points a and c
	 double s = (distAB+distBC+distAC)/2;
	 return Math.sqrt(s*(s-distAB)*(s-distBC)*(s-distAC));
    }
	
	
    //Triangle constructor
    public Triangle (Point a, Point b, Point c, Color color, boolean filled) {
	super(new Point[] {a,b,c},color,filled);
    }

}
	    
