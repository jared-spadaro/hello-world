import java.util.Scanner;
/**
 * Class which contains Treasure architecture and methods.
 *
 * @author Jared Spadaro
 * @version 5/27/13
 */

public class Treasure extends RandomOccupant {

    private boolean found;
	
	/**
     * Converts object to a string with given delimiter.
     * @param delimiter to separate elements of object
     */ 
	public String toText (char delimiter) {
	     return super.toText(delimiter) + delimiter + found;
	} 
	
	/**
	 * Converts string to an object with given scanner input.
	 * @param scanner which carries string to be converted
	 */
	public void toObject (Scanner input) {
	    super.toObject(input);
		if(input.hasNextBoolean()) {
		    found = input.nextBoolean();
		}
        else {
            throw new IllegalArgumentException();
        } 
		input.close();
	}
	
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
	
	/**
	 * Override occupant's moveTo method to remove treasure from location,
	 * move to new location, then place this treasure there.
	 * @param new location
	 */
	public void moveTo (Square newLoc) {
	    if (location()!=null) {
			location().setTreasure(null);
		}
		super.moveTo(newLoc);
		newLoc.setTreasure(this);
	}
	
}