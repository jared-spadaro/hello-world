import java.awt.Color;
import java.awt.Point;


public class Circle implements Shape {
    //Instance variables
    private double radius;
    private Point position;
    private Color color;
    private boolean filled;

    //Methods mandated by Shape interface

    //Returns area of circle
    public double getArea () {
	return Math.PI * radius * radius;
    }
	
    //Returns color of circle
    public Color getColor () {
	return color;
    }
	
    //Sets color of circle
    public void setColor (Color color) {
	int r = color.getRed();
	int g = color.getGreen();
	int b = color.getBlue();
	this.color = new Color (r,g,b);
    }
	
    //Returns filled value of circle
    public boolean getFilled () {
	return filled;
    }
	
    //Sets filled value of circle to parameter value
    public void setFilled (boolean filled) {
	this.filled = filled;
    }
	
    //Returns position (center) of circle
    public Point getPosition () {
	return this.position;
    }
	
    public void setPosition (Point position) {
	this.position.x = position.x;
        this.position.y = position.y;
    }
	
    //Moves center of circle
    public void move (Point delta) {
	position.x += delta.x;
        position.y += delta.y;
    }
	
    //Methods unique to circle
	
    //Constructs a circle
    public Circle (double radius, Point position, Color color, boolean filled) {
        this.radius = radius;
        this.position = position;
        this.color = color;
        this.filled = filled;
    }

    //Returns radius
    public double getRadius () {
	    return radius;
    }
	
    //Sets radius to parameter value
    public void setRadius (double radius) {
	this.radius = radius;
    }
	
    //For comparing doubles to a certain precision
    private boolean doubleEq (double x, double y) {
	if (Math.abs(x-y)<0.000001) {
            return true;
	}
	return false;
    }
	
    //Equals method checks for null and for like classes, then checks for instance variable equality
    public boolean equals (Object c) {
        if (c==null) {
            return false;
	}
	if(this.getClass() != c.getClass()) {
            return false;
	}
        return doubleEq(((Circle)c).radius,radius) && ((Circle)c).position.equals(this.position) 
        && ((Circle)c).color.equals(color) && ((Circle)c).filled==this.filled;
    }
	
	
}
