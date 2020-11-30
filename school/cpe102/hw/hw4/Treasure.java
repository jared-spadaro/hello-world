/**
 * Class which contains Treasure architecture and methods.
 *
 * @author Jared Spadaro
 * @version 5/15/13
 */

public class Treasure extends RandomOccupant {

    private boolean found;
    /**
    * Treasure constructor.
    * @param maze which treasure is in
    */
    public Treasure (Maze maze) {
       super(maze);
       found = false;
       location().setTreasure(this);
    }
    /**
     * Treasure constructor.
     * @param maze which treasure is in
     * @param seed for random number generator
     */
    public Treasure (Maze maze, long seed) {
        super(maze,seed);
        found = false;
        location().setTreasure(this);
    }
    /**
     * Treasure constructor.
     * @param maze which treasure is in
     * @param starting location of treasure
     */
    public Treasure (Maze maze, Square location) {
       super(maze,location);
       found = false;
       location().setTreasure(this);
    }
    //get method for found
    public boolean found () {
        return found;
    }
    //Set found to true
    public void setFound () {
       found = true;
    }
    //Override random occupant's move method because treasure don't move randomly
    public void move () {
	
    }
	
}
