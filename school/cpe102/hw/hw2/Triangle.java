import java.awt.Point;
import java.awt.Color;

public class Triangle implements Shape {
    //Instance variables
    private Point a;    
    private Point b;
    private Point c;
    private Color color;
    private boolean filled;
	
    //Methods mandated by Shape interface
	
    //Returns distance between two points
    private double distance (Point p1, Point p2) {
	return Math.sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
    }
	
    //Returns area of triangle
     public double getArea () {
	 double distAB = distance(a,b); //Distance between points a and b
	 double distBC = distance(b,c); //Distance between points b and c
	 double distAC = distance(a,c); //Distance between points a and c
	 double s = (distAB+distBC+distAC)/2;
	 return Math.sqrt(s*(s-distAB)*(s-distBC)*(s-distAC));
    }
	
    //Returns color of triangle
    public Color getColor () {
	return color;
    }
	
    //Sets color of triangle to parameter value
    public void setColor (Color color) {
	this.color = color;
    }
	
    //Returns filled value of triangle
    public boolean getFilled () {
	return filled;
    }
	
    //Sets filled value of triangle to parameter value
    public void setFilled (boolean filled) {
	this.filled = filled;
    }
	
    //Returns position of triangle (point a)
    public Point getPosition () {
	return a;
    }
	
    //Sets position of triangle by adding/subtracting the x/y difference between
    //position and point a
    public void setPosition (Point position) {
	if (position.x >= a.x) {
            b.x = (b.x+Math.abs(position.x-a.x));
	    c.x = (c.x+Math.abs(position.x-a.x));
	}
	else {
            b.x = (b.x-Math.abs(position.x-a.x));
	    c.x = (c.x-Math.abs(position.x-a.x));
	}
	if (position.y >= a.y) {
            b.y = (b.y+Math.abs(position.y-a.y));
	    c.y = (c.y+Math.abs(position.y-a.y));
        }
	else {
            b.y = (b.y-Math.abs(position.y-a.y));
	    c.y = (c.y-Math.abs(position.y-a.y));
        }
	a = position;
    }
	
    //Moves triangle's points by delta
     public void move (Point delta) {
	 a.x += delta.x;
	 a.y += delta.y;
	 b.x += delta.x;
	 b.y += delta.y;
	 c.x += delta.x;
	 c.y += delta.y;
    }
	
    //Methods unique to Triangle
	
    //Triangle constructor
    public Triangle (Point a, Point b, Point c, Color color, boolean filled) {
	this.a = a;
	this.b = b;
	this.c = c;
	this.color = color;
	this.filled = filled;
    }
	
    //Returns vertex a
    public Point getVertexA () {
	return a;
    }
	
    //Sets vertex a to parameter value
    public void setVertexA (Point point) {
	a = point;
    }
	
    //Returns vertex b
    public Point getVertexB () {
	return b;
    }
	
    //Sets vertex b to parameter value
    public void setVertexB (Point point) {
	b = point;
    }
	
    //Returns vertex c
    public Point getVertexC () {
	return c;
    }
	
    //Sets vertex c to parameter value
    public void setVertexC (Point point) {
        c = point;
    }
	
    //Equals method checks for null and for like classes, then checks for instance variable equality
    public boolean equals (Object t) {
        if (t==null) {
            return false;
	}
	if(this.getClass() != t.getClass()) {
            return false;
	}
		    
	return ((Triangle)t).a.x==this.a.x && ((Triangle)t).a.y==this.a.y && ((Triangle)t).b.x==this.b.x &&
        ((Triangle)t).b.y==this.b.y && ((Triangle)t).c.x==this.c.x && ((Triangle)t).c.y==this.c.y && 
        ((Triangle)t).color.equals(this.color) && ((Triangle)t).filled==this.filled;
    }
	    
	
}
	    
