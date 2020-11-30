/**
 * @author Jared Spadaro
 * @version Lab Quiz 1
 */

public class Box {
    private double width;
    private double height;
    private double depth;
    private static final double DEFAULT_WIDTH = 1.0;
    private static final double DEFAULT_HEIGHT = 1.0;
    private static final double DEFAULT_DEPTH = 1.0;
    
    Box () {
        width = DEFAULT_WIDTH;
        height = DEFAULT_HEIGHT;
        depth = DEFAULT_DEPTH;
    }

    Box (double width, double height, double depth) {
        if (width < 0) {
            width = 0;
        }
        if (height < 0) {
            height = 0;
        }
        if (depth < 0) {
            depth = 0;
        }
        this.width = width;
        this.height = height;
        this.depth = depth;
    }

    public double getWidth () {
        return width;
    }

    public double getHeight () {
        return height;
    }

    public double getDepth () {
        return depth;
    }

    public double getSurfaceArea () {
        return width*height + height*depth + width*depth;
    }

    public double getVolume () {
        return width * height * depth;
    }

    public boolean equals (Box b) {
        if (b!= null && b instanceof Box) {
           return b.width==width && b.height==height && b.depth==depth;
        }
        return false;
    }

    public String toString () {
        return ("width=" + width + ", height=" + height + ", depth=" + depth);
    }

}
        












