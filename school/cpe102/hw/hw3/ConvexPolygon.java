import java.awt.Point;
import java.awt.Color;
import java.util.Arrays;


public class ConvexPolygon extends Shape {
    //Instance variables
    private Point[] vertices;
	
	
    //Returns area of convex polygon
    public double getArea () {
	int i; 
	double sum1=0; 
	double sum2=0; //Represent the sums of cross-multiplication of the vertices
	for (i=1;i<vertices.length;i++) {
            sum1 += vertices[i-1].x * vertices[i].y;
	    sum2 += vertices[i-1].y * vertices[i].x;
	}
	sum1 += vertices[vertices.length-1].x * vertices[0].y;
	sum2 += vertices[vertices.length-1].y * vertices[0].x;
	return (sum1 - sum2) / 2;
    }
	
    //Return position of convex polygon (aka vertices[0])
    public Point getPosition () {
	return new Point(vertices[0].x,vertices[0].y);
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
	    vertices[i] = new Point(vertices[i].x,vertices[i].y);
	}
	vertices[0] = new Point(position.x,position.y);
    }
	
    //Moves all of convex polygon's points by delta
    public void move (Point delta) {
	int i;
	for(i=0;i<vertices.length;i++) {
	    vertices[i].x += delta.x;
	    vertices[i].y += delta.y;
	}
    }
	

    private void ArrayCopier (Point[] Old, Point[] New) {
	if(Old!=null && New!=null) {
            int i;
	    for (i=0;i<Old.length;i++) {
		 New[i] = new Point (Old[i].x,Old[i].y);
	    }
	}
    }
	
	
    //Convex polygon constructor
    public ConvexPolygon (Point[] vertices,Color color, boolean filled) {
	super(color,filled);
	Point verticesCopy[] = new Point[vertices.length];
	ArrayCopier(vertices,verticesCopy);
	this.vertices = verticesCopy;
    }
	
    //Return vertex of convex polygon (aka vertices[0])
    public Point getVertex (int index) {
	return new Point (vertices[index].x,vertices[index].y);
    }
	
	
    //Sets a vertex (specified by index) to point parameter
    public void setVertex (int index, Point vertex) {
	vertices[index] = new Point(vertex.x,vertex.y);
    }
	
    //Equals method checks for null and for like classes, then checks for instance variable equality
    public boolean equals (Object p) {
	if (p == null) {
	    return false;
	}
	if (getClass() != p.getClass()) {
            return false;
	}
	int i;
	boolean isEqual = true;
	for(i=0;i<vertices.length;i++) {
	    if(((ConvexPolygon)p).vertices[i].x!=vertices[i].x||((ConvexPolygon)p).vertices[i].y!=vertices[i].y) {
                isEqual = false;
	    }
        }
	return isEqual && getColor() == ((ConvexPolygon)p).getColor() && getFilled() == ((ConvexPolygon)p).getFilled();
    }
	
	
}
