import java.awt.Point;
import java.awt.Color;

public class ConvexPolygon implements Shape {
    //Instance variables
    private Point[] vertices;
    private Color color;
    private boolean filled;
	
    //Methods mandated by Shape interface
	
    //Returns area of convex polygon
    public double getArea () {
	int i, sum1=0, sum2=0; //Represent the sums of cross-multiplication of the vertices
	for (i=1;i<vertices.length;i++) {
            sum1 += vertices[i-1].x * vertices[i].y;
	    sum2 += vertices[i-1].y * vertices[i].x;
	}
	sum1 += vertices[vertices.length-1].x * vertices[0].y;
	sum2 += vertices[vertices.length-1].y * vertices[0].x;
	return (sum1 - sum2) / 2;
    }
	
    //Returns color of convex polygon
    public Color getColor () {
	return color;
    }
	
    //Sets color of convex polygon to parameter value
    public void setColor (Color color) {
	this.color = color;
    }
	
    //Returns filled value of convex polygon
    public boolean getFilled () {
	return filled;
    }
	
    //Sets filled value of convex polygon to parameter value
    public void setFilled (boolean filled) {
	this.filled = filled;
    }
	
    //Return position of convex polygon (aka vertices[0])
    public Point getPosition () {
	return vertices[0];
    }
	
    //Set position of polygon by adding/subtracting x/y difference between position
    //and vertex (aka vertices[0])
    public void setPosition (Point position) {
	int i;
	for (i=1;i<vertices.length;i++) {
	    if (position.x >= vertices[0].x) {
	        vertices[i].x =  vertices[i].x+Math.abs(position.x-vertices[0].x);
	    }
	    else {
                vertices[i].x =  vertices[i].x-Math.abs(position.x-vertices[0].x);
            }
	    if (position.y >= vertices[0].y) {
	        vertices[i].y =  vertices[i].y+Math.abs(position.y-vertices[0].y);
	    }
	    else {
	        vertices[i].y =  vertices[i].y-Math.abs(position.y-vertices[0].y);
	    }
	}
	vertices[0] = position;
    }
	
    //Moves all of convex polygon's points by delta
    public void move (Point delta) {
	int i;
	for(i=0;i<vertices.length;i++) {
	    vertices[i].x += delta.x;
	    vertices[i].y += delta.y;
	}
    }
	
    //Methods unique to ConvextPolygon
	
    //Convex polygon constructor
    public ConvexPolygon (Point[] vertices, Color color, boolean filled) {
	this.vertices = vertices;
        this.color = color;
	this.filled = filled;
    }
	
    //Return vertex of convex polygon (aka vertices[0])
    public Point getVertex (int index) {
        return vertices[index];
    }
	
    //Sets a vertex (specified by index) to point parameter
    public void setVertex (int index, Point vertex) {
	vertices[index] = vertex;
    }
	
    //Equals method checks for null and for like classes, then checks for instance variable equality
    public boolean equals (Object p) {
	if (p==null) {
            return false;
	}
	if(this.getClass() != p.getClass()) {
	    return false;
	}
	int i;
	boolean isEqual = true;
	for(i=0;i<vertices.length;i++) {
	    if(((ConvexPolygon)p).vertices[i].x!=vertices[i].x||((ConvexPolygon)p).vertices[i].y!=vertices[i].y) {
	        isEqual = false;
	    }
	}
	return isEqual && ((ConvexPolygon)p).color.equals(color) && ((ConvexPolygon)p).filled==filled;
    }
	
	
}
