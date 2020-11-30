import mycs1.*;

public class Lab6B
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
      //g.print();

      System.out.print("Enter starting vertex: ");
      int from = Keyboard.readInt();
      int checkSum = 0;
      for(int to=0;to<g.vertices();++to)
      {
         int length = g.fewestEdgePath(from,to);
         System.out.println("Fewest-edge path from " + from + " to " + to +
            " contains " + length + " edges.");
         checkSum += length;
      }
      System.out.println("Total of all path lengths = " + checkSum);
  }
}