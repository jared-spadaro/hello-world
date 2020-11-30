# Jared Spadaro and Michael Woodson
# Section: 1
# Description: Takes two arguments, raises the first to the power of the second

# Java Code
# public static int exponent (int x, int y) {
#    int i = x, j = y-1, result = 0, temp = x, z = x;
#    while (j-- > 0) {
#       result = 0;
#       temp = z;
#       i = x;
#       while (i-- > 0) {
#          result += temp;
#          z = result;
#       }
#    }
#    return result;
# }

#global strings
.globl prompt_one
.globl prompt_two
.globl result

#Data Area
.data

prompt_one:
	.asciiz "Enter a number \n"

prompt_two:
	.asciiz "Enter an exponent \n"

result:
	.asciiz "Result = "

#Text Area
.text

main:

	#Display prompt one
	ori $v0, $0, 4
	lui $a0, 0x1001
	syscall

	#Read in number
	ori $v0, $0, 5
	syscall

	#Place number in a1
	addu $a1, $v0, $0

	#Display prompt two
	ori $v0, $0, 4
	lui $a0, 0x1001
	ori $a0, $a0, 0x11
	syscall

	#Read in exponent
	ori $v0, $0, 5
	syscall

	#Place exponent in a2
	addu $a2, $v0, $0

	#initialization

        #inner loop counter
	addu $s0, $a1, $0 

	#outer loop counter (one less than exponent)
	add $s1, $a2, -1 

	#initialize sum to 0
	addu $s2, $0, $0
 	
        #create 2 copies of number
	addu $s3, $a1, $0
        addu $s4, $a1, $0

outerloop:
	
	#outer loop check
	beq $s1, $0, end

	#set sum back to 0 at start to prevent extra sum
	addu $s2, $0, $0

	#set s3 to s4 to ensure proper summing in inner loop
	addu $s3, $s4, $0

	#reset inner loop counter
	addu $s0, $a1, $0

	#decrement outer loop counter
	addi $s1, $s1, -1

innerloop:

	#inner loop check
	beq $s0, $0, outerloop

	#add number to itself (multiply), store in register
	addu $s2, $s2, $s3 

	#set backup copy of number to new sum
	addu $s4, $s2, $0

	#decrement inner loop counter
	addi $s0, $s0, -1

	j innerloop

end:

	#print result string
	ori $v0, $0, 4
	lui $a0, 0x1001
	ori $a0, $a0, 0x25
	syscall

	#print result
	ori $v0, $0, 1
	addu $a0, $s2, $0
	syscall

	#Exit
	ori $v0, $0, 10
	syscall
	
