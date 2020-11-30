import java.awt.Point;
import java.awt.Color;
import java.util.ArrayList;

public class Canvas {
    //Instance variable 
    private ArrayList<Shape> shapes = new ArrayList<Shape>();
	
    /**
     * Constructs a canvas.
     */

    public Canvas () {
	this.shapes = shapes;
    }
	
    /**
     * Adds a shape to the array list "shapes.".
     * 
     * @param Shape to be added
     */

    public void add (Shape shape) {
        shapes.add(shape);
    }
	
    /**
     * Returns shape at given index and then removes it from arraylist.
     *
     * @param index to indicate which shape will be returned/removed
     *
     * @return shape at given index
     */

    public Shape remove (int index) {
        if (index<0 || index>shapes.size()) {
            return null;
	}
	Shape s = (shapes.get(index));
	shapes.remove(index);
	return s;
    }
	
    /**
     * Returns shape at given index of arraylist.
     *
     * @param index to indicate which shape will be returned
     *
     * @return shape at given index
     */

    public Shape get (int index) {
        return shapes.get(index);
    }
	
    /**
     * Returns size of arraylist.
     * 
     * @return size of shapes array
     */

    public int size () {
        return shapes.size();
    }
	
     /**
      * Fills new arraylist with just circles.
      *
      * @return arraylist with just circles
      */

     public ArrayList<Circle> getCircles () {
	int i;
	ArrayList <Circle> circles = new ArrayList<Circle>();
	for (i=0;i<shapes.size();i++) {
            if(shapes.get(i) instanceof Circle) {
	        circles.add((Circle)shapes.get(i));
	    }
	}
	return circles;
    }
	
    /**
     * Fills new arraylist with just rectangles.
     *
     * @return arraylist with just rectangles
     */

    public ArrayList<Rectangle> getRectangles () {
        int i;
	ArrayList <Rectangle> rectangles = new ArrayList<Rectangle>();
	for (i=0;i<shapes.size();i++) {
            if(shapes.get(i).getClass().equals(Rectangle.class)) {
	        rectangles.add((Rectangle)shapes.get(i));
	    }
        }
	return rectangles;
    }
	
    /**
     * Fills new arraylist with just triangles.
     *
     * @return arraylist with just triangles
     */

    public ArrayList<Triangle> getTriangles () {
        int i;
	ArrayList <Triangle> triangles = new ArrayList<Triangle>();
	for (i=0;i<shapes.size();i++) {
            if(shapes.get(i) instanceof Triangle) {
                 triangles.add((Triangle)shapes.get(i));
	    }
        }
	return triangles;
    }
	
    /**
     * Fills new arraylist with just convex polygons.
     *
     * @return arraylist with just convex polygons
     */

    public ArrayList <ConvexPolygon> getConvexPolygons () {
	int i;
	ArrayList <ConvexPolygon> convexpolygons = new ArrayList<ConvexPolygon>();
	for (i=0;i<shapes.size();i++) {
            if(shapes.get(i).getClass().equals(ConvexPolygon.class)) {
                convexpolygons.add((ConvexPolygon)shapes.get(i));
	    }
        }
	return convexpolygons;
    }
	
    /**
     * Fills new arraylist with just shapes that have the same color as specified.
     * 
     * @param color of shapes to be added
     *
     * @return arraylist with just shapes of given color 
     */

    public ArrayList <Shape> getShapesByColor (Color color) {
	int i;
	ArrayList <Shape> ColorShapes = new ArrayList<Shape>();
	for (i=0;i<shapes.size();i++) {
            if(shapes.get(i).getColor() == color) {
	        ColorShapes.add(shapes.get(i));
	    }
        }
	return ColorShapes;
    }	    
	
    /**
     * Returns the sum of the area of all shapes in the arraylist "shapes."
     *
     * @return sum of the area of all shapes in arraylist "shapes"
     */

    public double getAreaOfAllShapes () {
	double totalArea=0;
	int i;
	for (i=0;i<shapes.size();i++) {
            totalArea += shapes.get(i).getArea();
	}
	    return totalArea;
    }
	
	
}
