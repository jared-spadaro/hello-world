import java.lang.reflect.*;
import java.awt.event.KeyEvent;
import java.util.ArrayList;
import java.util.Scanner;
import java.io.*;

/**
 * Class to Test the Maze Game Project with File Read/Write Capabilities
 * 
 * @author Julie Workman
 * @version Version 2.0
 * @version May 19, 2013  
 * 
 * <br>Revisions:
 *    <br>1.0 Initial version.
 */
public class P5TestDriver
{
   private static final String RESULTS_FOR = "Results for Program 5";
   private static Square[][] fixedSquares = new Square[5][5];
   
   public static void main(String[] args)
   {
      boolean pass = true;
      
      printHeader(args);
      
      // Architecture tests...
      //
      pass &= testOccupantArch();
      pass &= testRandomOccArch();
      pass &= testExplorerArch();
      pass &= testMonsterArch();
      pass &= testTreasureArch();
      pass &= testDrawableExplorerArch();
      pass &= testDrawableMonsterArch();
      pass &= testDrawableTreasureArch();
      pass &= testSquareArch();
      pass &= testDrawableSquareArch();
      pass &= testMazeArch();
      pass &= testDrawableMazeArch();
      
      // Set up maze for unit tests
      resetFixedSquares();
      
      // Unit Tests...
      //
      try
      {
         pass &= testSquare();
      }
      catch (Exception e)
      {
         pass &= false;
         System.out.println("FAILED, runtime exception testing Square");
         e.printStackTrace();
      }

      try
      {
         pass &= testRandomOccupant();
      }
      catch (Exception e)
      {
         pass &= false;
         System.out.println("FAILED, runtime exception testing RandomOccupant");
         e.printStackTrace();
      }
      
      try
      {
         pass &= testExplorer();
      }
      catch (Exception e)
      {
         pass &= false;
         System.out.println("FAILED, runtime exception testing Explorer");
         e.printStackTrace();
      }
      
      try
      {
         pass &= testMonster();
      }
      catch (Exception e)
      {
         pass &= false;
         System.out.println("FAILED, runtime exception testing Monster");
         e.printStackTrace();
      }
      
      try
      {
         pass &= testTreasure();
      }
      catch (Exception e)
      {
         pass &= false;
         System.out.println("FAILED, runtime exception testing Treasure");
         e.printStackTrace();
      }
      
      try
      {
         pass &= testMaze();
      }
      catch (Exception e)
      {
         pass &= false;
         System.out.println("FAILED, runtime exception testing Maze");
         e.printStackTrace();
      }
      
      try
      {
         pass &= testMazeReadWrite();
      }
      catch (Exception e)
      {
         pass &= false;
         System.out.println("FAILED, runtime exception testing Maze");
         e.printStackTrace();
      }
      
      
      printResults(pass);
   }
   
   //-------------------------------------- Architecture Tests --------------------------------
   
   private static boolean testOccupantArch()
   {
      boolean pass = true;
      int test = 1;
      int cnt;
      Class cl = Occupant.class;
      
      System.out.println("Occupant architecture tests...");

      pass &= test(cl.getConstructors().length == 2, test++);  // Test 1   
      pass &= test((cl.getInterfaces()).length == 1, test++);  // Test 2
      pass &= test((cl.getSuperclass()).getName().equals("java.lang.Object"), test++);  // Test 3 
      cnt = countModifiers(cl.getDeclaredMethods(), Modifier.PUBLIC);     
      pass &= test(cnt == 3, test++);  // Test 4
      
      cnt = cl.getFields().length;
      pass &= test(cnt == 0, test++);  // Test 5 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED);
      pass &= test(cnt == 0, test++);  // Test 6 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE);
      pass &= test(cnt == 1, test++);  // Test 7 
      
      // Count and test number of of PACKAGE fields
      cnt = cl.getDeclaredFields().length
          - countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE)
          - countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED)
          - countModifiers(cl.getDeclaredFields(), Modifier.PUBLIC);
      pass &= test(cnt == 0, test++);  // Test 8 

      return pass;
   }
   
   private static boolean testRandomOccArch()
   {
      boolean pass = true;
      int test = 1;
      int cnt;
      Square[][] squares = new Square[1][1];
      Maze maze = new Maze(squares, 1, 1);
      
      Class cl = RandomOccupant.class;
      
      System.out.println("RandomOccupant architecture tests...");

      pass &= test(cl.getConstructors().length == 3, test++);  // Test 1   
      pass &= test((cl.getInterfaces()).length == 0, test++);  // Test 2  
      pass &= test((cl.getSuperclass()).getName().equals("Occupant"), test++);  // Test 3 
      
      cnt = countModifiers(cl.getDeclaredMethods(), Modifier.PUBLIC);     
      pass &= test(cnt == 2, test++);  // Test 4 
      
      cnt = cl.getFields().length;
      pass &= test(cnt == 0, test++);  // Test 5 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED);
      pass &= test(cnt == 0, test++);  // Test 6 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE);
      pass &= test(cnt == 2, test++);  // Test 7 
      
      // Count and test number of of PACKAGE fields
      cnt = cl.getDeclaredFields().length
          - countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE)
          - countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED)
          - countModifiers(cl.getDeclaredFields(), Modifier.PUBLIC);
      pass &= test(cnt == 0, test++);  // Test 8 

      return pass;
   }

   private static boolean testExplorerArch()
   {
      boolean pass = true;
      int test = 1;
      int cnt;
      Explorer ex;
      Square square = new Square(true, true, true, true, 0, 0);
      Square[][] squares = new Square[1][1];
      squares[0][0] = square;
      Maze maze = new Maze(squares, 1, 1);
      
      Class cl;
      
      System.out.println("Explorer architecture tests...");
      
      ex = new Explorer(square, maze, "name");
      
      cl = ex.getClass();

      pass &= test(cl.getConstructors().length == 2, test++);  // Test 1   
      pass &= test((cl.getInterfaces()).length == 0, test++);  // Test 2  
      pass &= test((cl.getSuperclass()).getName().equals("Occupant"), test++);  // Test 3 
      
      cnt = countModifiers(cl.getDeclaredMethods(), Modifier.PUBLIC);     
      pass &= test(cnt == 5, test++);  // Test 4 
      
      cnt = cl.getFields().length;
      pass &= test(cnt == 0, test++);  // Test 5 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED);
      pass &= test(cnt == 0, test++);  // Test 6 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE);
      pass &= test(cnt == 2, test++);  // Test 7 
      
      // Count and test number of of PACKAGE fields
      cnt = cl.getDeclaredFields().length
          - countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE)
          - countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED)
          - countModifiers(cl.getDeclaredFields(), Modifier.PUBLIC);
      pass &= test(cnt == 0, test++);  // Test 8 

      return pass;
   }
   
   private static boolean testMonsterArch()
   {
      boolean pass = true;
      int test = 1;
      int cnt;
      Monster mon;
      Square[][] squares = new Square[1][1];
      Maze maze = new Maze(squares, 1, 1);
      
      Class cl;
      
      System.out.println("Monster architecture tests...");
      
      mon = new Monster(maze, 0);
      
      cl = mon.getClass();

      pass &= test(cl.getConstructors().length == 3, test++);  // Test 1   
      pass &= test((cl.getInterfaces()).length == 0, test++);  // Test 2  
      pass &= test((cl.getSuperclass()).getName().equals("RandomOccupant"), test++);  // Test 3 
      
      cnt = countModifiers(cl.getDeclaredMethods(), Modifier.PUBLIC);     
      pass &= test(cnt == 0, test++);  // Test 4 
      
      cnt = cl.getFields().length;
      pass &= test(cnt == 0, test++);  // Test 5 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED);
      pass &= test(cnt == 0, test++);  // Test 6 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE);
      pass &= test(cnt == 0, test++);  // Test 7 
      
      // Count and test number of of PACKAGE fields
      cnt = cl.getDeclaredFields().length
          - countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE)
          - countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED)
          - countModifiers(cl.getDeclaredFields(), Modifier.PUBLIC);
      pass &= test(cnt == 0, test++);  // Test 8 

      return pass;
   }
   
   private static boolean testTreasureArch()
   {
      boolean pass = true;
      int test = 1;
      int cnt;
      Treasure tr;
      Square[][] squares = new Square[1][1];
      squares[0][0] = new Square(true, true, true, true, 0, 0);
      Maze maze = new Maze(squares, 1, 1);
      
      Class cl;
      
      System.out.println("Treasure architecture tests...");
      
      tr = new Treasure(maze, 0);
      
      cl = tr.getClass();

      pass &= test(cl.getConstructors().length == 3, test++);  // Test 1   
      pass &= test((cl.getInterfaces()).length == 0, test++);  // Test 2  
      pass &= test((cl.getSuperclass()).getName().equals("RandomOccupant"), test++);  // Test 3 
      
      cnt = countModifiers(cl.getDeclaredMethods(), Modifier.PUBLIC);     
      pass &= test(cnt == 6, test++);  // Test 4 
      
      cnt = cl.getFields().length;
      pass &= test(cnt == 0, test++);  // Test 5 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED);
      pass &= test(cnt == 0, test++);  // Test 6 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE);
      pass &= test(cnt == 1, test++);  // Test 7 
      
      // Count and test number of of PACKAGE fields
      cnt = cl.getDeclaredFields().length
          - countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE)
          - countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED)
          - countModifiers(cl.getDeclaredFields(), Modifier.PUBLIC);
      pass &= test(cnt == 0, test++);  // Test 8 

      return pass;
   }

   private static boolean testDrawableExplorerArch()
   {
      boolean pass = true;
      int test = 1;
      int cnt;
      DrawableExplorer drEx;
      Square square = new Square(true, true, true, true, 0, 0);
      Square[][] squares = new Square[1][1];
      squares[0][0] = square;
      Maze maze = new Maze(squares, 1, 1);
      
      Class cl;
      
      System.out.println("DrawableExplorer architecture tests...");
      
      drEx = new DrawableExplorer(square, maze, "name");
      
      cl = drEx.getClass();

      pass &= test(cl.getConstructors().length == 1, test++);  // Test 1   
      pass &= test((cl.getInterfaces()).length == 1, test++);  // Test 2  
      pass &= test((cl.getSuperclass()).getName().equals("Explorer"), test++);  // Test 3 
      
      cnt = countModifiers(cl.getDeclaredMethods(), Modifier.PUBLIC);     
      pass &= test(cnt == 1, test++);  // Test 4 
      
      cnt = cl.getFields().length;
      pass &= test(cnt == 0, test++);  // Test 5 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED);
      pass &= test(cnt == 0, test++);  // Test 6 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE);
      pass &= test(cnt == 0, test++);  // Test 7 
      
      // Count and test number of of PACKAGE fields
      cnt = cl.getDeclaredFields().length
          - countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE)
          - countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED)
          - countModifiers(cl.getDeclaredFields(), Modifier.PUBLIC);
      pass &= test(cnt == 0, test++);  // Test 8 

      return pass;
   }

   private static boolean testDrawableMonsterArch()
   {
      boolean pass = true;
      int test = 1;
      int cnt;
      DrawableMonster drMon;
      Square square = new Square(true, true, true, true, 0, 0);
      Square[][] squares = new Square[1][1];
      squares[0][0] = square; 
      Maze maze = new Maze(squares, 1, 1);
      
      Class cl;
      
      System.out.println("DrawableMonster architecture tests...");
      
      drMon = new DrawableMonster(maze, 0);
      
      cl = drMon.getClass();

      pass &= test(cl.getConstructors().length == 3, test++);  // Test 1   
      pass &= test((cl.getInterfaces()).length == 1, test++);  // Test 2  
      pass &= test((cl.getSuperclass()).getName().equals("Monster"), test++);  // Test 3 
      
      cnt = countModifiers(cl.getDeclaredMethods(), Modifier.PUBLIC);     
      pass &= test(cnt == 1, test++);  // Test 4 
      
      cnt = cl.getFields().length;
      pass &= test(cnt == 0, test++);  // Test 5 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED);
      pass &= test(cnt == 0, test++);  // Test 6 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE);
      pass &= test(cnt == 0, test++);  // Test 7 
      
      // Count and test number of of PACKAGE fields
      cnt = cl.getDeclaredFields().length
          - countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE)
          - countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED)
          - countModifiers(cl.getDeclaredFields(), Modifier.PUBLIC);
      pass &= test(cnt == 0, test++);  // Test 8 

      return pass;
   }
   
   private static boolean testDrawableTreasureArch()
   {
      boolean pass = true;
      int test = 1;
      int cnt;
      DrawableTreasure drTr;
      Square[][] squares = new Square[1][1];
      squares[0][0] = new Square(true, true, true, true, 0, 0);
      Maze maze = new Maze(squares, 1, 1);
      
      Class cl;
      
      System.out.println("DrawableTreasure architecture tests...");
      
      drTr = new DrawableTreasure(maze, 0);
      
      cl = drTr.getClass();

      pass &= test(cl.getConstructors().length == 3, test++);  // Test 1   
      pass &= test((cl.getInterfaces()).length == 1, test++);  // Test 2  
      pass &= test((cl.getSuperclass()).getName().equals("Treasure"), test++);  // Test 3 
      
      cnt = countModifiers(cl.getDeclaredMethods(), Modifier.PUBLIC);     
      pass &= test(cnt == 1, test++);  // Test 4 
      
      cnt = cl.getFields().length;
      pass &= test(cnt == 0, test++);  // Test 5 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED);
      pass &= test(cnt == 0, test++);  // Test 6 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE);
      pass &= test(cnt == 0, test++);  // Test 7 
      
      // Count and test number of of PACKAGE fields
      cnt = cl.getDeclaredFields().length
          - countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE)
          - countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED)
          - countModifiers(cl.getDeclaredFields(), Modifier.PUBLIC);
      pass &= test(cnt == 0, test++);  // Test 8 

      return pass;
   }
   
   private static boolean testSquareArch()
   {
      boolean pass = true;
      int test = 1;
      int cnt;
      Square sq;
      Class cl;
      
      System.out.println("Square architecture tests...");
      
      sq = new Square(true, true, true, true, 0, 0);
      
      cl = sq.getClass();

      pass &= test(cl.getConstructors().length == 2, test++);  // Test 1   
      pass &= test((cl.getInterfaces()).length == 1, test++);  // Test 2  
      pass &= test((cl.getSuperclass()).getName().equals("java.lang.Object"), test++);  // Test 3 
      cnt = countModifiers(cl.getDeclaredMethods(), Modifier.PUBLIC);     
      pass &= test(cnt == 13, test++);  // Test 4 
      
      cnt = cl.getFields().length;
      pass &= test(cnt == 5, test++);  // Test 5 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED);
      pass &= test(cnt == 0, test++);  // Test 6 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE);
      pass &= test(cnt == 6, test++);  // Test 7 
      
      // Count and test number of of PACKAGE fields
      cnt = cl.getDeclaredFields().length
          - countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE)
          - countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED)
          - countModifiers(cl.getDeclaredFields(), Modifier.PUBLIC);
      pass &= test(cnt == 5, test++);  // Test 8 

      return pass;
   }
   
   private static boolean testDrawableSquareArch()
   {
      boolean pass = true;
      int test = 1;
      int cnt;
      DrawableSquare drSq;
      Class cl;
      
      System.out.println("DrawableSquare architecture tests...");
      
      drSq = new DrawableSquare(true, true, true, true, 0, 0);
      
      cl = drSq.getClass();

      pass &= test(cl.getConstructors().length == 1, test++);  // Test 1   
      pass &= test((cl.getInterfaces()).length == 1, test++);  // Test 2  
      pass &= test((cl.getSuperclass()).getName().equals("Square"), test++);  // Test 3 
      cnt = countModifiers(cl.getDeclaredMethods(), Modifier.PUBLIC);     
      pass &= test(cnt == 1, test++);  // Test 4 
      
      cnt = cl.getFields().length;
      pass &= test(cnt == 5, test++);  // Test 5 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED);
      pass &= test(cnt == 0, test++);  // Test 6 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE);
      pass &= test(cnt == 0, test++);  // Test 7 
      
      // Count and test number of of PACKAGE fields
      cnt = cl.getDeclaredFields().length
          - countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE)
          - countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED)
          - countModifiers(cl.getDeclaredFields(), Modifier.PUBLIC);
      pass &= test(cnt == 0, test++);  // Test 8 

      return pass;
   }
   
   private static boolean testMazeArch()
   {
      boolean pass = true;
      int test = 1;
      int cnt;
      Square[][] squares = new Square[1][1];
      squares[0][0] = new Square(true, true, true, true, 0, 0);
      Maze maze = new Maze(squares, 1, 1);
      
      Class cl;
      
      System.out.println("Maze architecture tests...");
      
      cl = maze.getClass();

      pass &= test(cl.getConstructors().length == 2, test++);  // Test 1   
      pass &= test((cl.getInterfaces()).length == 0, test++);  // Test 2  
      pass &= test((cl.getSuperclass()).getName().equals("java.lang.Object"), test++);  // Test 3 
      
      cnt = countModifiers(cl.getDeclaredMethods(), Modifier.PUBLIC);     
      pass &= test(cnt == 15, test++);  // Test 4 
      
      //cnt = countModifiers(cl.getDeclaredMethods(), Modifier.PRIVATE);     
      //pass &= test(cnt == 2, test++);  // Test 5 
      test++;

      cnt = cl.getFields().length;
      pass &= test(cnt == 3, test++);  // Test 6 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED);
      pass &= test(cnt == 0, test++);  // Test 7 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE);
      pass &= test(cnt == 5, test++);  // Test 8 
      
      // Count and test number of of PACKAGE fields
      cnt = cl.getDeclaredFields().length
          - countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE)
          - countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED)
          - countModifiers(cl.getDeclaredFields(), Modifier.PUBLIC);
      pass &= test(cnt == 3, test++);  // Test 9 

      return pass;
   }
   
   private static boolean testDrawableMazeArch()
   {
      boolean pass = true;
      int test = 1;
      int cnt;
      DrawableSquare[][] squares = new DrawableSquare[1][1];
      squares[0][0] = new DrawableSquare(true, true, true, true, 0, 0);
      DrawableMaze drMaze = new DrawableMaze(squares, 1, 1);
      
      Class cl;
      
      System.out.println("DrawableMaze architecture tests...");
      
      cl = drMaze.getClass();

      pass &= test(cl.getConstructors().length == 1, test++);  // Test 1   
      pass &= test((cl.getInterfaces()).length == 1, test++);  // Test 2  
      pass &= test((cl.getSuperclass()).getName().equals("Maze"), test++);  // Test 3 
      
      cnt = countModifiers(cl.getDeclaredMethods(), Modifier.PUBLIC);     
      pass &= test(cnt == 1, test++);  // Test 4 
      
      cnt = countModifiers(cl.getDeclaredMethods(), Modifier.PRIVATE);     
      pass &= test(cnt == 0, test++);  // Test 5 
      
      cnt = cl.getFields().length;
      pass &= test(cnt == 3, test++);  // Test 6 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED);
      pass &= test(cnt == 0, test++);  // Test 7 
      
      cnt = countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE);
      pass &= test(cnt == 0, test++);  // Test 8 
      
      // Count and test number of of PACKAGE fields
      cnt = cl.getDeclaredFields().length
          - countModifiers(cl.getDeclaredFields(), Modifier.PRIVATE)
          - countModifiers(cl.getDeclaredFields(), Modifier.PROTECTED)
          - countModifiers(cl.getDeclaredFields(), Modifier.PUBLIC);
      pass &= test(cnt == 0, test++);  // Test 9 

      return pass;
   }
   
   //-------------------------------------- Unit Tests --------------------------------
   
   private static boolean testSquare()
   {
      boolean pass = true;
      int test = 1;
      Square square;
      Treasure treasure;
      Square[][] squares = new Square[1][1];
      squares[0][0] = new Square(true, true, true, true, 0, 0);
      Maze maze = new Maze(squares, 1, 1);
      
      System.out.println("Square tests...");  

      pass &= test(Square.SQUARE_SIZE == 50, test++);  // test 1
      pass &= test(Square.UP == 0, test++);  // test 2
      pass &= test(Square.RIGHT == 1, test++);  // test 3
      pass &= test(Square.DOWN == 2, test++);  // test 4
      pass &= test(Square.LEFT == 3, test++);  // test 5

      square = new Square(false, true, true, false, 3, 1);   
      pass &= test(!square.wall(Square.UP), test++);  // test 6
      pass &= test(square.wall(Square.RIGHT), test++);  // test 7
      pass &= test(square.wall(Square.DOWN), test++);  // test 8
      pass &= test(!square.wall(Square.LEFT), test++);  // test 9
      pass &= test(!square.seen(), test++);  // test 10
      pass &= test(!square.inView(), test++);  // test 11
      pass &= test(square.row() == 3, test++);  // test 12
      pass &= test(square.col() == 1, test++);  // test 13
      pass &= test(square.x() == 50, test++);  // test 14
      pass &= test(square.y() == 150, test++);  // test 15
      pass &= test(square.treasure() == null, test++);  // test 16
      
      square.setInView(false);
      pass &= test(!square.seen(), test++);  // test 17
      pass &= test(!square.inView(), test++);  // test 18
      
      square.setInView(true);
      pass &= test(square.seen(), test++);  // test 19
      pass &= test(square.inView(), test++);  // test 20
      
      square.setInView(false);
      pass &= test(square.seen(), test++);  // test 21
      pass &= test(!square.inView(), test++);  // test 22
      
      square.enter();  // make sure there isn't a null pointer exception here
      treasure = new Treasure(maze, 0); 
      square.setTreasure(treasure);
      pass &= test(square.treasure() == treasure, test++);  // test 23
      pass &= test(!square.treasure().found(), test++);  // test 24
      
      square.enter();
      pass &= test(square.treasure().found(), test++);  // test 25
      pass &= test(!square.inView(), test++);  // test 26
      
      return pass;  
   }

   private static boolean testRandomOccupant()
   {
      boolean pass = true;
      int test = 1;
      RandomOccupant randOcc;
      Square prevLoc;
      Maze maze = new Maze(fixedSquares, 5, 5);
      
      System.out.println("RandomOccupant tests...");
      
      randOcc = new Monster(maze, 0);
      pass &= test(randOcc.location() != null, test++);  // test 1
      pass &= test(randOcc.location().row() == 0, test++);  // test 2
      pass &= test(randOcc.location().col() == 3, test++);  // test 3
      
      randOcc.move();
      pass &= test(randOcc.location().row() == 1, test++);  // test 4
      pass &= test(randOcc.location().col() == 3, test++);  // test 5
      
      randOcc.move();
      pass &= test(randOcc.location().row() == 2, test++);  // test 6
      pass &= test(randOcc.location().col() == 3, test++);  // test 7
      
      randOcc.move();
      pass &= test(randOcc.location().row() == 3, test++);  // test 8
      pass &= test(randOcc.location().col() == 3, test++);  // test 9
      
      randOcc.move();
      pass &= test(randOcc.location().row() == 2, test++);  // test 10
      pass &= test(randOcc.location().col() == 3, test++);  // test 11
      
      randOcc.move();
      pass &= test(randOcc.location().row() == 3, test++);  // test 12
      pass &= test(randOcc.location().col() == 3, test++);  // test 13
      
      randOcc.move();
      pass &= test(randOcc.location().row() == 2, test++);  // test 14
      pass &= test(randOcc.location().col() == 3, test++);  // test 15
      
      randOcc.move();
      pass &= test(randOcc.location().row() == 1, test++);  // test 16
      pass &= test(randOcc.location().col() == 3, test++);  // test 17
      
      randOcc.move();
      pass &= test(randOcc.location().row() == 0, test++);  // test 18
      pass &= test(randOcc.location().col() == 3, test++);  // test 19
      
      randOcc.move();
      pass &= test(randOcc.location().row() == 0, test++);  // test 20
      pass &= test(randOcc.location().col() == 4, test++);  // test 21
      
      randOcc.move();
      pass &= test(randOcc.location().row() == 1, test++);  // test 22
      pass &= test(randOcc.location().col() == 4, test++);  // test 23
      
      randOcc.move();
      pass &= test(randOcc.location().row() == 0, test++);  // test 24
      pass &= test(randOcc.location().col() == 4, test++);  // test 25
      
      randOcc.move();
      pass &= test(randOcc.location().row() == 1, test++);  // test 26
      pass &= test(randOcc.location().col() == 4, test++);  // test 27
      
      randOcc.move();
      pass &= test(randOcc.location().row() == 0, test++);  // test 28
      pass &= test(randOcc.location().col() == 4, test++);  // test 29
      
      randOcc.move();
      pass &= test(randOcc.location().row() == 0, test++);  // test 30
      pass &= test(randOcc.location().col() == 3, test++);  // test 31
      
      randOcc = new Monster(maze);
      pass &= test(randOcc.location() != null, test++);  // test 32
      
      prevLoc = randOcc.location();
      randOcc.move();
      pass &= test(randOcc.location() != prevLoc, test++);  // test 33
      
      randOcc = new Monster(maze, fixedSquares[0][0]);
      pass &= test(randOcc.location() == fixedSquares[0][0], test++);  // test 34
      
      prevLoc = randOcc.location();
      randOcc.move();
      pass &= test(randOcc.location() != prevLoc, test++);  // test 35
      
      return pass;  
   }
   
   private static boolean testExplorer()
   {
      boolean pass = true;
      int test = 1;
      Explorer ex;
      Treasure treasure;
      Maze maze = new Maze(fixedSquares, 5, 5);
      
      System.out.println("Explorer tests...");
      
      ex = new Explorer(fixedSquares[0][0], maze, "Scary Name");
      pass &= test(ex.location() == fixedSquares[0][0], test++);  // test 1
      pass &= test(ex.name().equals("Scary Name"), test++);  // test 2
      pass &= test(fixedSquares[0][0].inView(), test++);  // test 3
      pass &= test(fixedSquares[0][1].inView(), test++);  // test 4
      pass &= test(fixedSquares[1][0].inView(), test++);  // test 5
      pass &= test(fixedSquares[1][1].inView(), test++);  // test 6
      pass &= test(!fixedSquares[0][2].inView(), test++);  // test 7
      pass &= test(!fixedSquares[2][0].inView(), test++);  // test 8
      
      ex.move(KeyEvent.VK_UP);
      pass &= test(ex.location() == fixedSquares[0][0], test++);  // test 9
      
      ex.move(KeyEvent.VK_LEFT);
      pass &= test(ex.location() == fixedSquares[0][0], test++);  // test 10
      
      ex.move(KeyEvent.VK_RIGHT);
      pass &= test(ex.location() == fixedSquares[0][1], test++);  // test 11
      
      ex.move(KeyEvent.VK_LEFT);
      pass &= test(ex.location() == fixedSquares[0][0], test++);  // test 12
      
      ex.move(KeyEvent.VK_KP_RIGHT);
      pass &= test(ex.location() == fixedSquares[0][1], test++);  // test 13
      
      ex.move(KeyEvent.VK_KP_LEFT);
      pass &= test(ex.location() == fixedSquares[0][0], test++);  // test 14
      
      ex.move(KeyEvent.VK_DOWN);
      pass &= test(ex.location() == fixedSquares[1][0], test++);  // test 15
      
      ex.move(KeyEvent.VK_UP);
      pass &= test(ex.location() == fixedSquares[0][0], test++);  // test 16
      
      ex.move(KeyEvent.VK_KP_DOWN);
      pass &= test(ex.location() == fixedSquares[1][0], test++);  // test 17
      
      ex.move(KeyEvent.VK_KP_UP);
      pass &= test(ex.location() == fixedSquares[0][0], test++);  // test 18
      
      ex = new Explorer(fixedSquares[4][4], maze, "Scary Name");
      pass &= test(ex.location() == fixedSquares[4][4], test++);  // test 19
      
      ex.move(KeyEvent.VK_RIGHT);
      pass &= test(ex.location() == fixedSquares[4][4], test++);  // test 20
      
      ex.move(KeyEvent.VK_DOWN);
      pass &= test(ex.location() == fixedSquares[4][4], test++);  // test 21
      
      ex.move(KeyEvent.VK_ENTER);
      pass &= test(ex.location() == fixedSquares[4][4], test++);  // test 22
      
      treasure = new Treasure(maze, fixedSquares[3][3]); 
      ex.moveTo(fixedSquares[3][3]);
      pass &= test(fixedSquares[3][3].inView(), test++);  // test 23
      pass &= test(!fixedSquares[3][4].inView(), test++);  // test 24
      pass &= test(!fixedSquares[3][2].inView(), test++);  // test 25
      pass &= test(!fixedSquares[4][3].inView(), test++);  // test 26
      pass &= test(fixedSquares[2][3].inView(), test++);  // test 27
      pass &= test(fixedSquares[3][3].treasure().found(), test++);  // test 28
      
      return pass;  
   }
   
   private static boolean testMonster()
   {
      boolean pass = true;
      int test = 1;
      Monster monster;
      Square prevLoc;
      Maze maze = new Maze(fixedSquares, 5, 5);
      
      System.out.println("Monster tests...");
      
      monster = new Monster(maze, 0);
      pass &= test(monster.location() != null, test++);  // test 1
      pass &= test(monster.location().row() == 0, test++);  // test 2
      pass &= test(monster.location().col() == 3, test++);  // test 3
      
      monster.move();
      pass &= test(monster.location().row() == 1, test++);  // test 4
      pass &= test(monster.location().col() == 3, test++);  // test 5
      
      monster = new Monster(maze);
      pass &= test(monster.location() != null, test++);  // test 6
      
      prevLoc = monster.location();
      monster.move();
      pass &= test(monster.location() != prevLoc, test++);  // test 7
      
      monster = new Monster(maze, fixedSquares[0][0]);
      pass &= test(monster.location() == fixedSquares[0][0], test++);  // test 8
      
      prevLoc = monster.location();
      monster.move();
      pass &= test(monster.location() != prevLoc, test++);  // test 9
      
      return pass;  
   }
   
   private static boolean testTreasure()
   {
      boolean pass = true;
      int test = 1;
      Treasure treasure;
      Square prevLoc;
      Maze maze = new Maze(fixedSquares, 5, 5);
      
      System.out.println("Treasure tests...");
      
      treasure = new Treasure(maze, 0);
      pass &= test(treasure.location() != null, test++);  // test 1
      pass &= test(treasure.location().row() == 0, test++);  // test 2
      pass &= test(treasure.location().col() == 3, test++);  // test 3
      pass &= test(!treasure.found(), test++);  // test 4
      
      treasure.move();
      pass &= test(treasure.location().row() == 0, test++);  // test 5
      pass &= test(treasure.location().col() == 3, test++);  // test 6
      
      treasure = new Treasure(maze);
      pass &= test(treasure.location() != null, test++);  // test 7
      pass &= test(!treasure.found(), test++);  // test 8
      
      prevLoc = treasure.location();
      treasure.move();
      pass &= test(treasure.location() == prevLoc, test++);  // test 9
      
      treasure = new Treasure(maze, fixedSquares[0][0]);
      pass &= test(treasure.location() == fixedSquares[0][0], test++);  // test 10
      pass &= test(!treasure.found(), test++);  // test 11
      
      treasure.setFound();
      pass &= test(treasure.found(), test++);  // test 12
      
      return pass;  
   }
   
   private static boolean testMaze()
   {
      boolean pass = true;
      int test = 1;
      Maze maze, maze2;
      Explorer ex;
      Treasure t1, t2;
      Monster m1, m2;
      
      System.out.println("Maze tests...");
      
      maze = new Maze(fixedSquares, 5, 5);

      pass &= test(Maze.ACTIVE == 0, test++);  // test 1
      pass &= test(Maze.EXPLORER_WIN == 1, test++);  // test 2
      pass &= test(Maze.MONSTER_WIN == 2, test++);  // test 3
      pass &= test(maze.getSquare(0,0) == fixedSquares[0][0], test++);  // test 4
      pass &= test(maze.rows() == 5, test++);  // test 5
      pass &= test(maze.cols() == 5, test++);  // test 6
      pass &= test(maze.getExplorer() == null, test++);  // test 7
      pass &= test(maze.getNumRandOccupants() == 0, test++);  // test 8
      pass &= test(maze.gameStatus() == Maze.EXPLORER_WIN, test++);  // test 9
      
      ex = new Explorer(fixedSquares[0][0], maze, "Scary Name");
      maze.setExplorer(ex);
      pass &= test(maze.getExplorer() == ex, test++);  // test 10
      pass &= test(maze.explorerName().equals("Scary Name"), test++);  // test 11
      
      maze.explorerMove(KeyEvent.VK_RIGHT);
      pass &= test(maze.getExplorer().location() == fixedSquares[0][1], test++);  // test 12
      
      t1 = new Treasure(maze, fixedSquares[4][4]);
      maze.addRandomOccupant(t1);
      pass &= test(maze.gameStatus() == Maze.ACTIVE, test++);  // test 13
      pass &= test(maze.getRandomOccupant(0) == t1, test++);  // test 14
      
      t2 = new Treasure(maze, fixedSquares[2][2]);
      m1 = new Monster(maze, fixedSquares[4][4]);
      m2 = new Monster(maze, fixedSquares[3][3]);
      maze.addRandomOccupant(t2);
      maze.addRandomOccupant(m1);
      maze.addRandomOccupant(m2);
      pass &= test(maze.gameStatus() == Maze.ACTIVE, test++);  // test 15
      pass &= test(maze.getNumRandOccupants() == 4, test++);  // test 16
      pass &= test(maze.getRandomOccupant(3) == m2, test++);  // test 17
     
      maze.randMove();
      pass &= test(maze.getRandomOccupant(0).location() == fixedSquares[4][4], test++);  // test 18
      pass &= test(maze.getRandomOccupant(1).location() == fixedSquares[2][2], test++);  // test 19
      pass &= test(maze.getRandomOccupant(2).location() != fixedSquares[4][4], test++);  // test 20
      pass &= test(maze.getRandomOccupant(0).location() != fixedSquares[3][3], test++);  // test  21
      
      t1.setFound();
      pass &= test(maze.gameStatus() == Maze.ACTIVE, test++);  // test 22
      
      maze.addRandomOccupant(new Monster(maze, fixedSquares[0][1]));
      pass &= test(maze.gameStatus() == Maze.MONSTER_WIN, test++);  // test 23
      
      maze.randMove();
      pass &= test(maze.gameStatus() == Maze.ACTIVE, test++);  // test 24
      
      t2.setFound();
      pass &= test(maze.gameStatus() == Maze.EXPLORER_WIN, test++);  // test 25
      
      pass &= test(!fixedSquares[4][0].seen(), test++);  // test 26
      pass &= test(!fixedSquares[4][0].inView(), test++);  // test 27
      
      maze.lookAround(fixedSquares[4][0]);
      pass &= test(fixedSquares[4][0].inView(), test++);  // test 28
      pass &= test(!fixedSquares[4][1].inView(), test++);  // test 29
      pass &= test(fixedSquares[3][0].inView(), test++);  // test 30
      pass &= test(!fixedSquares[3][1].inView(), test++);  // test 31
      
      return pass;  
   }
   
   private static boolean testMazeReadWrite() throws MazeReadException, IOException
   {  
      boolean pass = true;
      boolean caught;
      int test = 1;
      Maze maze, maze2;
      Explorer ex;
      Treasure t1, t2;
      Monster m1, m2;
      
      System.out.println("Maze Read/Write tests...");
      
      resetFixedSquares();
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
      
      // test writing maze to file
      maze.writeMazeToFile("test.txt");
      pass &= test(filesEqual("test.txt", "mazeGood.txt"), test++);  // test 1
      
      // move the explorer
      maze.getExplorer().moveTo(maze.getSquare(0,2));
      maze.writeMazeToFile("test.txt");
      pass &= test(filesEqual("test.txt", "mazeGood2.txt"), test++);  // test 2
  
      // test reading a good maze
      maze = new Maze();
      maze.readMazeFromFile("mazeGood.txt");
      maze.writeMazeToFile("test.txt");
      pass &= test(filesEqual("test.txt", "mazeGood.txt"), test++);  // test 3
      
      // test reading a good maze with Square out of row/col order
      maze = new Maze();
      maze.readMazeFromFile("mazeGoodOutOfOrder.txt");
      maze.writeMazeToFile("test.txt");
      pass &= test(filesEqual("test.txt", "mazeGood.txt"), test++);  // test 4
      
      // test reading a bad file - bad row/col
      maze = new Maze();
      caught = false;
      try 
      {
         maze.readMazeFromFile("mazeBadRowCol.txt");
      } 
      catch (MazeReadException e)
      {
         caught = true;
         pass &= test(e.getMessage().equals("Rows and columns not specified."), test++); // test 5
         pass &= test(e.getLine().equals("Square,0,0,true,false,false,true,true,true"), test++); // test 6
         pass &= test(e.getLineNum() == 1, test++); // test 7
      }
      
      if (!caught)
      {
         System.out.println("   FAILED test #8"); // test 8
         pass &= false;
      }
      test = 9;
      
      // test reading a bad file - duplicate square
      maze = new Maze();
      caught = false;
      try 
      {
         maze.readMazeFromFile("mazeDupSquare.txt");
      } 
      catch (MazeReadException e)
      {
         caught = true;
         pass &= test(e.getMessage().equals("Duplicate square."), test++); // test 9
         pass &= test(e.getLine().equals("Square,2,0,false,false,false,true,false,false"), test++); // test 10
         pass &= test(e.getLineNum() == 13, test++); // test 11
      }
      
      if (!caught)
      {
         System.out.println("   FAILED test #12"); // test 12
         pass &= false;
      }
      test = 13;
      
      // test reading a bad file - unknown type
      maze = new Maze();
      caught = false;
      try 
      {
         maze.readMazeFromFile("mazeUnknownType.txt");
      } 
      catch (MazeReadException e)
      {
         caught = true;
         pass &= test(e.getMessage().equals("Unknown type."), test++); // test 13
         pass &= test(e.getLine().equals("Sword,1,4,false,true,false,true,false,false"), test++); // test 14
         pass &= test(e.getLineNum() == 11, test++); // test 15
      }
      
      if (!caught)
      {
         System.out.println("   FAILED test #16"); // test 16
         pass &= false;
      }
      test = 17;
      
      // test reading a bad file - bad line format
      maze = new Maze();
      caught = false;
      try 
      {
         maze.readMazeFromFile("mazeBadLineFormat.txt");
      } 
      catch (MazeReadException e)
      {
         caught = true;
         pass &= test(e.getMessage().equals("Line format or other error."), test++); // test 17
         pass &= test(e.getLine().equals("Treasure,4,true,4,true"), test++); // test 18
         pass &= test(e.getLineNum() == 28, test++); // test 19
      }
      
      if (!caught)
      {
         System.out.println("   FAILED test #20"); // test 20
         pass &= false;
      }
      test = 21;
      
      // test reading a bad file - different bad line format
      maze = new Maze();
      caught = false;
      try 
      {
         maze.readMazeFromFile("mazeBadLineFormat2.txt");
      } 
      catch (MazeReadException e)
      {
         caught = true;
         pass &= test(e.getMessage().equals("Line format or other error."), test++); // test 21
         pass &= test(e.getLine().equals(""), test++); // test 22
         pass &= test(e.getLineNum() == 3, test++); // test 23
      }
      
      if (!caught)
      {
         System.out.println("   FAILED test #24"); // test 24
         pass &= false;
      }
      test = 25;
      
      // test reading a good maze with different number of rows/cols
      maze = new Maze();
      maze.readMazeFromFile("mazeGoodDiffRowsCols.txt");
      maze.writeMazeToFile("test.txt");
      pass &= test(filesEqual("test.txt", "mazeGoodDiffRowsCols.txt"), test++);  // test 25

      return pass;  
   }
   
   //-------------------------------------- Utility Methods --------------------------------
   
   private static void printHeader(String[] args)
   {
      if (args.length == 1)
      {
         System.out.println(args[0]);
      }
      
      System.out.println(RESULTS_FOR + "\n");
   }   
   
   private static void printResults(boolean pass)
   {
      String msg;
      
      if(pass)
      {
         msg = "\nCongratulations, you passed all the tests!\n\n"
            + "Your grade will be based on whether or not  and any deductions for the quality of your\n"
            + "implementation.  Quality is based on, but not limited to,\n"
            + "coding style, documentation requirements, compiler warnings,\n"
            + "and the efficiency and elegance of your code.\n";
      }
      else
      {
         msg = "\nNot done yet - you failed one or more tests!\n";
      }
      
      System.out.print(msg);       
   }
     
   private static int countModifiers(Field[] fields, int modifier)
   {
      int count = 0;
      
      for (Field f : fields)
      {
         if (f.getModifiers() == modifier)
         {
            count++;
         }
      }
      
      return count;
   }
   
   private static int countModifiers(Method[] methods, int modifier)
   {
      int count = 0;
      
      for (Method m : methods)
      {
         if (m.getModifiers() == modifier)
         {
            count++;
         }
      }
      
      return count;
   }
   
   private static boolean test(boolean pass, int testNum)
   {
      if (!pass)
      {
         System.out.println("   FAILED test #" + testNum);
      }

      return pass;
   }
   
   private static boolean filesEqual(String fn1, String fn2) throws IOException
   {
       Scanner s1 = new Scanner(new File(fn1));
       Scanner s2 = new Scanner(new File(fn2));
       
       while (s1.hasNext() && s2.hasNext())
       {
           if (!s1.nextLine().equals(s2.nextLine()))
               return false;
       }
       if (s1.hasNext())
           return false;
       if (s2.hasNext())
           return false;
           
       return true;
   }   
   private static void resetFixedSquares()
   {
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
   }
}
