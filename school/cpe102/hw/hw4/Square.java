/**
 * Class which contains Square architecture and methods.
 *
 * @author Jared Spadaro
 * @version 5/15/13
 */

public class Square {


    public static final int SQUARE_SIZE = 50;
    public static final int UP = 0;
    public static final int RIGHT = 1;
    public static final int DOWN = 2;
    public static final int LEFT = 3;
    private boolean isWall[] = new boolean[4];
    private boolean seen;
    private boolean inView;
    private int row;
    private int col;
    private Treasure treasure;
    /**
      * Square constructor.
      * @param boolean values for whether a wall is present
      * @param row and col which give position of square.
     */
    public Square (boolean up, boolean right, boolean down, boolean left, int row, int col) {
	isWall[0] = up;
	isWall[1] = right;
	isWall[2] = down;
	isWall[3] = left;
        this.row = row;
	this.col = col;
	seen = false;
	inView = false;
	treasure = null;
    }
    //Get whether wall is present in given direction
    public boolean wall (int direction) {
        return isWall[direction];
    }
	
    public boolean seen () {
        return seen;
    }
	
    public boolean inView () {
        return inView;
    }
	
    public int row () {
        return row;
    }
	
    public int col () {
        return col;
    }
	
    public Treasure treasure () {
        return treasure;
    }
	
    public int x () {
        return col * SQUARE_SIZE;
    }
	
    public int y () {
        return row * SQUARE_SIZE;
    }
    /** 
     * Set inView to given value, if true, set seen to true also.
     * @param value of inView
     */
    public void setInView (boolean inView) {
        this.inView = inView;
	if(inView==true) {
	    seen = true;
	}
    }
    /**
     * Set treasure to given input.
     * @param treasure parameter
     */
    public void setTreasure (Treasure t) {
	treasure = t;
    }
    /**
     * Set treasure to found if it exists.
     */
    public void enter () {
        if(treasure!=null) {
	    treasure.setFound();
	}
    }

}
