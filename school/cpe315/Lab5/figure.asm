Begin:
                   addi $sp, $0, 8142
                   add $t5, $0, $0
                   
                   # head
                   addi $a0, $0, 30
                   addi $a1, $0, 100
                   addi $a2, $0, 20
                   jal Circle
                   
                   # body
                   addi $a0, $0, 30
                   addi $a1, $0, 80
                   addi $a2, $0, 30
                   addi $a3, $0, 30
                   jal Line
                   
                   # left leg
                   addi $a0, $0, 20
                   addi $a1, $0, 1
                   addi $a2, $0, 30
                   addi $a3, $0, 30
                   jal Line
                   
                   # right leg
                   addi $a0, $0, 40
                   addi $a1, $0, 1
                   addi $a2, $0, 30
                   addi $a3, $0, 30
                   jal Line
                   
                   # left arm
                   addi $a0, $0, 15
                   addi $a1, $0, 60
                   addi $a2, $0, 30
                   addi $a3, $0, 50
                   jal Line
                   
                   # right arm
                   addi $a0, $0, 30
                   addi $a1, $0, 50
                   addi $a2, $0, 45
                   addi $a3, $0, 60
                   jal Line
                   
                   # left eye
                   addi $a0, $0, 24
                   addi $a1, $0, 105
                   addi $a2, $0, 3
                   jal Circle
                   
                   # right eye
                   addi $a0, $0, 36
                   addi $a1, $0, 105
                   addi $a2, $0, 3
                   jal Circle
                   
                   # mouth center
                   addi $a0, $0, 25
                   addi $a1, $0, 90
                   addi $a2, $0, 35
                   addi $a3, $0, 90
                   jal Line
                   
                   # mouth left
                   addi $a0, $0, 25
                   addi $a1, $0, 90
                   addi $a2, $0, 20
                   addi $a3, $0, 95
                   jal Line
                   
                   # mouth right
                   addi $a0, $0, 35
                   addi $a1, $0, 90
                   addi $a2, $0, 40
                   addi $a3, $0, 95
                   jal Line
                   
                   j end

# $s0 = st
# $s1 = x
# $s2 = y
# $t0 = deltax
# $t1 = deltay
# $t2 = error
# $t3 = ystep
# $t4 = reserved for temp values
# $t5 = plot index (in data memory)
# $t6 = reserved for temp values
# $t7 = reserved for temp values
# $a0 = x0
# $a1 = y0
# $a2 = x1
# $a3 = y1
# calls helper functions 'swap' and 'abs'
Line:               
                      sub $t0, $a3, $a1 
                      addi $sp, $sp, 2
                      sw $a0, 0($sp)
                      sw $ra, -1($sp)
                      add $a0, $t0, $0
                      jal abs
                      lw $a0, 0($sp)
                      add $s3, $v0, $0 # abs y
                      sub $t0, $a2, $a0
                      sw $a0, 0($sp)
                      add $a0, $t0, $0
                      jal abs
                      add $s2, $v0, $0 # abs x
                      lw $a0, 0($sp)
                      addi $sp, $sp, -1
                      add $s0, $0, $0
                      slt $s0, $s2, $s3
                      addi $t0, $0, 1
                      
                      # Swap1
                      # if st == 1, execute swaps below
                      bne $s0, $t0, Swap2
                      jal swap
                      addi $sp, $sp, 2
                      sw $a0, 0($sp)
                      sw $a1, -1($sp)
                      add $a0, $a2, $0
                      add $a1, $a3, $0
                      jal swap
                      add $a2, $a0, $0
                      add $a3, $a1, $0
                      lw $a0, 0($sp)
                      lw $a1, -1($sp)
                      addi $sp, $sp, -2
Swap2:
                      add $t1, $0, $0
                      slt $t1, $a2, $a0
                      
                      # Skip these swaps if x0 > x1
                      beq $t1, $0, Delta
                      addi $sp, $sp, 1
                      sw $a1, 0($sp)
                      add $a1, $a2, $0
                      jal swap
                      add $a2, $a1, $0
                      lw $a1, 0($sp)
                      sw $a0, 0($sp)
                      add $a0, $a3, $0
                      jal swap
                      add $a3, $a0, $0
                      lw $a0, 0($sp)
                      addi $sp, $sp, -1
Delta:
                      sub $t0, $a2, $a0
                      addi $sp, $sp, 1
                      sw $a0, 0($sp)
                      sub $a0, $a3, $a1
                      jal abs
                      add $t1, $a0, $0
                      lw $a0, 0($sp)
                      addi $sp, $sp, -1
                      add $t2, $0, $0
                      add $s2, $a1, $0
Ystep:
                      addi $t4, $0, 1
                      slt $t3, $a1, $a3
                      add $s1, $a0, $0
                      beq $t3, $t4, Plot1
                      addi $t3, $0, -1
Plot1:
                      addi $t7, $a2, 1
                      beq $s1, $t7, EndLine
                      addi $t4, $0, 1
                      bne $s0, $t4, PlotXY
PlotYX:
                      sw $s2, 0($t5)
                      addi $t5, $t5, 1
                      sw $s1, 0($t5)
                      addi $t5, $t5, 1
                      j Error
PlotXY:
                      sw $s1, 0($t5)
                      addi $t5, $t5, 1
                      sw $s2, 0($t5)
                      addi $t5, $t5, 1
Error:
                      add $t2, $t2, $t1
                      add $t4, $t2, $t2
                      slt $t6, $t4, $t0
                      addi $t4, $0, 1
                      beq $t6, $t4, Iterate
                      add $s2, $s2, $t3
                      sub $t2, $t2, $t0
Iterate:
                      addi $s1, $s1, 1
                      j Plot1
EndLine:
                      lw $ra, 0($sp)
                      addi $sp, $sp, -1
                      jr $ra
                      
# function to create a circle
# $a0 = xc
# $a1 = yc
# $a2 = r
# $t0 = x
# $t1 = y
# $t2 = g
# $t3 = diagonalInc
# $t4 = rightInc
# $s0 = reserved for temp
# $t6 = reserved for temp
# $t7 = reserved for temp
Circle:
                      addi $t0, $0, $0
                      add $t1, $a2, $0
                      add $s0, $a2, $a2
                      addi $t6, $0, 3
                      sub $t2, $t6, $s0
                      addi $s0, $0, 4
                      add $t6, $0, $0
MultiplyR:
                      beq $s0, $0, Assign
                      add $t6, $t6, $a2
                      addi $s0, $s0, -1
                      j MultiplyR
Assign:
                      addi $s0, $0, 10
                      sub $t3, $s0, $t6
                      addi $t4, $0, 6
                      add $s0, $0, $0
Plot:
                      addi $t7, $0, 1
                      slt $s0, $t1, $t0
                      beq $s0, $t7, EndCircle
                      
                      # point 1
                      add $t6, $a0, $t0
                      add $t7, $a1, $t1
                      sw $t6, 0($t5)
                      addi $t5, $t5, 1
                      sw $t7, 0($t5)
                      addi $t5, $t5, 1
                      
                      # point 2
                      add $t6, $a0, $t0
                      sub $t7, $a1, $t1
                      sw $t6, 0($t5)
                      addi $t5, $t5, 1
                      sw $t7, 0($t5)
                      addi $t5, $t5, 1
                      
                      # point 3 
                      sub $t6, $a0, $t0
                      add $t7, $a1, $t1
                      sw $t6, 0($t5)
                      addi $t5, $t5, 1
                      sw $t7, 0($t5)
                      addi $t5, $t5, 1
                      
                      # point 4 
                      sub $t6, $a0, $t0
                      sub $t7, $a1, $t1
                      sw $t6, 0($t5)
                      addi $t5, $t5, 1
                      sw $t7, 0($t5)
                      addi $t5, $t5, 1
                      
                      # point 5
                      add $t6, $a0, $t1
                      add $t7, $a1, $t0
                      sw $t6, 0($t5)
                      addi $t5, $t5, 1
                      sw $t7, 0($t5)
                      addi $t5, $t5, 1
                      
                      # point 6
                      add $t6, $a0, $t1
                      sub $t7, $a1, $t0
                      sw $t6, 0($t5)
                      addi $t5, $t5, 1
                      sw $t7, 0($t5)
                      addi $t5, $t5, 1
                      
                      # point 7
                      sub $t6, $a0, $t1
                      add $t7, $a1, $t0
                      sw $t6, 0($t5)
                      addi $t5, $t5, 1
                      sw $t7, 0($t5)
                      addi $t5, $t5, 1
                      
                      # point 8 
                      sub $t6, $a0, $t1
                      sub $t7, $a1, $t0
                      sw $t6, 0($t5)
                      addi $t5, $t5, 1
                      sw $t7, 0($t5)
                      addi $t5, $t5, 1
                      
                      slt $t6, $0, $t2
                      beq $t6, $0, RightInc
DiagonalInc:
                      add $t2, $t2, $t3
                      addi $t3, $t3, 8
                      addi $t1, $t1, -1
                      j Increment
RightInc:
                      add $t2, $t2, $t4
                      addi $t3, $t3, 4
Increment:
                      addi $t4, $t4, 4
                      addi $t0, $t0, 1
                      j Plot
EndCircle:
                      jr $ra

# swap function
swap:
                      add $t4, $a0, $0 
                      add $a0, $a1, $0
                      add $a1, $t4, $0
                      jr $ra
                      
# absolute value function
abs:           
                      addi $sp, $sp, 3 # store all the 's' registers
                      sw $s2, 0($sp)
                      sw $s1, -1($sp)
                      sw $s0, -2($sp)
                      slt $s0, $a0, $0 # set register to 1 if a0 is negative
                      addi $s1, $0, 1 
                      beq $s0, $s1, Positive # branch if a0 was negative
                      add $s2, $a0, $0
endAbs:          
                      add $v0, $s2, $0 # put value into return register
                      lw $s2, 0($sp)
                      lw $s1, -1($sp)
                      lw $s0, -2($sp)
                      addi $sp, $sp, -3
                      jr $ra
Positive: 
                      sub $s2, $0, $a0 # make negative value positive
                      j endAbs
                      
end:                add $0, $0, $0
