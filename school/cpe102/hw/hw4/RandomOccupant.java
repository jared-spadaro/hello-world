/**
 * Class which contains Random Occupant architecture and methods.
 *
 * @author Jared Spadaro
 * @version 5/15/13
 */

    import java.util.Random;

    public abstract class RandomOccupant extends Occupant {

    private Random numGenerator;
    private Maze maze;
    /**
     * Random occupant constructor.
     * @param maze which random occupant is in
     */
    public RandomOccupant (Maze maze) {
	super();
	this.maze = maze;
	numGenerator = new Random();
	moveTo(maze.getSquare(numGenerator.nextInt(maze.rows()),numGenerator.nextInt(maze.cols())));
    }
    /**
     * Random occupant consturctor.
     * @param maze which random occupant is in
     * @param seed for random number generator
     */
    public RandomOccupant (Maze maze, long seed) {
        super();
	this.maze = maze;
	numGenerator = new Random(seed);
	moveTo(maze.getSquare(numGenerator.nextInt(maze.rows()),numGenerator.nextInt(maze.cols())));
    }
    /**
     * Random occupant constructor.
     * @param maze which random occupant is in
     * @param location of random occupant
     */
    public RandomOccupant (Maze maze, Square location) {
       super();
       this.maze = maze;
       numGenerator = new Random();
       moveTo(location);
    }
    /**
     * Moves random occupant, randomly, using random number generator.
     */
    public void move () {
        int row = location().row();
        int col = location().col();
	int i = numGenerator.nextInt(4);
	while(location().wall(i)==true) {
	    i = numGenerator.nextInt(4);
	}
	if (i==location().UP) {
	    row-=1;
        }
	else if (i==location().DOWN) { 
            row+=1;
	}
	else if (i==location().LEFT) {
            col-=1;
	}
	else if (i==location().RIGHT) {
	    col+=1;
	}
	Square s = maze.getSquare(row,col);
	moveTo(s);
    }
	
}
    
