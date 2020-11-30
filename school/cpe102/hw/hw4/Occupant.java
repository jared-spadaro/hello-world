/**
 * Class which contains Occupant architecture and methods.
 *
 * @author Jared Spadaro
 * @version 5/15/13
 */

public abstract class Occupant {

    private Square location;
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
