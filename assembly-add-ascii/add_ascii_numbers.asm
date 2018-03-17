# File:		add_ascii_numbers.asm
# Author:	K. Reek
# Contributors:	P. White, W. Carithers
#		Connor Egbert
#
# Updates:
#		3/2004	M. Reek, named constants
#		10/2007 W. Carithers, alignment
#		09/2009 W. Carithers, separate assembly
#
# Description:	Add two ASCII numbers and store the result in ASCII.
#
# Arguments:	a0: address of parameter block.  The block consists of
#		four words that contain (in this order):
#
#			address of first input string
#			address of second input string
#			address where result should be stored
#			length of the strings and result buffer
#
#		(There is actually other data after this in the
#		parameter block, but it is not relevant to this routine.)
#
# Returns:	The result of the addition, in the buffer specified by
#		the parameter block.
#

	.globl	add_ascii_numbers

add_ascii_numbers:
A_FRAMESIZE = 40

#
# Save registers ra and s0 - s7 on the stack.
#
	addi 	$sp, $sp, -A_FRAMESIZE
	sw 	$ra, -4+A_FRAMESIZE($sp)
	sw 	$s7, 28($sp)
	sw 	$s6, 24($sp)
	sw 	$s5, 20($sp)
	sw 	$s4, 16($sp)
	sw 	$s3, 12($sp)
	sw 	$s2, 8($sp)
	sw 	$s1, 4($sp)
	sw 	$s0, 0($sp)
	
# ##### BEGIN STUDENT CODE BLOCK 1 #####

	lw $s1, 0($a0) # Get address of first string
	lw $s2, 4($a0) # Get address of second string
	lw $s3, 8($a0) # Get address of result string
	lw $s4, 12($a0) # Get length of buffers
	add $s5, $zero, $zero # Make sure overflow value is zero first iteration
	add $s6, $zero, $s4 # save buffer length for use later

	add $s1, $s1, $s4 # start from the back of the string
	add $s2, $s2, $s4 # which is really the begining of the number
	add $s3, $s3, $s4

add_loop:
	lbu $t1, 0($s1)	# Get char from first string
	lbu $t2, 0($s2)	# get char from second string

do_not_overflow:
	addu $s7, $t1, $t2

	addiu $s7, $s7, -48 # Keep result in ascii digit range
	addu $s7, $s7, $s5
	add $s5, $zero, $zero

	sltiu $t7, $s7, 58 # If result is > 9
	bne $t7, $zero, no_overflow # then add one to overflow value
	addiu $s7, $s7, -10
	addiu $s5, $zero, 1

no_overflow:
	slti $t7, $s4, 1 # If buffer size is zero 
	bne $t7, $zero, add_loop_end # then go to loop end

	beq $s6, $s4, first_loop_skip # If write in the first loop, overwrite period
	sb $s7, 0($s3)		

first_loop_skip:
	addi $s1, $s1, -1 # Increment index of first string
	addi $s2, $s2, -1 # Increment address of second string
	addi $s3, $s3, -1 # Increment address of result string
	addiu $s4, $s4, -1 # Decrease length of buffer counter
	j add_loop

add_loop_end:
	sb $s7, 0($s3) 


# ###### END STUDENT CODE BLOCK 1 ######

#
# Restore registers ra and s0 - s7 from the stack.
#
	lw 	$ra, -4+A_FRAMESIZE($sp)
	lw 	$s7, 28($sp)
	lw 	$s6, 24($sp)
	lw 	$s5, 20($sp)
	lw 	$s4, 16($sp)
	lw 	$s3, 12($sp)
	lw 	$s2, 8($sp)
	lw 	$s1, 4($sp)
	lw 	$s0, 0($sp)
	addi 	$sp, $sp, A_FRAMESIZE

	jr	$ra			# Return to the caller.
