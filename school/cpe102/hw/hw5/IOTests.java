import java.io.*;

public class IOTests {

    private static void toTextTests () {
	    Square square = new Square (false,true,true,false,0,0);
		Square squares[][] = new Square[4][4];
		squares[0][0] = new Square (true,true,false,false,0,0);
		squares[0][1] = new Square (true,false,false,false,0,1);
		squares[0][2] = new Square (false,true,false,false,0,2);
		squares[0][3] = new Square (true,false,false,false,0,3);
		squares[1][0] = new Square (false,true,false,false,1,0);
		squares[1][1] = new Square (true,true,false,false,1,1);
		squares[1][2] = new Square (true,false,false,true,1,2);
		squares[1][3] = new Square (true,true,true,false,1,3);
		squares[2][0] = new Square (true,true,false,false,2,0);
		squares[2][1] = new Square (true,true,false,true,2,1);
		squares[2][2] = new Square (true,false,true,false,2,2);
		squares[2][3] = new Square (true,true,false,false,2,3);
		squares[3][0] = new Square (true,true,false,true,3,0);
		squares[3][1] = new Square (true,false,true,true,3,1);
		squares[3][2] = new Square (true,true,false,true,3,2);
		squares[3][3] = new Square (true,true,true,false,3,3);
		Maze maze = new Maze(squares,4,4);
		Explorer explorer = new Explorer (square,maze,"Benji Orion");
		Treasure treasure1 = new Treasure (maze);
		Treasure treasure2 = new Treasure (maze);
		Monster monster1 = new Monster (maze);
		Monster monster2 = new Monster (maze);
		maze.addRandomOccupant(treasure1);
		maze.addRandomOccupant(monster1);
		maze.addRandomOccupant(treasure2);
		maze.addRandomOccupant(monster2);
		maze.setExplorer(explorer);
		maze.getExplorer().moveTo(maze.getSquare(2,3));
		/*System.out.println(square.toText(','));
		System.out.println(explorer.toText(','));
		System.out.println(treasure1.toText(','));
		System.out.println(monster1.toText(','));*/
		//File f = new File ("testFile.txt");
		try {
            maze.writeMazeToFile("testFile.txt");
        }
        catch (IOException e) {
            System.out.println("Error");
        }
	}
	
	/*private static void toTextTestsAgain () {
	  Square fixedSquares[][] = new Square[5][5];
      fixedSquares[0][0] = new Square(true, false, false, true, 0, 0);
      fixedSquares[0][1] = new Square(true, false, true, false, 0, 1);
      fixedSquares[0][2] = new Square(true, false, true, false, 0, 2);
      fixedSquares[0][3] = new Square(true, false, false, false, 0, 3);
      fixedSquares[0][4] = new Square(true, true, false, false, 0, 4);
      fixedSquares[1][0] = new Square(false, false, true, true, 1, 0);
      fixedSquares[1][1] = new Square(true, false, true, false, 1, 1);
      fixedSquares[1][2] = new Square(true, true, false, false, 1, 2);
      fixedSquares[1][3] = new Square(false, true, false, true, 1, 3);
      fixedSquares[1][4] = new Square(false, true, false, true, 1, 4);
      fixedSquares[2][0] = new Square(true, false, false, true, 2, 0);
      fixedSquares[2][1] = new Square(true, false, true, false, 2, 1);
      fixedSquares[2][2] = new Square(false, true, false, false, 2, 2);
      fixedSquares[2][3] = new Square(false, true, false, true, 2, 3);
      fixedSquares[2][4] = new Square(false, true, false, true, 2, 4);
      fixedSquares[3][0] = new Square(false, true, false, true, 3, 0);
      fixedSquares[3][1] = new Square(true, false, false, true, 3, 1);
      fixedSquares[3][2] = new Square(false, true, false, false, 3, 2);
      fixedSquares[3][3] = new Square(false, true, true, true, 3, 3);
      fixedSquares[3][4] = new Square(false, true, false, true, 3, 4);
      fixedSquares[4][0] = new Square(false, true, true, true, 4, 0);
      fixedSquares[4][1] = new Square(false, true, true, true, 4, 1);
      fixedSquares[4][2] = new Square(false, false, true, true, 4, 2);
      fixedSquares[4][3] = new Square(true, false, true, false, 4, 3);
      fixedSquares[4][4] = new Square(false, true, true, false, 4, 4);
	  //resetFixedSquares();
	  Maze maze, maze2;
	  Explorer ex;
      Treasure t1, t2;
      Monster m1, m2;
      maze = new Maze(fixedSquares, 5, 5);
      ex = new Explorer(fixedSquares[0][0], maze, "Scary Name");
      t1 = new Treasure(maze, fixedSquares[4][4]);      
      t2 = new Treasure(maze, fixedSquares[2][2]);
      m1 = new Monster(maze, fixedSquares[4][4]);
      m2 = new Monster(maze, fixedSquares[3][3]);
      t1.setFound();
      maze.addRandomOccupant(t1);
      maze.addRandomOccupant(t2);
      maze.addRandomOccupant(m1);
      maze.addRandomOccupant(m2);
      maze.setExplorer(ex);    
      try {
	      maze.writeMazeToFile("jared.txt");
	  }
	  catch (IOException e) {
	  }
	}*/
	  
	
	public static void main (String args[]) {
	     toTextTests();
		 //  toTextTestsAgain();
	}
	
}
