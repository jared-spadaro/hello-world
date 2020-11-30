import java.awt.Point;
import java.awt.Color;

public class Rectangle extends ConvexPolygon {
    
    //Throws exception to prevent tampering with rectalinear structure
    public void setVertex (int index, Point vertex) {
	throw new UnsupportedOperationException();
    }

    //Returns height of rectangle	
    public int getHeight () {
	return getVertex(3).y - getVertex(0).y;
    }
	
    //Sets height of rectangle to given parameter
    public void setHeight (int height) {
	super.setVertex(2,new Point(getVertex(2).x,getVertex(1).y+height));
        super.setVertex(3,new Point(getVertex(3).x,getVertex(0).y+height));
    } 

    //Returns width of rectangle	
    public int getWidth () {
	return getVertex(1).x - getVertex(0).x;
    }

    //Sets width of rectangle to given parameter	
    public void setWidth (int width) {
	super.setVertex(1,new Point(getVertex(0).x+width,getVertex(1).y));
	super.setVertex(2,new Point(getVertex(3).x+width,getVertex(2).y));
    }
	
    	
    //Rectangle constructor	
    public Rectangle (int width, int height, Point position, Color color, boolean filled) {
	super(new Point[] {new Point(position.x,position.y), new Point(position.x+width,position.y),
        new Point (position.x+width,position.y+height),new Point (position.x,position.y+height)},color,filled);
    }
	
}
	
