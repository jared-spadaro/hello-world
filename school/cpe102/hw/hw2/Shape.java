/** This is the interface Shape, which is extends by all other classes in this library except
 *  for Canvas. This interface provides several methods that are shared amongst the members
 *  of this library (Circle, Rectangle, Triangle, and ConvexPolygon).
 *  @author Jared Spadaro  jared458@gmail.com
 */


import java.awt.Color;
import java.awt.Point;


public interface Shape {

    /**
     * Calculates and returns the area of the shape. 
     *
     * @return Area of shape
     */
	 
    public double getArea ();
	
    /**
     * Returns the color of the shape.
     *
     * @return Color of shape
     */
	
     public Color getColor ();
	
     /**
      * Sets the color of the shape.
      *
      * @param The color that the shape will be set to
      */
	
    public void setColor (Color color);
	
    /**
      * Returns true if the shape is filled, otherwise false. 
      * 
      * @return Boolean value for whether shape is filled
      */
	
    public boolean getFilled ();
	
    /**
      * Sets the filled state of the shape to the specified value.
      *
      * @param Boolean value for whether shape will be filled
      */
	
    public void setFilled (boolean filled);
	
     /**
      * Returns the current position of the shape.
      *
      * @return Position of shape
      */
	
    public Point getPosition ();
	
    /**
      * Changes the position of the shape to the specified point.
      *
      * @param Point to which shape will move to
      */
	
    public void setPosition (Point position);
	
    /**
      * Moves the shape by the x and y amounts specified (in the Point delta).
      *
      * @param Point delta (shape will move by x and y values of delta)
      */
	
    public void move (Point delta);

}
