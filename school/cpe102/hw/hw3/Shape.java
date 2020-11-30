/** This is the interface Shape, which is extends by all other classes in this library except
 *  for Canvas. This interface provides several methods that are shared amongst the members
 *  of this library (Circle, Rectangle, Triangle, and ConvexPolygon).
 *  @author Jared Spadaro  jared458@gmail.com
 */

//TEST


import java.awt.Color;
import java.awt.Point;
import java.lang.Comparable;


public abstract class Shape implements Comparable<Shape> {

    private Color color;
	private boolean filled;
	
	
	/** 
	 * Constructs shape
	 *
	 * @param color value for shape
	 *
	 */
	 
	public Shape (Color color, boolean filled) {
	    this.color = color;
		this.filled = filled;
	}
	
	
    /**
	 * Calculates and returns the area of the shape. 
	 *
	 * @return Area of shape
	 */
	 
    public abstract double getArea ();
	
	/**
	 * Returns the color of the shape.
	 *
	 * @return Color of shape
	 */
	
	public Color getColor () {
	    return color;
	}
	
    /**
	 * Sets the color of the shape.
	 *
	 * @param The color that the shape will be set to
	 */
	
	public void setColor (Color color) {
	    this.color = color;
	}
	
	/**
	 * Returns true if the shape is filled, otherwise false. 
	 * 
	 * @return Boolean value for whether shape is filled
	 */
	
	public boolean getFilled () {
	    return filled;
    }
	
	/**
	 * Sets the filled state of the shape to the specified value.
	 *
	 * @param Boolean value for whether shape will be filled
	 */
	
	public void setFilled (boolean filled) {
	    this.filled = filled;
	}
	
	/**
	 * Returns the current position of the shape.
	 *
	 * @return Position of shape
	 */
	
	public abstract Point getPosition ();
	
	/**
	 * Changes the position of the shape to the specified point.
	 *
	 * @param Point to which shape will move to
	 */
	
	public abstract void setPosition (Point position);
	
	/**
	 * Moves the shape by the x and y amounts specified (in the Point delta).
	 *
	 * @param Point delta (shape will move by x and y values of delta)
	 */
	
	public abstract void move (Point delta);
	
	/**
	 * Compares two Shapes, first by their names, and, if those are equal, by area.
	 *
	 * @param Shape to compare to. 
	 *
	 * @return Negative value if parameter shape is greater, positive value if paramter shape
	 * is less than, or 0 if parameter shape equals shape.
	 */
	 
	public int compareTo (Shape b) {
	    String classNameA = getClass().getName();
		String classNameB = b.getClass().getName();
		if (classNameA.compareTo(classNameB) < 0) {
		    return -1;
		}
		else if (classNameA.compareTo(classNameB) > 0) {
		    return 1;
		}
		else {
		    if (getArea() < ((Shape)b).getArea()) {
			    return -1;
			}
			else if (getArea() > ((Shape)b).getArea()) {
			    return 1;
			}
			else {
			    return 0;
			}
		} 
	}
	
	/**
	 * Compares two shapes by their common instance variables.
	 *
	 * @param Shape to compare to.
	 *
	 * @return True if the shapes are equal, false otherwise.
	 */
	 
	public boolean equals (Object s) {
	    if (s == null) return false;
		if (!getClass().equals(s.getClass())) return false;
		Shape shape = (Shape)s;
		return color == shape.color && filled == shape.filled;
	}
}