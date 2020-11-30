import java.util.Scanner;
/**
 * Class which contains Monster architecture and methods.
 *
 * @author Jared Spadaro
 * @version 5/27/13
 */

public class Monster extends RandomOccupant {
    
	/**
	 * Monster constructor.
	 * @param maze which monster is in
	 */
    public Monster (Maze maze) {
	    super(maze);
	}
	/**
	 * Monster constructor.
	 * @param maze which monster is in
	 * @param seed for random number generator
	 */
	public Monster (Maze maze, long seed) {
	    super(maze,seed);
	}
	/**
	 * Monster constructor.
	 * @param maze which monster is in
	 * @param location of monster
	 */
	public Monster (Maze maze, Square location) {
	    super(maze,location);
	}
	
	
}