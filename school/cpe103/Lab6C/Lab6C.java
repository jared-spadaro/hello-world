import mycs1.*;

public class Lab6C
{
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
      System.out.println("Weight of MST via Kruskal's algorithm = " + g.Kruskal());
   }
}