//Program by Jared Spadaro
//CPE103 with Professor Buckalew
//12/5/13

import java.awt.*;
import java.awt.event.*;
import java.applet.Applet;
import java.util.Iterator;
import javax.swing.*;
import java.util.Scanner;
import java.io.File;

public class Maze extends Applet {
   
   //these are variables to keep track of the location of the mouse click
   // and how many times it has been clicked
   private int click = 0;
   private int mousePositionXGreen = 0;
   private int mousePositionYGreen = 0; 
   private int mousePositionXRed = 0;
   private int mousePositionYRed = 0; 

 // array that holds the maze info
   private int[][] maze;

   //this is to hold the collection of vertices (taken from maze)
   private int[] vertices;

   //number of rows and columns in the maze
   private int rows, cols;

   // initial size of maze - if bigger may go off window
   private final int MAXROWS = 20;
   private final int MAXCOLS = 30;
   
   // size of each block in pixels
   private final int blkSize = 20;
   
   //inner class that displays the maze
   private MazeCanvas mazeField;

   // everything is put on this panel   
   private JPanel mazePanel;

   private JPanel buttonPanel;

   // label, textfield, string, and load button for the file
   private JLabel fileLabel;
   private JTextField fileText;
   String fileName;
   private JButton fileButton;
  
   private JButton goButton;
   
   //this listener object responds to button events
   private ButtonActionListener buttonListener;
   private MouseEventListener mouseListener;

   // this method sets up the canvas and starts it off
   public void init() {
      System.out.println("Maze started"); // goes to console 
      
      click = 0;
      mouseListener = new MouseEventListener();
      buttonListener = new ButtonActionListener();
               
      // the mazePanel is the panel that contains the maze interfaces, including
      // the buttons and output display
      mazePanel = new JPanel();
      // Y_AXIS layout places components from top to bottom, in order of adding
      mazePanel.setLayout(new BoxLayout(mazePanel, BoxLayout.Y_AXIS));
      
      // components for loading the filename

      //new panel to make the buttons look a little nicer
      buttonPanel = new JPanel();
      buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));

      fileLabel = new JLabel("File name:");
      mazePanel.add(fileLabel);
      fileText = new JTextField("Maze.txt", 20);
      mazePanel.add(fileText);
      fileButton = new JButton("Load File");
      buttonPanel.add(fileButton);
      fileButton.addActionListener(buttonListener);
     
      goButton = new JButton("GO");
      buttonPanel.add(goButton);
      goButton.addActionListener(buttonListener);

      mazePanel.add(buttonPanel);

      // this is where the maze is drawn
      // if you add more to this layout after the mazeField, 
      // it may be below the bottom of the window, depending on window size
      mazeField = new MazeCanvas();
      mazePanel.add(mazeField);
      mazeField.addMouseListener(mouseListener);

      // now add the maze panel to the applet
      add(mazePanel);
   }
   
   // this object is triggered whenever a button is clicked
   private class ButtonActionListener implements ActionListener {
      public void actionPerformed(ActionEvent event) {
          
         // find out which button was clicked 
         Object source = event.getSource();
         
         if (source == fileButton)
         {
            fileName = fileText.getText();
            makeMaze(fileName);
         }
      } 
   }

   private class MouseEventListener implements MouseListener
   {
      public void mouseClicked(MouseEvent e)
      {
         // location on the mazeCanvas where mouse was clicked
         // upper-left is (0,0)
         // if no clicks have been recorded (or it has been reset to 0), 
         // then store the click's position (for green square)  
         if (click==0) {
           mousePositionXGreen = e.getX()/blkSize;
           mousePositionYGreen = e.getY()/blkSize;
         }
         // if there has been a click recorded, then store the click's position (for the red square) 
         else if (click==1) {
           mousePositionXRed = e.getX()/blkSize;
           mousePositionYRed = e.getY()/blkSize;
         }
         //increment click because a click has been recorded
         click++;
         //paint the squares
         mazeField.paint(mazeField.getGraphics());
     }
      
      public void mousePressed(MouseEvent e) { }
      public void mouseReleased(MouseEvent e) { }
      public void mouseEntered(MouseEvent e) { }
      public void mouseExited(MouseEvent e) { }
   }

   public boolean makeMaze(String fileName)
   {
      try
      {
         Scanner scanner = new Scanner(new File(fileName));
         rows = scanner.nextInt();
         cols = scanner.nextInt();
         maze = new int[rows][cols];
         //fill out maze matrix
         for(int i=0; i<rows; i++)
         {
            for(int j=0; j<cols; j++)
            {
               maze[i][j] = scanner.nextInt();
            }
         }
   
         // now draw it
         mazeField.paint(mazeField.getGraphics());
         return true;
      }
      catch(Exception e)
      {
         return false;
      }
   }
           
   class MazeCanvas extends Canvas {
      // this class paints the output window 
       
     // the constructor sets it up
      MazeCanvas() {
         rows = MAXROWS;
         cols = MAXCOLS;
         maze = new int[MAXROWS][MAXCOLS];
         setSize(cols*blkSize, rows*blkSize);
         setBackground(Color.white);
      }
       
      public void paint(Graphics g)
      {
         g.setColor(Color.white);
         g.fillRect(0, 0, cols*blkSize, rows*blkSize);
         
         for (int i=0; i<rows; i++)
         { 
            for (int j=0; j<cols; j++)
            {
               if (maze[i][j] == -1)
               {
                  // location is a wall
                  g.setColor(Color.black);
               }
               else
               {
                  // location is clear
                  g.setColor(Color.white);
               }
               // draw the location
               g.fillRect(j*blkSize, i*blkSize, blkSize, blkSize);
            }
         }
         //if this is the first click then paint a green square
         if(click==1) {
           g.setColor(Color.green);
           g.fillRect(mousePositionXGreen*blkSize, mousePositionYGreen*blkSize, blkSize, blkSize);
         }
         //if this is the second click then paint both squares
         else if(click==2) {
           g.setColor(Color.green);
           g.fillRect(mousePositionXGreen*blkSize, mousePositionYGreen*blkSize, blkSize, blkSize);
           g.setColor(Color.red);
           g.fillRect(mousePositionXRed*blkSize, mousePositionYRed*blkSize, blkSize, blkSize);
         }
         //on the third click, remove the blocks and reset click
         else click=0;
      }
   }

   //this is the method that creates an adjacency matrix from the 2d maze array
   //I struggled with this method for a long time and could not find a solution
   public int[][] createAdjacencyMatrix () {
      //an array to hold the vertices from maze[][]
      vertices = new int[MAXROWS*MAXCOLS];
      for(int i=0;i<MAXROWS;i++) {
         for(int j=0;j<MAXCOLS;j++) {
            //fill array with the vertices from maze
            //I thought this would be a good idea but did not find a use for it
            vertices[i*MAXCOLS+j] = maze[i][j];
         }
      }
      //initialize adjacency matrix. size of both dimensions is the total number of vertices
      int[][] adj = new int[MAXROWS*MAXCOLS][MAXROWS*MAXCOLS];
      for(int i=0;i<MAXROWS;i++) {      //these two loops are to iterate through each vertex
         for(int j=0;j<MAXCOLS;j++) {
            if(maze[i][j]==-1) {  //if current vertex is a wall
               adj[i*MAXCOLS+j][0] = 0;  //add 0 to adj
            }
            else {  //we know that it is a 0 (so not a wall)
               adj[i*MAXCOLS+j][i*MAXCOLS+j] = 0; //vertices are not connected to themselves
               //if the vertex to the left of the current vertex isn't a wall
               if(maze[i-1][j]==0) {  
                  //add an edge to the adjacency matrix (couldn't figure out how to get the correct indices for adj)
                  adj[i*MAXCOLS+j][(i-1)*MAXCOLS+j] = 1;
               }
               //if the vertex to the right to the current vertex isn't a wall
               else if (maze[i+1][j]==0) {
                  //add an edge to the adjacency matrix (couldn't figure out how to get the correct indices for adj)
                  adj[i*MAXCOLS+j][(i+1)*MAXCOLS+j] = 1;
               }
               //if the vertex below to the current vertex isn't a wall
               else if (maze[i][j-1]==0) {
                  //add an edge to the adjacency matrix (couldn't figure out how to get the correct indices for adj)
                  adj[i*MAXCOLS+j][i*MAXCOLS+(j-1)] = 1;
               }
               //if the vertex above the current vertex isn't a wall
               else if (maze[i][j+1]==0) {
                  //add an edge to the adjacency matrix (couldn't figure out how to get the correct indices for adj)
                  adj[i*MAXCOLS+j][i*MAXCOLS+(j+1)] = 1;
               }  
               else {}
            }
         }
      }
      return adj;
   }

   //this method paints the path from start to stop (UNFINISHED)
   public void paintYellowPath () {
      //create adjacency matrix from 2d maze array
      int adj[][] = createAdjacencyMatrix();
      //create graph with adjacency array and MAXROWS*MAXCOLS vertices
      Graph g = new Graph (adj,MAXROWS*MAXCOLS);
      //run dijkstra's algorithm from start position (first mouse click) to stop position (second mouse click)
      g.dijkstra(adj[mousePositionXGreen][mousePositionYGreen], adj[mousePositionXRed][mousePositionYRed]);
   } 
















}