import java.awt.Point;
import java.awt.Color;

public class Rectangle implements Shape {
    //Instance variables
    private int width;    
    private int height;
    private Point position;
    private Color color;
    private boolean filled;
	
    //Methods mandated by Shape interface
	
    //Returns area of rectangle
    public double getArea () {
	return width * height;
    }
	
    //Returns color of rectangle
    public Color getColor () {
	return color;
    }
	
    //Sets color of rectangle to parameter value
    public void setColor (Color color) {
	this.color = color;
    }
	
    //Returns filled value of rectangle
    public boolean getFilled () {
	return filled;
    }
	
    //Sets filled value of rectangle to parameter value
    public void setFilled (boolean filled) {
	this.filled = filled;
    }
	
    //Returns position of rectangle
    public Point getPosition () {
	return position;
    }
	
    //Sets position of rectangle to parameter value
    public void setPosition (Point position) {
	this.position = position;
    }
	
    //Moves rectangle by parameter value
    public void move (Point delta) {
	position.x += delta.x;
	position.y += delta.y;
    }
	
    //Methods unique to Rectangle
    	
    //Rectangle constructor	
    public Rectangle (int width, int height, Point position, Color color, boolean filled) {
	this.width = width;
        this.height = height;
	this.position = position;
	this.color = color;
	this.filled = filled;
    }
	
    //Returns width of rectangle
    public int getWidth () {
	return width;
    }
	
    //Sets width of rectangle to parameter value
    public void setWidth (int width) {
	this.width = width;
    }
	
    //Returns height of rectangle
    public int getHeight () {
	return height;
    }
	
    //Sets height of rectangle to parameter value
    public void setHeight (int height) {
	this.height = height;
    }
	
    //Equals method checks for null and for like classes, then checks for instance variable equality
    public boolean equals (Object r) {
	if (r==null) {
            return false;
	}
	if(this.getClass() != r.getClass()) {
            return false;
	}
	return ((Rectangle)r).width==width && ((Rectangle)r).height==height &&
        ((Rectangle)r).position.equals(position) &&
        ((Rectangle)r).color.equals(color) && ((Rectangle)r).filled==filled;
    }
	
}
	
