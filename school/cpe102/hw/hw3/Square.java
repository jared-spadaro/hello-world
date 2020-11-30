import java.awt.Point;
import java.awt.Color;

public class Square extends Rectangle {

    /**
     * Constructs a square.
     *
     * @param length of the sides of the square
     *
     * @param position of square (lower left corner)
     *
     * @param color of square
     *
     * @param boolean value representing whether shape is filled
     */

    public Square (int sideLength, Point position, Color color, boolean filled) {
	super(sideLength,sideLength,position,color,filled);
    }
	
    /**
     * Returns the side length of the square.
     *
     * @return side length of square
     */

    public int getSize () {
	return getVertex(1).x - getVertex(0).x;
    }

    /**
     * Sets the side length of the square to given parameter.
     *
     * @param new side length
     */
	
    public void setSize (int size) {
	super.setHeight(size);
	super.setWidth(size);
    }

    /**
     * Overrides setHeight from class Rectangle to set all sides
     * of square to given parameter.
     *
     * @param new side length
     */
	
    public void setHeight (int size) {
	super.setHeight(size);
	super.setWidth(size);
    }

    /**
     * Overrides setWidth from class Rectangle to set all sides
     * of square to given parameter.
     *
     * @param new side length
     */	
	
    public void setWidth (int size) {
	super.setHeight(size);
	super.setWidth(size);
    }
	
}
