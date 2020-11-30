import mycs1.*;
public class Lab6A
{
   private static int[] marker;
   private static final int FORWARD = 0;
   private static final int BACKWARD = 1;

   public static void main(String[] args)
   { 
      String fileName;
      if (args.length == 0)
      { 
         System.out.println("File name can be passed as a command line argument.");
         System.out.print("Enter data file name: ");
         fileName = Keyboard.readWord();
      }
      else
         fileName = args[0];
      Graph g = new Graph(fileName);
      // g.print();

      marker = new int[g.vertices()];
      for(int i=0;i<marker.length;++i)
         marker[i] = -1;

      int component = 0;
      int start = unvisited(FORWARD);
      while(start != -1)
      {
         for(int i=start;i<g.vertices();++i)
            if (g.isPath(start,i))
               marker[i] = component;
         ++component;
         start = unvisited(FORWARD);
      }
      
      System.out.println();
      System.out.println("The components of " + fileName + " are:");
      for(int i=0;i<component;++i)
      {
         System.out.print("Component " + i + ": ");
         for(int j=0;j<marker.length;++j)
            if(marker[j] == i)
               System.out.print(j + " ");
         System.out.println();
      }

      for(int i=0;i<marker.length;++i)
         marker[i] = -1;
      component = 0;
      start = unvisited(BACKWARD);
      while(start != -1)
      {
         for(int i=start;i>=0;--i)
            if (g.isPath(start,i))
               marker[i] = component;
         ++component;
         start = unvisited(BACKWARD);
      }
      
      System.out.println();
      System.out.println("RECHECKING: The components of " + fileName + " are:");
      for(int i=0;i<component;++i)
      {
         System.out.print("Component " + i + ": ");
         for(int j=0;j<marker.length;++j)
            if(marker[j] == i)
               System.out.print(j + " ");
         System.out.println();
      }
   }

   private static int unvisited(int direction)
   {
      int i;
      if (direction == FORWARD)
      {
         for(i=0;i<marker.length;++i)
            if (marker[i] == -1)
               return i;
         return -1;
      }
      else
      {
         for(i=marker.length-1;i>=0;--i)
            if (marker[i] == -1)
               return i;
         return -1;
      }
   }

}