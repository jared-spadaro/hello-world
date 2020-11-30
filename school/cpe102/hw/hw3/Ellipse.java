import java.awt.Point;
import java.awt.Color;

public class Ellipse extends Shape {

    //Instance variables
    private double semiMajorAxis;
    private double semiMinorAxis;
    private Point position;

    //Ellipse constructor
    public Ellipse (double semiMajorAxis, double semiMinorAxis, Point position, Color color, boolean filled) {
	super(color,filled);
	this.semiMajorAxis = semiMajorAxis;
	this.semiMinorAxis = semiMinorAxis;
	this.position = new Point (position.x,position.y);
    }
	
    //Accessor method for semiMajorAxis	
    public double getSemiMajorAxis () {
	return semiMajorAxis;
    }
	
    //Sets semiMajorAxis to given parameter	
    public void setSemiMajorAxis (double newAxis) {
	if (newAxis < semiMinorAxis) {
	    semiMajorAxis = semiMinorAxis;
            semiMinorAxis = newAxis; 
	}
	else {
            semiMajorAxis = newAxis;
	}
    }

    //Accessor method for semiMinorAxis	
    public double getSemiMinorAxis () {
	return semiMinorAxis;
    }
	
    public void setSemiMinorAxis (double newAxis) {
	if (newAxis > semiMajorAxis) {
	    semiMinorAxis = semiMajorAxis;
            semiMajorAxis = newAxis;
	}
	else {
            semiMinorAxis = newAxis;
	}
    }
	
    //Accessor method for position (center) of ellipse 
    public Point getPosition () {
	return new Point(position.x,position.y);
    }
	
    //Sets position of ellipse to given parameter
    public void setPosition (Point position) {
	this.position = new Point(position.x,position.y);
    }
	
    //Moves position of ellipse by given parameter
    public void move (Point delta) {
        position.x += delta.x;
	position.y += delta.y;
    }
	
    //Returns area of ellipse
    public double getArea () {
	return semiMajorAxis * semiMinorAxis * Math.PI;
    }
	
    //Overriden equals method. Calls super equals then compare instance variables	
    public boolean equals (Object e) {
	boolean isEqual = super.equals(e);
	return isEqual && semiMinorAxis == ((Ellipse)e).semiMinorAxis && 
	semiMajorAxis == ((Ellipse)e).semiMajorAxis && position.equals(((Ellipse)e).position);
    }
	
}
