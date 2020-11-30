/* Jared Spadaro and Michael Woodson
 * CPE 315
 * Lab 3
 * 10/22/15
 * This program takes in a .asm file and parses it, 
 * and takes an optional script file and executes it.
 * BUGS: gets caught in infinite loop during 'r' in script 2
 */



import java.util.*;
import java.io.*;
import java.text.*;

public class lab4 {
   
   private int pc;
   private int[] ram;
   private Hashtable<String,Integer> regMap;
   private String[] regNames;
   private int[] regValues;  
   private ArrayList<Instruction> instrList;
   private Hashtable<String, Integer> labels;
   private int lineCount;
   private int instrCount; 
   private int previousInstruction; //this will be used to check for use-after-load   
   private int currentInstruction;
   private int jumpToInstruction;
   private boolean branch;
   private String[] pipeline;
   private boolean flag;      // whether function requires delays
   private int squashCount; // number of delays for instruction
   private double cycles;    // number of total cycles completed 
   private double instructions; // num of instructions executed
   private String squashCauser;
   private boolean pipeSquash;

   public lab4 () {
      pc = 0;
      ram = new int[8192];
      regMap = new Hashtable<String,Integer>();
      regNames = new String[27];
      regValues = new int[27];
      instrList = new ArrayList<Instruction>();
      labels = new Hashtable<String,Integer>();
      lineCount = 0; 
      instrCount = 0;
      previousInstruction = -1;
      currentInstruction = 0;
      jumpToInstruction = 0;
      branch = false;
      pipeline = new String[4];
      for (int i = 0; i < 4; i++) {
         pipeline[i] = "empty";
      }
      flag = false;
      squashCount = 0;
      cycles = 4;
      instructions = 0;
      squashCauser = "";
      pipeSquash = false;
   }
   
   public void populateRegMap () {
      regMap.put("$zero",0);
      regMap.put("$0",0);
   
      regMap.put("$v0",0);
      regMap.put("$v1",0);

      regMap.put("$a0",0);
      regMap.put("$a1",0);
      regMap.put("$a2",0);
      regMap.put("$a3",0);

      regMap.put("$t0",0);
      regMap.put("$t1",0);
      regMap.put("$t2",0);
      regMap.put("$t3",0);
      regMap.put("$t4",0);
      regMap.put("$t5",0);
      regMap.put("$t6",0);
      regMap.put("$t7",0);

      regMap.put("$s0",0);
      regMap.put("$s1",0);
      regMap.put("$s2",0);
      regMap.put("$s3",0);
      regMap.put("$s4",0);
      regMap.put("$s5",0);
      regMap.put("$s6",0);
      regMap.put("$s7",0);

      regMap.put("$t8",0);
      regMap.put("$t9",0);
 
      regMap.put("$sp",0);

      regMap.put("$ra",0);
   }

   public void makeRegArrays () {
      
      regNames[0] = "$0";
      regNames[1] = "$v0";
      regNames[2] = "$v1";
      regNames[3] = "$a0";
      regNames[4] = "$a1";
      regNames[5] = "$a2";
      regNames[6] = "$a3";
      regNames[7] = "$t0";
      regNames[8] = "$t1";
      regNames[9] = "$t2";
      regNames[10] = "$t3";
      regNames[11] = "$t4";
      regNames[12] = "$t5";
      regNames[13] = "$t6";
      regNames[14] = "$t7";
      regNames[15] = "$s0";
      regNames[16] = "$s1";
      regNames[17] = "$s2";
      regNames[18] = "$s3";
      regNames[19] = "$s4";
      regNames[20] = "$s5";
      regNames[21] = "$s6";
      regNames[22] = "$s7";
      regNames[23] = "$t8";
      regNames[24] = "$t9";
      regNames[25] = "$sp";
      regNames[26] = "$ra";

      regValues[0] = regMap.get("$0");    
      regValues[1] = regMap.get("$v0");
      regValues[2] = regMap.get("$v1");
      regValues[3] = regMap.get("$a0");
      regValues[4] = regMap.get("$a1");
      regValues[5] = regMap.get("$a2");
      regValues[6] = regMap.get("$a3");
      regValues[7] = regMap.get("$t0");    
      regValues[8] = regMap.get("$t1");    
      regValues[9] = regMap.get("$t2");    
      regValues[10] = regMap.get("$t3");
      regValues[11] = regMap.get("$t4");
      regValues[12] = regMap.get("$t5");
      regValues[13] = regMap.get("$t6");
      regValues[14] = regMap.get("$t7");
      regValues[15] = regMap.get("$s0");
      regValues[16] = regMap.get("$s1");
      regValues[17] = regMap.get("$s2");
      regValues[18] = regMap.get("$s3");
      regValues[19] = regMap.get("$s4");
      regValues[20] = regMap.get("$s5");
      regValues[21] = regMap.get("$s6");
      regValues[22] = regMap.get("$s7");
      regValues[23] = regMap.get("$t8");
      regValues[24] = regMap.get("$t9");
      regValues[25] = regMap.get("$sp");
      regValues[26] = regMap.get("$ra");
   }

   public void printMemoryState () {
      makeRegArrays();
      System.out.println("pc = " + pc);
      int i = 0;
      while(i<27) {
         if(i==1) System.out.print(" ");
         System.out.print(regNames[i] + " = " + regValues[i] + "    ");
         i++;
         if(i%4 == 0) System.out.print('\n');
      }
      System.out.print('\n');
   }

   public class Instruction {
      String name, desReg, srcReg, tReg;
      int imm, line, count;

      public Instruction() {
         name = "";
         desReg = "";
         srcReg = "";
         tReg = "";
         imm = 0;
         line = 0;
         count = 0;
      }
	  
      public String printInstr () {
         return "Name = " + this.name + " desReg = " + desReg + " srcReg = " + srcReg + 
		    " tReg = " + tReg + " imm = " + imm + " line = " + line;
      }
      
  } 

   public void printPipe() {
      System.out.println("pc      if/id      id/exe      exe/mem     mem/wb");
      System.out.println(pc + "        " + pipeline[0] + "        " + pipeline[1] + 
      "        " + pipeline[2] + "        " + pipeline[3]);
      /*System.out.print("pc " + pc + " ");
      for (int i = 0; i < 4; i++) {
         System.out.print(pipeline[i] + " ");
      }
      System.out.println();*/
   }      

   // take the instruction and put it in the pipeline array
   public void updatePipe(Instruction instr) {
      if(pipeSquash == false) {
         pipeline[3] = pipeline[2];
         pipeline[2] = pipeline[1];
         pipeline[1] = pipeline[0];
         pipeline[0] = instr.name;
      }
      else { //we are performing a squash or a stall
         if(squashCauser.equals("branch")) { //3 squashes
            pipeline[3] = pipeline[2]; //the beq or bne instr
            pipeline[2] = "squash";
            pipeline[1] = "squash";
            pipeline[0] = "squash";
            currentInstruction = jumpToInstruction;
            pc = currentInstruction;
         }
         else if(squashCauser.equals("jump")) { //1 squash
            pipeline[3] = pipeline[2]; 
            pipeline[2] = pipeline[1];
            pipeline[1] = pipeline[0];
            pipeline[0] = "squash";
            currentInstruction = jumpToInstruction;
            pc = currentInstruction;
         }
         else { //use after load (stall)
            pipeline[3] = pipeline[2];
            pipeline[2] = pipeline[1];
            pipeline[1] = "stall";
            //pipeline[0] does not change
         }
      }
   }

   public void executeInstruction (Instruction instr) {
      int i;
      
      //updatePipe(instr);

      Instruction prev;

      instructions++;
      if(previousInstruction == -1) prev = null; //ensure that we are not on first instr of program
      else prev = instrList.get(previousInstruction);

      if(instr.name.equals("add")) {
         regMap.put(instr.desReg, regMap.get(instr.srcReg) + regMap.get(instr.tReg));

         if(prev != null) { //make sure we are not on first instr of program
            if(prev.name.equals("lw")) {
               if(instr.srcReg.equals(prev.tReg) || instr.tReg.equals(prev.tReg)) {
                  flag = true; //we have entered a "squash routine" (stall in this case)
                  squashCount = 1; //not sure about this right now
                  squashCauser = "useAfterLoad";
               }
            }
         }      
      }
      else if(instr.name.equals("addi")) {
         regMap.put(instr.tReg, regMap.get(instr.srcReg) + instr.imm);

         if(prev != null) { //make sure we are not on first instr of program
            if(prev.name.equals("lw")) {
               if(instr.srcReg.equals(prev.tReg)) {
                  flag = true; //we have entered a "squash routine" (stall in this case)
                  squashCount = 1; //not sure about this right now
                  squashCauser = "useAfterLoad";
               }
            }
         }      
      }
      else if(instr.name.equals("sub")) {
         regMap.put(instr.desReg, regMap.get(instr.srcReg) - regMap.get(instr.tReg));

         if(prev != null) { //make sure we are not on first instr of program
            if(prev.name.equals("lw")) {
               if(instr.srcReg.equals(prev.tReg) || instr.tReg.equals(prev.tReg)) {
                  flag = true; //we have entered a "squash routine" (stall in this case)
                  squashCount = 1; //not sure about this right now
                  squashCauser = "useAfterLoad";
               }
            }
         }      
      }
      else if(instr.name.equals("or")) {
         regMap.put(instr.desReg, regMap.get(instr.srcReg) | regMap.get(instr.tReg));

         if(prev != null) { //make sure we are not on first instr of program
            if(prev.name.equals("lw")) {
               if(instr.srcReg.equals(prev.tReg) || instr.tReg.equals(prev.tReg)) {
                  flag = true; //we have entered a "squash routine" (stall in this case)
                  squashCount = 1; //not sure about this right now
                  squashCauser = "useAfterLoad";
               }
            }
         }      
      }
      else if(instr.name.equals("and")) {
         regMap.put(instr.desReg, regMap.get(instr.srcReg) & regMap.get(instr.tReg));

         if(prev != null) { //make sure we are not on first instr of program
            if(prev.name.equals("lw")) {
               if(instr.srcReg.equals(prev.tReg) || instr.tReg.equals(prev.tReg)) {
                  flag = true; //we have entered a "squash routine" (stall in this case)
                  squashCount = 1; //not sure about this right now
                  squashCauser = "useAfterLoad";
               }
            }
         }      
      }
      else if(instr.name.equals("slt")) {
         if(regMap.get(instr.srcReg) < regMap.get(instr.tReg)) regMap.put(instr.desReg, 1);
         else regMap.put(instr.desReg, 0);
         if(prev != null) { //make sure we are not on first instr of program
            if(prev.name.equals("lw")) {
               if(instr.srcReg.equals(prev.tReg) || instr.tReg.equals(prev.tReg)) {
                  flag = true; //we have entered a "squash routine" (stall in this case)
                  squashCount = 1; //not sure about this right now
                  squashCauser = "useAfterLoad";
               }
            }
         }      
      }
      else if(instr.name.equals("sll")) {
         regMap.put(instr.desReg, (regMap.get(instr.tReg)) << instr.imm);
         if(prev != null) { //make sure we are not on first instr of program
            if(prev.name.equals("lw")) {
               if(instr.desReg.equals(prev.tReg)) {
                  flag = true; //we have entered a "squash routine" (stall in this case)
                  squashCount = 1; //not sure about this right now
                  squashCauser = "useAfterLoad";
               }
            }
         }      
      }
      else if(instr.name.equals("beq")) {
         int labelLocation;
         if(regMap.get(instr.srcReg) == regMap.get(instr.tReg)) {
            flag = true; //we have entered a "squash routine"
            squashCount = 3; //we will squash 3 instructions 
            squashCauser = "branch";           

            labelLocation = instr.imm + instr.count+1;
            for(i=0;i<instrList.size();i++) { 
              if(instrList.get(i).count >= labelLocation) { //first instruction we encounter that's equal or greater than label line no.
                 branch = true;
                 jumpToInstruction = instrList.get(i).count;
                 i=10000;
              }
              else {
                 branch = false;
              }
           }
         }
         else {
            branch = false;
         }
      }
      else if(instr.name.equals("bne")) {
         int labelLocation;   
         if(regMap.get(instr.srcReg) != regMap.get(instr.tReg)) {
            flag = true; //we have entered a "squash routine"
            squashCount = 3; //we will squash 3 instructions 
            squashCauser = "branch";  

            labelLocation = instr.imm + instr.count + 1;         
            for(i=0;i<instrList.size();i++) { 
               if(instrList.get(i).count >= labelLocation) { //first instruction we encounter that's equal or greater than label line no.
                  branch = true;
                  jumpToInstruction = instrList.get(i).count;
                  i=10000;
               }
               else {
                  branch = false;
               }
            }
         }
         else {
            branch = false;
         }
      }
      else if(instr.name.equals("lw")) {
         regMap.put(instr.tReg, ram[regMap.get(instr.srcReg) + instr.imm]);

         if(prev != null) { //make sure we are not on first instr of program
            if(prev.name.equals("lw")) {
               if(instr.srcReg.equals(prev.tReg)) {
                  flag = true; //we have entered a "squash routine" (stall in this case)
                  squashCount = 1; //not sure about this right now
                  squashCauser = "useAfterLoad";
               }
            }
         }      
      }
      else if(instr.name.equals("sw")) {
         ram[regMap.get(instr.srcReg) + instr.imm] = regMap.get(instr.tReg);

         if(prev != null) { //make sure we are not on first instr of program
            if(prev.name.equals("lw")) {
               if(instr.srcReg.equals(prev.tReg) || instr.tReg.equals(prev.tReg)) {
                  flag = true; //we have entered a "squash routine" (stall in this case)
                  squashCount = 1; //not sure about this right now
                  squashCauser = "useAfterLoad";
               }
            }
         }      
      }
      else if(instr.name.equals("j")) {
         flag = true; //we have entered a "squash routine"
         squashCount = 1; //we will squash 1 instruction 
         squashCauser = "jump"; 
 
         for(i=0;i<instrList.size();i++) {
            if(instrList.get(i).count >= instr.imm) {
               jumpToInstruction = instrList.get(i).count;
               i=10000;
            }
         }
      }
      else if(instr.name.equals("jr")) {
         flag = true; //we have entered a "squash routine"
         squashCount = 1; //we will squash 1 instruction 
         squashCauser = "jump";

         for(i=0;i<instrList.size();i++) {
            if(instrList.get(i).count >= regMap.get(instr.srcReg)) {
               jumpToInstruction = instrList.get(i).count;
               i=10000;
            }
         }
      }
      else if(instr.name.equals("jal")) {  
         flag = true; //we have entered a "squash routine"
         squashCount = 1; //we will squash 1 instruction 
         squashCauser = "jump";

         regMap.put("$ra", currentInstruction+1);
         for(i=0;i<instrList.size();i++) {
            if(instrList.get(i).count >= instr.imm) {
               jumpToInstruction = instrList.get(i).count;
               i=10000;
            }
         }
      }         
      else {}
   }

   public void scanFileNames (String[] args) throws FileNotFoundException {
      int argLength;
      File script = null, mips;
      
      //incorrect number of arguments
      if(args.length < 1 || args.length > 2) {
         System.out.println("Format: java lab3 [mipsFile.asm] [optional script file]");
         System.exit(-1);
      }

      argLength = args[0].length();

      //incorrect formatting 
      if(!args[0].substring(argLength-4,argLength).equals(".asm")) {
         System.out.println("Wrong file format");
         System.exit(-1);
      }


      mips = new File(args[0]);
    
      //if script file is included
      if(args.length == 2) {
         script = new File(args[1]);
      }

      parseMips (mips);
      scanCommands(script);
   
   }

   public void parseMips (File mips) throws FileNotFoundException {
      findLabels(mips);
      findInstruction(mips);  
   }
   
   /************************************************************************/
   /***************          MODDED LAB 2 FUNCTIONS            *************/
   /************************************************************************/   
   
   //fills label hashmap
   public void findLabels(File mipsFile) throws FileNotFoundException {
      Scanner lineScan, fileScan = new Scanner(mipsFile);
      String line;
      lineCount = 0;
      while (fileScan.hasNextLine()) {
         line = fileScan.nextLine().trim();
        
         if (line.contains("#")) { 
            line = line.substring(0, line.indexOf('#')).trim();
         }
         if (!line.equals("")) {
            if (line.contains(":")) {
               lineScan = new Scanner(line);
               lineScan.useDelimiter(":");
               line = lineScan.next().trim();
               System.out.println(line + " " + this.lineCount);
               this.labels.put(line, this.lineCount);
               lineScan.useDelimiter(":");
               if (lineScan.hasNext()) {
                  line = lineScan.next().trim();
                  System.out.println(line);
                  if (!line.equals("")) {
                     lineCount++;
                  }
               }
               lineScan.close();
            }
            else {
               lineCount++;
            }
         }
      }
   }
   //fills instr fields: name, imm
   public void findInstruction(File mipsFile) throws FileNotFoundException {
      this.lineCount = 0;
      Scanner lineScan, fileScan = new Scanner(mipsFile);
      String line, args="";
      int regNdx = 0;
      while (fileScan.hasNextLine()) {
         Instruction instr = new Instruction();
         line = fileScan.nextLine().trim(); 
         try {
            if (!line.equals("")) {
               if (line.charAt(0) != '#') { 
                  if (line.contains("#")) {
                     line = line.substring(0, line.indexOf("#")).trim();
                  }
		  		  
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
                     instr.name = lineScan.next().trim();
                     args = lineScan.nextLine().trim(); //this is line in question
                  }
                  else {
                     instr.name = line.substring(0, regNdx).trim();
                     args = line.substring(regNdx, line.length()).trim();
                  }
                  instr.line = lineCount;
                  instr.count = instrCount;
                  decode(instr, args);
                  instrCount++;
               }
            }
            lineCount++;
         } 
         catch (NoSuchElementException e) {
         }
      }
   }
    //fills instr fields: imm
    public void decode(Instruction instr, String args) {
      Scanner scan;
      String immediate = "";
      String[] register = {"", "", ""};
      int i = 0; 
      int imm = 0;
      boolean decodeFlag;
      args = args.trim();
      scan = new Scanner(args);

      scan.useDelimiter(",");
      while (scan.hasNext()) {
         args = scan.next().trim(); //ex: $a0
         decodeFlag = false; //indicates whether it is a label or immediate value
         if (i > 2) {
            System.out.println("Invalid args");
            System.exit(0);
         }

         if (args.contains("($")) { //lw or sw
            immediate = args.substring(0, 1);
            register[i] = args.substring(2, args.length() - 1);
            imm = Integer.parseInt(immediate);
            if (register[i]==null) {
               System.out.println("Register doesn't exist");
               System.exit(0);
            }
            i++;
         }
         else if (args.contains("$")) { //regular register (e.g. "$a0")
            register[i] = args;
            if (args == null) { //setting args to reg array as before
               System.out.println("Register doesn't exist");
               System.exit(0);
            }
            i++;
         }
         else { //immediate value or label (label will be converted to value)
            try {
               imm = Integer.parseInt(args);
            }
            catch (NumberFormatException e) {  //label
               decodeFlag = true;
               if (null == (Integer)(imm = this.labels.get(args))) { //sets imm to correct val for a label
                  System.out.println("Label doesn't exist");
                  System.exit(0);
               }
            }
            if (instr.name.equals("j") ||     //logic specifically for j/jal (imm only)
             instr.name.equals("jal")) {
			   

            }
            else { //this is only executed when the current instr is beq/bne with label
               if (decodeFlag) { //label
                  imm = imm - (this.instrCount + 1);
               } 
            }
         }
      }
      instr.imm = imm;
      fillInstruction(instr, register[0], register[1], register[2]);
   }

   
   //fills fields: desReg, srcReg, tReg
   public void fillInstruction (Instruction instr, String reg0, String reg1, String reg2) {
      String name = instr.name;
	  if(name.equals("add") || name.equals("sub") || name.equals("and") || name.equals("or") || name.equals("slt")) {
	     instr.desReg = reg0;
        instr.srcReg = reg1;
        instr.tReg = reg2;
	  }
	  else if(name.equals("addi")) {
	     instr.tReg = reg0;
        instr.srcReg = reg1;
	  }
	  else if(name.equals("sll")) {
	     instr.desReg = reg0;
	     instr.tReg = reg1;
	  }
     else if(name.equals("lw") || name.equals("sw")) {
        instr.tReg = reg0;
        instr.srcReg = reg1;
     }
	  else if(name.equals("beq") || name.equals("bne")) {
	     instr.srcReg = reg0;
	     instr.tReg = reg1;
     }
	  else if(name.equals("j") || name.equals("jal")) {
	     
	  }
	  else { //jr
	     instr.srcReg = reg0;
	  }
	  //now that the current instruction has all data, add to list
	  instrList.add(instr);
   }
   
   public void printInstrList () {
      int i;
      for(i=0;i<instrList.size();i++) {
	      System.out.println("Name = " + instrList.get(i).name + "     desReg = " + instrList.get(i).desReg + 
          "     srcReg = " + instrList.get(i).srcReg + "     tReg = " + instrList.get(i).tReg + "     imm = " + 
          instrList.get(i).imm + "    line = " + instrList.get(i).line + "    count = " + instrList.get(i).count);
      }
   }
  
   public void stepInstr() {
      DecimalFormat numFormat = new DecimalFormat("#.00");
      if(currentInstruction >= instrList.size()) {
            System.out.println("Program complete");
            System.out.println("CPI = " + numFormat.format(cycles/instructions) + "      Cycles = " + 
            (int)cycles + "      Instructions = " + (int)instructions);
            return;
      }
      if(instrList.get(currentInstruction) == null) {
         System.out.println("instrList.get(currentInstruction) is null");
         System.exit(0);
      }

      if(flag == false) { //we are not in a "squash routine"
         executeInstruction(instrList.get(currentInstruction));
         pc++;
         updatePipe(instrList.get(currentInstruction));
         previousInstruction = currentInstruction;
         currentInstruction++;
      }
      else { //flag is true, and we are in a squash routine
         squashCount--;
         if(squashCount != 0) { //we don't want to execute, but we will update pipe and increment pc
            pc++;
            updatePipe(instrList.get(currentInstruction));
            previousInstruction = currentInstruction;
            currentInstruction++;
         }
         else { //squash count is 0, so we perform squash/stall 
            pipeSquash = true;
            updatePipe(instrList.get(currentInstruction));

            flag = false;
            squashCount = 100; //this will get set to legit value next squash routine we encounter. here we must set it to non-zero value
            pipeSquash = false;
            squashCauser = "";
         }
      }
      cycles++;

   }


   public void interpretCommand (String cmd) {
      DecimalFormat numFormat = new DecimalFormat("#.000");
      int i,num1,num2;
      if(cmd.equals("h")) {
         System.out.println("");
         System.out.println("h = show help");
         System.out.println("d = dump register state");
         System.out.println("p = show pipeline registers");
         System.out.println("s = step through a single clock cycle (i.e. simulate one cycle and stop)");
         System.out.println("s num = step through num clock cycles");
         System.out.println("r = run until the program ends and display timing summary");
         System.out.println("m num1 num2 = display data memory from location num1 to num2");
         System.out.println("c = clear all registers, memory, and the program counter to 0");
         System.out.println("q = exit the program");
         System.out.println("");
      }
      else if(cmd.equals("d")) {
         System.out.println("");
         printMemoryState();
         System.out.println("");
      }
      else if(cmd.equals("p")) {
         printPipe();
      }
      else if(cmd.equals("s")) {
         stepInstr();
         if(currentInstruction < instrList.size()) printPipe();
         //System.out.println("       1 instruction(s) executed");
      }
      else if(cmd.length() > 1) {
         if(cmd.contains("s")) {
            cmd = cmd.substring(1);
            cmd = cmd.trim();
            num1 = Integer.parseInt(cmd);
            for(i=0;i<num1;i++) {
               if(currentInstruction == instrList.size()) {
                  //System.out.println("Program complete");
                  //System.out.println("CPI = " + numFormat.format(cycles/instructions) + "      Cycles = " + 
                  //(int)cycles + "      Instructions = " + (int)instructions);
               }
               stepInstr();   
            }
            printPipe();
            System.out.println("       " + num1 + " instruction(s) executed");
         }
         else if(cmd.contains("m")) {
            Scanner sc = new Scanner(cmd);
            sc.next();
            num1 = (int)Integer.parseInt(sc.next());
            num2 = (int)Integer.parseInt(sc.next());
            System.out.println("");
            for(i=num1;i<=num2;i++) {
               System.out.println("[" + i + "] = " + ram[i]);
            }
            System.out.println(""); 
         }
         else {}
      }
      else if(cmd.equals("r")) {
         while(currentInstruction < instrList.size()) {
            stepInstr();
         }
         System.out.println("Program complete");
         System.out.println("CPI = " + numFormat.format(cycles/instructions) + "      Cycles = " + 
         (int)cycles + "      Instructions = " + (int)instructions);
      }
      else if(cmd.equals("c")) {
         pc = 0;
         populateRegMap(); //this will reset all registers to 0
         for(i=0;i<8192;i++) {
            ram[i] = 0;
         }
         previousInstruction = 0;
         currentInstruction = 0;
         System.out.println("        Simulator reset"); 
      }
      else if(cmd.equals("q")) {
         System.exit(0);
      }
      else {
         System.out.println("Command not recognized");
         System.exit(0);
      }
   }

   public void scanCommands (File script) throws FileNotFoundException {
      String line;
      if(script == null) {
         Scanner sc;
         while(true) {
            System.out.print("mips> ");
            sc = new Scanner(System.in);
            interpretCommand(sc.nextLine());
         }
      }
      else {   //script is not null --> we will scan script file
         Scanner fsc = new Scanner(script);
         while(fsc.hasNextLine()) {
            line = fsc.nextLine();
            System.out.println("mips> " + line);
            interpretCommand(line);
         }
      }             
   }
         
 
   public static void main (String[] args) throws FileNotFoundException {
      lab4 spim = new lab4();

      spim.populateRegMap();
      spim.scanFileNames(args);
   }

}
