import java.awt.Color;
import java.awt.Point;


public class Circle extends Ellipse {


    //Constructs a circle
    public Circle (double radius, Point position, Color color, boolean filled) {
	super(radius,radius,position,color,filled);
    }
	
    public double getRadius () {
	return getSemiMajorAxis();
    }
	
    public void setRadius (double radius) {
	super.setSemiMinorAxis(radius);
	super.setSemiMajorAxis(radius);
    }

    public void setSemiMajorAxis (double newAxis) {
        super.setSemiMajorAxis(newAxis);
	super.setSemiMinorAxis(newAxis);
    }
	
    public void setSemiMinorAxis (double newAxis) {
	super.setSemiMinorAxis(newAxis);
	super.setSemiMajorAxis(newAxis);
    }

}
