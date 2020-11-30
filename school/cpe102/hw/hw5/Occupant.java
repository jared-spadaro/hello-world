import java.util.Scanner;

/**
 * Class which contains Occupant architecture and methods.
 *
 * @author Jared Spadaro
 * @version 5/27/13
 */

public abstract class Occupant implements DelimitedTextIO {

    private Square location;
	
	/**
	 * Converts object to a string.
	 * @param delimiter for elements of object
	 */
	public String toText (char delimiter) {
		return getClass().getName() + delimiter + location.row() + delimiter + location.col();
	}
	
	
	
	/**
	 * Default occupant constructor.
	 */
	public Occupant () {
	   
	}
	/**
	 * Occupant constructor.
	 * @param location of occupant
     */ 
	public Occupant (Square start) {
	    location = start;
	}
	
	//Return location
	public Square location () {
	    return location;
	}
	/**
	 * Move explorer to given square.
	 * @param location for explorer to move to
	 */
	public void moveTo (Square newLoc) {
	    location = newLoc;
	}
	
}