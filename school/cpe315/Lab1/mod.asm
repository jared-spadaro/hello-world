#   Mod Program
#   Jared Spadaro and Michael Woodson
#   Section: 1
#   Description: divides a divisor into a number and returns the remainder


#   Java Function
#
#   public static int mod(int num, int div) {
#      return num & div-1;
#   }


# declare global so programmer can see actual addresses.
.globl prompt_one
.globl prompt_two
.globl result

#  Data Area (this area contains strings to be displayed during the program)
.data

prompt_one:
	.asciiz "Input a number \n"

prompt_two:
	.asciiz "Input a divisor \n"

result: 
	.asciiz "Remainder = "

#Text Area (i.e. instructions)
.text

main:
	#Display prompt one
	ori $v0, $0, 4
        add $a0, $0, $0
	lui $a0, 0x1001
	syscall

	#Scan in first number
	ori $v0, $0, 5
	syscall

	#Place first number into a1 [NUMBER]
	addu $a1, $v0, $0

	#Display prompt two
	ori $v0, $0, 4
	lui $a0, 0x1001
	ori $a0, $a0, 0x11
	syscall

	#Scan in second number
	ori $v0, $0, 5
	syscall

	#Place second number into a2 [DIVISOR]
	addu $a2, $v0, $0

	#Decrement DIVISOR by 1
	addi $a2, $a2, -1

	#Bitwise AND decremented divisor with number
	and $s0, $a1, $a2

	#Print result string
	ori $v0, $0, 4
	lui $a0, 0x1001
	ori $a0, $a0, 0x23
	syscall

	#Clear a0
	add $a0, $0, $0

	#Print result
	ori $v0, $0, 1
	addu $a0, $s0, $0
	syscall

	#Exit
	ori $v0, $0, 10
	syscall	






