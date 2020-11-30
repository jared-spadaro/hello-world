# Jared Spadaro and Michael Woodson
# Section: 1
# Description: divides a 64-bit unsigned number with a 31-bit unsigned number

# Java Code
# public static void divide(int upper, int lower, int div) {
#    int shifts = 0;
#    int temp = 0;
#
#    while (div != 1) {
#       div >>= 1;
#       temp |= (upper & 1) << shifts;
#       shifts++;
#       upper >>= 1;
#    }
#
#    lower >>>= shifts;
#    temp <<= 32 - shifts;
#    lower |= temp;
#    System.out.println("Upper: " + upper + " Lower: " + lower);
# }

# declare global so programmer can see actual addresses.
.globl upper
.globl lower
.globl divisor
.globl resultUp
.globl resultLow

#  Data Area (this area contains strings to be displayed during the program)
.data

# 32 bytes, or in 0
upper:
   .asciiz "Enter the upper 32-bit number.\n"

# 32 bytes, or in 32
lower:
   .asciiz "Enter the lower 32-bit number.\n"

# 19 bytes, or in 64
divisor: 
   .asciiz "Enter the divisor\n"

# 9 bytes, or in 83
resultUp:
   .asciiz "Upper = "

# 10 bytes, or in 92
resultLow:
   .asciiz " Lower = "

#Text Area (i.e. instructions)
.text

main:
   #prompts user to enter upper 32 bits
   ori   $v0, $0, 4
   lui   $a0, 0x1001
   syscall

   #reads upper 32 bits from user
   ori   $v0, $0, 5
   syscall

   #store input into $s0
   add   $s0, $0, $v0

   #prompts user to enter lower 32 bits
   ori   $v0, $0, 4
   lui   $a0, 0x1001
   ori   $a0, $a0, 0x20
   syscall

   #reads lower 32 bits from user
   ori   $v0, $0, 5
   syscall

   #store input into $s1
   add $s1, $0, $v0

   #prompts user to enter divisor
   ori   $v0, $0, 4
   lui   $a0, 0x1001
   ori   $a0, $a0, 0x40
   syscall
   
   #reads divisor from user
   ori   $v0, $0, 5
   syscall
   
   #store input into $s2
   add   $s2, $0, $v0

   #contains the number of shifts
   add   $t0, $0, $0
  
   #contains the temp bit value
   add   $t1, $0, $0

   #set compare register to 1
   addi  $t2, $0, 1

   #temporary reg
   add   $t3, $0, $0

loop:
   beq   $s2, $t2, shift
   srl   $s2, $s2, 1
   andi  $t3, $s0, 1
   sllv  $t3, $t3, $t0
   or    $t1, $t1, $t3
   addi  $t0, $t0, 1
   srl   $s0, $s0, 1
   j loop 
 
shift:
   srlv  $s1, $s1, $t0 
   addi  $t3, $0, 32
   sub   $t3, $t3, $t0
   sllv  $t1, $t1, $t3
   or    $s1, $s1, $t1

   #display upper text
   ori   $v0, $0, 4
   lui   $a0, 0x1001
   ori   $a0, $a0, 0x53
   syscall

   #display upper
   ori   $v0, $0, 1
   add,  $a0, $0, $s0
   syscall

   #display lower text
   ori   $v0, $0, 4
   lui   $a0, 0x1001
   ori   $a0, $a0, 0x5c
   syscall

   #display lower
   ori   $v0, $0, 1
   add   $a0, $0, $s1
   syscall

   #exit
   ori   $v0, $0, 10
   syscall 
