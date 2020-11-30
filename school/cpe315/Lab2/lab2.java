import java.io.*;
import java.util.*;

public class lab2 {
   private Hashtable<String, String> regMap;
   private Hashtable<String, String> instrMap;
   private Hashtable<String, Integer> labels;
   private int lineCount;
   private String instruction;
    
   public lab2() {
      labels = new Hashtable<String, Integer>();
      instrMap = new Hashtable<String, String>();
      regMap = new Hashtable<String, String>();
      lineCount = 0;
      instruction = "";
   }   

   public void regDecode () {
      this.regMap.put("$zero","00000");
      this.regMap.put("$0","00000");
   
      this.regMap.put("$v0","00010");
      this.regMap.put("$v1","00011");

      this.regMap.put("$a0","00100");
      this.regMap.put("$a1","00101");
      this.regMap.put("$a2","00110");
      this.regMap.put("$a3","00111");

      this.regMap.put("$t0","01000");
      this.regMap.put("$t1","01001");
      this.regMap.put("$t2","01010");
      this.regMap.put("$t3","01011");
      this.regMap.put("$t4","01100");
      this.regMap.put("$t5","01101");
      this.regMap.put("$t6","01110");
      this.regMap.put("$t7","01111");

      this.regMap.put("$s0","10000");
      this.regMap.put("$s1","10001");
      this.regMap.put("$s2","10010");
      this.regMap.put("$s3","10011");
      this.regMap.put("$s4","10100");
      this.regMap.put("$s5","10101");
      this.regMap.put("$s6","10110");
      this.regMap.put("$s7","10111");

      this.regMap.put("$t8","11000");
      this.regMap.put("$t9","11001");
 
      this.regMap.put("$sp","11101");

      this.regMap.put("$ra","11111");
   }

   public void findLabels(File file) throws FileNotFoundException {
      Scanner lineScan, scan = new Scanner(file);
      String line;

      while (scan.hasNextLine()) {
         line = scan.nextLine().trim();
         
         if (line.contains("#")) 
            line = line.substring(0, line.indexOf('#')).trim();

         if (line.contains(":")) {
            lineScan = new Scanner(line);
            lineScan.useDelimiter(":");
            this.labels.put(lineScan.next().trim(), this.lineCount);
            lineScan.close();
         }
         
         this.lineCount++;      
      }
   }

   public void findInstruction(File file) throws FileNotFoundException {
      this.lineCount = 0;
      Scanner lineScan, scan = new Scanner(file);
      String line, args;
      int regNdx = 0;      

      while (scan.hasNextLine()) {
         line = scan.nextLine().trim(); 
         try {
            if (!line.equals("")) {
               if (line.charAt(0) != '#') { 
                  if (line.contains("#")) 
                     line = line.substring(0, line.indexOf("#")).trim();
            
                  lineScan = new Scanner(line);

                  if (line.contains(":")) {
                     lineScan.useDelimiter(":");
                     lineScan.next().trim();
                     line = lineScan.next().trim();
                     lineScan.close();
                     lineScan = new Scanner(line);
                  }

                  regNdx = line.indexOf("$");
            
                  if (regNdx == -1) {
                     this.instruction = lineScan.next().trim();
                     args = lineScan.nextLine().trim();
                  }
                  else {
                     this.instruction = line.substring(0, regNdx).trim();
                     args = line.substring(regNdx, line.length()).trim();
                  }
            
                  decode(args);
               }
            }
         } 
         catch (NoSuchElementException e) {
         
         }
         this.lineCount++;   
      }
   }

   public void decode(String args) {
      Scanner scan;
      int bytes = 0;
      String immediate = "";
      String[] register = {"", "", ""};
      int i = 0; 
      int imm = 0;
      boolean flag;

      args = args.trim();
      scan = new Scanner(args);

      scan.useDelimiter(",");
      while (scan.hasNext()) {
         args = scan.next().trim();
         flag = false;

         if (i > 2) 
            throw new RuntimeException("Invalid args\n");

         if (args.contains("($")) {
            immediate = args.substring(0, 1);
            register[i] = args.substring(2, args.length() - 1);
            bytes = Integer.parseInt(immediate);
            immediate = String.format("%16s", 
             Integer.toBinaryString(bytes)).replace(' ', '0');
            if (null == (register[i] = this.regMap.get(register[i++]))) {
               throw new RuntimeException("Register doesn't exist\n");
            }
         }
         else if (args.contains("$")) {
            if (null == (register[i++] = this.regMap.get(args))) {
               throw new RuntimeException("Register doesn't exist\n");
            }
         }
         else {
            try {
               imm = Integer.parseInt(args);
            }
            catch (NumberFormatException e) {
               flag = true;
               if (null == (Integer)(imm = this.labels.get(args))) {
                  throw new RuntimeException("Label doesn't exist\n");
               }   
            }
            if (this.instruction.equals("j") || 
             this.instruction.equals("jal")) {
               immediate = String.format("%26s", 
                Integer.toBinaryString(imm)).replace(' ', '0');
            }
            else {
               if (flag) {
                  imm = imm - (this.lineCount + 1);
               }
               
               immediate = String.format("%16s", 
                Integer.toBinaryString(imm)).replace(' ', '0');        
            }
         }
      }
      System.out.println(register[0]);
      System.out.println(register[1]);
      System.out.println(register[2]);
      System.out.println(immediate);
      System.out.print("\n");
   }

   public static void main (String args[]) throws FileNotFoundException {
      lab2 asm = new lab2();
      File mips = new File(args[0]);
      
      asm.regDecode();
      asm.findLabels(mips);
      asm.findInstruction(mips);
   }
}
