/**
 * Class which contains Explorer architecture and methods.
 *
 * @author Jared Spadaro
 * @version 5/15/13
 */


import java.awt.event.KeyEvent;

public class Explorer extends Occupant {

    private String name;
    private Maze maze;
	
    /**
     * Explorer constructor.
     *
     * @param location of explorer 
     * @param maze which explorer is in
     * @param name of explorer
     */
    public Explorer (Square location, Maze maze, String name) {
       super(location);
       this.name = name;
       this.maze = maze;
       maze.lookAround(location);
    }
    //Returns name of explorer
    public String name () {
        return name;
    }
    /**
     * Moves explorer according to key press.
     *
     * @param code for which key was pressed
     */
    public void move (int key) {
        int row = location().row();
	int col = location().col();
	if (key==KeyEvent.VK_KP_UP||key==KeyEvent.VK_UP) {
	    if(location().wall(0)==false) {
        	moveTo(maze.getSquare(row-1,col));
	    }
	 }
	 else if(key==KeyEvent.VK_KP_DOWN||key==KeyEvent.VK_DOWN) {
             if(location().wall(2)==false) {
                  moveTo(maze.getSquare(row+1,col));
             }
	 }
	 else if(key==KeyEvent.VK_KP_LEFT||key==KeyEvent.VK_LEFT) {
             if(location().wall(3)==false) {
                 moveTo(maze.getSquare(row,col-1));
             }
	 }
	 else if(key==KeyEvent.VK_KP_RIGHT||key==KeyEvent.VK_RIGHT) {
             if(location().wall(1)==false) {
                 moveTo(maze.getSquare(row,col+1));
             }
         }
	 else {
             //do nothing
	}
    }
    /**
     * Moves explorer to given square.
     *
     * @param square for explorer to move to
     */
    public void moveTo (Square s) {
        super.moveTo(s);
        s.enter();
        maze.lookAround(s);
    }
	
	
}
