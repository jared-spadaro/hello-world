
public static void instrDecode () {
   instrMap.put("and","000000100100");
   instrMap.put("or","000000100000"); //incorrect
   instrMap.put("add","000000100000");
   instrMap.put("addi","001000");
   instrMap.put("sll","000000100000"); //incorrect
   instrMap.put("sub","000000100010");
   instrMap.put("slt","000000100000"); //incorrect
   instrMap.put("beq","000100");
   instrMap.put("bne","000000100000"); //incorrect
   instrMap.put("lw","000000100000"); //incorrect
   instrMap.put("sw","000000100000"); //incorrect
   instrMap.put("j","000000100000"); //incorrect
   instrMap.put("jr","000000100000"); //incorrect
   instrMap.put("jal","000000100000"); //incorrect
}


public static void regDecode () {
   //zero registers
   regMap.put("$zero","00000");
   regMap.put("$0","00000");
   //result registers
   regMap.put("$v0","00010");
   regMap.put("$v1","00011");
   //argument registers
   regMap.put("$a0","00100");
   regMap.put("$a1","00101");
   regMap.put("$a2","00110");
   regMap.put("$a3","00111");
   //temporary registers
   regMap.put("$t0","01000");
   regMap.put("$t1","01001");
   regMap.put("$t2","01010");
   regMap.put("$t3","01011");
   regMap.put("$t4","01100");
   regMap.put("$t5","01101");
   regMap.put("$t6","01110");
   regMap.put("$t7","01111");
   //saved registers
   regMap.put("$s0","10000");
   regMap.put("$s1","10001");
   regMap.put("$s2","10010");
   regMap.put("$s3","10011");
   regMap.put("$s4","10100");
   regMap.put("$s5","10101");
   regMap.put("$s6","10110");
   regMap.put("$s7","10111");
   //more temporary registers
   regMap.put("$t8","11000");
   regMap.put("$t9","11001");
   //stack pointer
   regMap.put("$sp","11101");
   //return address
   regMap.put("$ra","11111");
}
