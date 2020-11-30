#   Parity Checker
#   Jared Spadaro and Michael Woodson
#   Section 1
#   Description: Returns 1 for even parity, 0 for odd parity


#   Java Function
#
#   public static int parity(int num) {
#      int parity = 1;
#      while (num != 0) {
#         parity = parity ^ (num & 1);
#         num >>= 1;
#      }
#
#      return parity; 
#   }


#global labels
.globl prompt
.globl result

#Data Area
.data

prompt:
	.asciiz "Enter a number \n"

result:
	.asciiz "Parity = "

#Text Area
.text

main:

	#Display the prompt
	ori $v0, $0, 4
	lui $a0, 0x1001
	syscall

	#Scan in the number
	ori $v0, $0, 5
	syscall

	#Place number into s0
	addu $s0, $v0, $0

	#Parity value, defaulted to 1
	addi $s1, $0, 1 

loop:

	beq $s0, $0, end
	andi $s2, $s0, 1
	xor $s1, $s1, $s2
	srl $s0, $s0, 1
	j loop

end:

	#Print out result string
	ori $v0, $0, 4
	lui $a0, 0x1001
	ori $a0, $a0, 0x11
	syscall

	#Load and print out result
	addu $a0, $s1, $0
	ori $v0, $0, 1
	syscall
 
	#Exit
	ori $v0, $0, 10
	syscall











	






