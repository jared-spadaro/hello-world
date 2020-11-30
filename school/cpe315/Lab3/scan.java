import java.util.*;
import java.io.*;

public class scan {
   
   public static void main(String[] args) throws FileNotFoundException {
      Scanner scanCmds, scanMips;      
      int argLen;
      File script;
      File mips;     
      
      //no arguments given
      if (args.length < 1) {
         System.out.println("Format: [mips file] [optional script file]");
         System.exit(-1);
      }

      argLen = args[0].length();

      //check that first input file is type ".asm"
      if (!args[0].substring(argLen - 4, argLen).equals(".asm")) {
         System.out.println("Wrong file format");
         System.exit(-1);
      }
      //no script file given
      if (args.length < 2) {
         System.out.println(System.in);
         scanCmds = new Scanner(System.in);
      }
      //script file given 
      else {
         script = new File(args[1]);
         scanCmds = new Scanner(script);
      }
      mips = new File(args[0]);
      scanMips = new Scanner(mips);
   }
}
