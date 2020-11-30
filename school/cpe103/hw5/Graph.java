//Program by Jared Spadaro
//CPE103 with Professor Buckalew
//12/5/13

import java.io.*;
import java.util.*;

public class Graph 
{
   private int[][] adj;      //adjacency matrix
   private int numVertices;  
   private int[] visited;
   private Vertex[] paths;  //contains all the vertices and the cost it took to reach them from start
   private Vertex[] shortestPath;  //contains the vertices travelled in the shortest path from start to stop

   //graph constructor
   public Graph (int[][]adj, int numVertices) {
      //initialize arrays
      adj = new int[numVertices][numVertices];    
      visited = new int[numVertices];
      for(int i=0;i<numVertices;i++) {
         visited[i] = -1;
         for(int j=0;j<numVertices;j++) {
            this.adj[i][j] = adj[i][j];
         }
      }   
      this.numVertices = numVertices;
   }    

   public int vertices()
   {
      return numVertices;
   }

   public static class Error extends RuntimeException
   {
      public Error(String message)
      {
         super(message);
      }
   }
  
   private class Vertex {
      //vertex's index
      private int position;
      public int position() { return position; }
      //number of steps it took to reach this vertex
      private int cost;
      public int cost() { return cost; }
      //the vertex travelled from to get here
      private int parent;
      public int parent () { return parent; }

      public void setCost (int cost) {
         this.cost = cost;
      }

      public void setParent (int p) {
         parent = p;
      }

      public Vertex (int position) {
         this.position = position;
         cost = 0;
      }

   }

   //this method performs dijkstra's algorithm 
   public Vertex[] dijkstra (int start, int stop) {
      //initializes paths array
      paths = new Vertex[numVertices];
      //create starting vertex
      Vertex source = new Vertex (start);
      visited[start] = 0;
      //put starting vertex in it's position in paths
      paths[start] = source;
      //initialize temp to something for the sake of the while loop check
      Vertex temp = source;
      //once we reach stop, ...stop
      while(temp.position()!=stop) {
         //get the vertex with the smallest cost
         temp = Min(paths);
         for(int i=0;i<numVertices;i++) {
            //check for a connection and see if it has been visited
            if(adj[temp.position()][i]==1 && visited[i]==-1) {
               visited[i] = 0;  //set to visited
               Vertex v = new Vertex(i);  //create vertex
               v.setParent(temp.position());  //set parent to temp
               v.setCost(temp.cost()+1);  //set cost to parent cost + 1
               paths[i] = v;      //now the array "paths" contains the shortest path from start to stop
            }
         }
      }
      return paths;
   }      
      

//Linear Search Method (to find minimum cost)
  public Vertex Min (Vertex[] x) {
    Vertex min = x[0];
    for(int i=1;i<x.length;i++) {                   
      if (x[i].cost()<min.cost()) min = x[i];  
    }                                                 
    return min;                                        
  }


}
