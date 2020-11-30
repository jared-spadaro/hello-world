
/**
 * Class that contains all the logic to model a Maze with Treasures, Monsters, and an Explorer.
 * 
 * @author Jared Spadaro 
 * @version 5/11/13
 */
 
import java.util.*;
 
public class Maze
{
   // named constants
   public static final int ACTIVE = 0;
   public static final int EXPLORER_WIN = 1;
   public static final int MONSTER_WIN = 2;
    
    // instance variables
   private Square[][] maze;
   private ArrayList<RandomOccupant> randOccupants;
   private Explorer explorer;
   private int rows;
   private int cols;

   /**
    * Constructor for objects of class Maze
    */
   public Maze(Square[][] maze, int rows, int cols)
   {
       this.maze = maze;
       this.rows = rows;
       this.cols = cols;	
       randOccupants = new ArrayList<RandomOccupant>();
   }
	
   // QUERIES
   public Square getSquare(int row, int col) { return maze[row][col]; }
   public int rows() {return rows;}
   public int cols() {return cols;}
   public String explorerName() {return explorer.name();}
   public Explorer getExplorer() {return explorer;}
    
    /**
     * Returns object at given index.
     * @return object at index
     */
    public RandomOccupant getRandomOccupant(int index) {
        return randOccupants.get(index);
    }
    /**
     * Returns size of the randOccupants arraylist.
     * @return size of arraylist
     */
    public int getNumRandOccupants() {
        return randOccupants.size();
    }
	
   // COMMANDS
    /**
     * Add parameter to randOccupants arraylist.
     * @param object to add
     */
    public void addRandomOccupant(RandomOccupant ro) {
        randOccupants.add(ro);   
    }
	
    public void setExplorer(Explorer e) {explorer = e;}
	
    public void explorerMove(int key)
    {
       explorer.move(key);
    }
   /**
    * Randomly moves all random occupants in arraylist.
    */
   public void randMove()
   {
       int i;
       for(i=0;i<getNumRandOccupants();i++) {
      	  getRandomOccupant(i).move();
       }
   }
	
   /**
    * Returns the status of the game.
    *
    * If all treasures have been found, return EXPLORER_WIN.
    * If not, check each maze occupant, if it is a Monster and
    *   it is in the same location as the Explorer, return
    *   MONSTER_WIN.  Note that you can use == to check locations, do you know why?
    * Otherwise, return ACTIVE.
    */
   public int gameStatus()
   {
      int status = ACTIVE;
      int i;
		
      if(foundAllTreasures()==true) {
          return EXPLORER_WIN;
      }
      for(i=0;i<getNumRandOccupants();i++) {
          if(getRandomOccupant(i) instanceof Monster) {
	      if(getRandomOccupant(i).location()==explorer.location()) {
	          return MONSTER_WIN;
	      }
	  }
      }
      return status;
   }
   /**
    * Checks all treasures to see if they have been found.
    * If yes, return true, otherwise return false.
    * @return boolean foundAll
    */ 
   private boolean foundAllTreasures()
   {
      boolean foundAll = true;
      //int numFound=0;
      int i,j;
      ArrayList<Treasure> treasures = new ArrayList<Treasure>();      
      for(i=0;i<getNumRandOccupants();i++) {
          if(getRandomOccupant(i) instanceof Treasure) {
              treasures.add((Treasure)getRandomOccupant(i));   
	  }
      }
      for(j=0;j<treasures.size();j++) {
          if(treasures.get(j).found()==false) {
              foundAll = false;
	  }
      }
      return foundAll;
   }
    /**
     * Look around the given square to see what is visible 
     * and what is not.
     * @param square to look around from
     */
   public void lookAround(Square s)
   {
      int row = s.row();
      int col = s.col();
        
      // Clear what was previously in view
      resetInView();
        
      // Set the current square so that we are viewing it (obviously)
      s.setInView(true);
        
      if(row>0) {
          if(s.wall(s.UP)==false) {
	      maze[row-1][col].setInView(true);
	  }
      }
	  
      if(row<rows-1) {
	  if(s.wall(s.DOWN)==false) {
	    maze[row+1][col].setInView(true);
	  }
      }
	  
      if(col<cols-1) {
	   if(s.wall(s.RIGHT)==false) {
	       maze[row][col+1].setInView(true);
	    }
      }
	  
      if(col>0) {
	   if(s.wall(s.LEFT)==false) {
	       maze[row][col-1].setInView(true);
	   }
      }
      //upper left
      if(col>0&&row>0) {
	  if((maze[row-1][col-1].wall(s.DOWN)==false||maze[row-1][col-1].wall(s.RIGHT)==false)
	  &&(maze[row][col].wall(s.LEFT)==false||maze[row][col].wall(s.UP)==false)) {
	  maze[row-1][col-1].setInView(true);
          }
      }
      //upper right
      if(row>0&&col<cols-1) {
	  if((maze[row-1][col+1].wall(s.DOWN)==false||maze[row-1][col+1].wall(s.LEFT)==false)
	  &&(maze[row][col].wall(s.UP)==false||maze[row][col].wall(s.RIGHT)==false)&&
	  (maze[row-1][col].wall(s.RIGHT)==false||maze[row][col].wall(s.RIGHT)==false)) {
	  maze[row-1][col+1].setInView(true);
	  }
       }
       //lower left
       if(col>0&&row<rows-1) {
	   if((maze[row+1][col-1].wall(s.UP)==false||maze[row+1][col-1].wall(s.RIGHT)==false)
           &&(maze[row][col].wall(s.DOWN)==false||maze[row][col].wall(s.LEFT)==false)&&
	   (maze[row+1][col].wall(s.LEFT)==false||maze[row][col].wall(s.LEFT)==false)) {
	        maze[row+1][col-1].setInView(true);
	    }
        }
	//lower right
	if(row<rows-1&&col<cols-1) {
	    if((maze[row+1][col+1].wall(s.UP)==false||maze[row+1][col+1].wall(s.LEFT)==false)
	    &&(maze[row][col].wall(s.DOWN)==false||maze[row][col].wall(s.RIGHT)==false)) {
	    maze[row+1][col+1].setInView(true);
	    }    
        }
   }
   /**
    * Resets the inView of all squares in the maze to false.
    */
   private void resetInView()
   {
      for (int i = 0; i<rows; i++) {
         for (int j = 0; j<cols; j++) {
            maze[i][j].setInView(false);
         }
      }
   }
}
