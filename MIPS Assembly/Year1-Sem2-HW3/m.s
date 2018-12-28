# Title: Assignment 6     Filename: m.s
# Author: Tamir Hazut 	 ID: 313521965
# Date: 10.06.2018

################# Data segment #####################
.data
ARRAY: .word 0:30
ARRAY_FOR_SORT: .word 0:30
jTABLE: .word add_number,REPLACE,DEL,find,average,max,print_array,sort,EXIT,default
NUM: .word 0
ARRAY_IS_EMPTY_STRING: .asciiz "\nThe array is empty.\n"
ARRAY_IS_FULL_STRING: .asciiz "\nThe array is full.\n"
AVERAGE_IS_STRING: .asciiz "\nAverage is: "
MENU_STRING: .asciiz "\nThe options are:\n1. Enter a number (base 10)\n2. Replace a number (base 10)\n3. DEL a number (base 10)\n4. Find a number in the array (base 10)\n5. Find average (base 2-10)\n6. Find Max (base 2-10)\n7. Print the array elements (base 2-10)\n8. Print sort array (base 2-10)\n9. END\n\n"
NUMBER_ADDED_STRING: .asciiz "\nNumber added successfully.\n"
NUMBER_DELETED_STRING: .asciiz "\nNumber deleted successfully.\n"
NUMBER_IS_IN_ARRAY_STRING: .asciiz "\nNumber is in the array in index: "
NUMBER_NOT_FOUND_IN_ARRAY_STRING: .asciiz "\nNumber is not in the array\n"
NUMBER_REPLACED_STRING: .asciiz "\nNumber replaced successfully.\n"
MAX_NUM_IS_1_STRING: .asciiz "\nMax number is: "
MAX_NUM_IS_2_STRING: .asciiz " ,In index: "
THE_ARRAY_IS_STRING: .asciiz "\nThe array is: "
WHAT_BASE_TO_PRINT_STRING: .asciiz "\nWhat base would you like to print?\n"
WHAT_NUM_TO_ADD_STRING: .asciiz "\nWhat number to add?\n"
WHAT_NUM_TO_DEL_STRING: .asciiz "\nWhat number to delete?\n"
WHAT_NUM_TO_FIND_STRING: .asciiz "\nWhat number to find?\n"
WHAT_NUM_TO_REPLACE_1_STRING: .asciiz "\nWhat number to replace?\n"
WHAT_NUM_TO_REPLACE_2_STRING: .asciiz "\nReplace the number "
WHAT_NUM_TO_REPLACE_3_STRING: .asciiz " (in index "
WHAT_NUM_TO_REPLACE_4_STRING: .asciiz ") with what number?\n"




################# Code segment #####################
.text
.globl main
main:	# Main program entry
la $a1, NUM
la $a2, ARRAY
la $a3, ARRAY_FOR_SORT
menu:
	# Print menu
	la $a0, MENU_STRING 
	li $v0, 4
	syscall

	# Get user's choice
	li $v0, 5
	syscall
	
	addi $v0,$v0,-1
	move $s0,$v0 	   # Get index in $s0
	sll $s0,$s0,2       # $s0=index*4
	lw  $s0,jTABLE($s0) # Load label to jump from jump table
	jalr $s0
	
default:
	j menu
	
EXIT:
	li $v0, 10	# Exit program
	syscall

############ Procedures #############
add_number:
	lw $t0, ($a1) # Number of integers in the array
	beq $t0, 30, ARRAY_IS_FULL # Checks if the array is full
	sw $a1, ($sp) # Push $a1 to stack
	move $a1, $t0 # Number of integers in the array to $a1
	
	# Print WHAT_NUM_TO_ADD_STRING String
	la $a0,WHAT_NUM_TO_ADD_STRING
	li $v0, 4
	syscall
	
	# Gets a integer number to add the array
	li $v0,5
	syscall
	
	move $t1,$v0 # Backup the integer to $t1
	beq $a1,$0,add_number_to_array # Check if the array is empty
	la $t2,CHECK # Load CHECK address to $t2
	addiu $sp, $sp, -4
	sw $ra, ($sp) # jump and link to address in $ra(=CHECK)
	jalr $t2 # jump and link to address in $t2(=CHECK)
	lw $ra,($sp) # Restore backuped return address to $ra
	addiu $sp, $sp, 4
	bne $v0,-1,NUMBER_IS_IN_THE_ARRAY # Integer is in the array already
	
	add_number_to_array:
		mul $t3,$t0,4 # Word(=4 Bytes) number in the array.
		add $t2,$t3,$a2
		sw $t1,($t2) # Store the integer the user enter to the place in the ARRAY
		addi $t0,$t0,1 # (Number of objects in array)++
		
		lw $a1, ($sp) # Restore NUM address to $a1
		sw $t0,($a1) # Store the number of object in the array at NUM address
		
		li $v0,4
		la $a0, NUMBER_ADDED_STRING
		syscall
		jr $ra
		
REPLACE:
	lw $t0, ($a1) # Number of integers in the array
	beq $t0,  0, ARRAY_IS_EMPTY # Check if the array is empty
	sw $a1, ($sp) # Push $a1 to stack
	move $a1, $t0 # Number of integers in the array to $a1
		
	# Print WHAT_NUM_TO_REPLACE_1_STRING String
	la $a0,WHAT_NUM_TO_REPLACE_1_STRING
	li $v0, 4
	syscall
	
	# Gets a integer number to replace the array
	li $v0,5
	syscall

	move $t1,$v0 # Backup the integer to $t1
	la $t2,CHECK # Load CHECK address to $t2
	addiu $sp, $sp, -4
	sw $ra, ($sp) # jump and link to address in $ra(=CHECK)
	jalr $t2 # jump and link to address in $t2(=CHECK)
	lw $ra,($sp) # Restore backuped return address to $ra
	addiu $sp, $sp, 4
	lw $a1, ($sp) # Restore NUM address to $a1
	sw $t0,($a1) # Store the number of object in the array at NUM address
	beq $v0,-1,NUMBER_IS_NOT_IN_THE_ARRAY # Integer is not in the array already
	move $t3,$v0 # Backup index found to $t3
	
	# Print WHAT_NUM_TO_REPLACE_2-4_STRING String
	li $v0,4
	la $a0, WHAT_NUM_TO_REPLACE_2_STRING
	syscall
	li $v0,1
	move $a0,$t1
	syscall
	li $v0,4
	la $a0, WHAT_NUM_TO_REPLACE_3_STRING
	syscall
	li $v0,1
	move $a0,$t3
	syscall
	li $v0,4
	la $a0, WHAT_NUM_TO_REPLACE_4_STRING
	syscall
	
	# Gets a integer number to replace with the old one found the array
	li $v0,5
	syscall
	
	move $t4,$v0 # Backup the vaule of the new integer to $t3
	
	sw $a1, ($sp) # Push $a1 to stack
	move $a1, $t0 # Number of integers in the array to $a1
	addiu $sp, $sp, -4
	
	sw $ra, ($sp) # jump and link to address in $ra(=CHECK)
	jalr $t2 # jump and link to address in $t2(=CHECK)
	lw $ra,($sp) # Restore backuped return address to $ra
	addiu $sp, $sp, 4
	
	lw $a1, ($sp) # Restore NUM address to $a1
	sw $t0,($a1) # Store the number of object in the array at NUM address
	
	bne $v0,-1,NUMBER_IS_IN_THE_ARRAY # New number is already in the ARRAY
	
	mul $t3,$t3,4
	add $t3,$a2,$t3 # Set the address of the value found in the array to $t3
	sw $t4,($t3) # Replace the old value in the array with the new one in $t4
	
	# Print NUMBER_REPLACED_STRING String
	li $v0,4
	la $a0,NUMBER_REPLACED_STRING
	syscall
	
	jr $ra

DEL:
	lw $t0, ($a1) # Number of integers in the array
	beq $t0, 0, ARRAY_IS_EMPTY # Check if the array is empty
	sw $a1, ($sp) # Push $a1 to stack
	move $a1, $t0 # Number of integers in the array to $a1
	
	# Print WHAT_NUM_TO_DEL_STRING String
	la $a0,WHAT_NUM_TO_DEL_STRING
	li $v0, 4
	syscall
	
	# Gets a integer number to add the array
	li $v0,5
	syscall
	
	move $t1,$v0 # Backup the integer to $t1
	la $t2,CHECK # Load CHECK address to $t2
	addiu $sp, $sp, -4
	sw $ra, ($sp) # jump and link to address in $ra(=CHECK)
	jalr $t2 # jump and link to address in $t2(=CHECK)
	lw $ra,($sp) # Restore backuped return address to $ra
	addiu $sp, $sp, 4
	lw $a1, ($sp) # Restore NUM address to $a1
	sw $t0,($a1) # Store the number of object in the array at NUM address
	beq $v0,-1,NUMBER_IS_NOT_IN_THE_ARRAY # Integer is not in the array already
	
	# Calc address of integer to be deleted
	mul $t3,$v0,4
	add $t4,$t3,$a2
	addi $t5,$t0,-1 # Last index in the array
	beq $v0,$t5,delete_without_reduction # Checks if the number found is the last one in the array

	la $t2,REDUCTION # Load CHECK address to $t2
	sw $ra, ($sp) # jump and link to address in $ra(=CHECK)
	addiu $sp, $sp, -4
	jalr $t2 # jump and link to address in $t2(=CHECK)
	lw $ra, ($sp) # Restore backuped return address to $ra
	j continue_delete
	
	delete_without_reduction:
		sw $0, ($t4) # Store the integer the user enter to the place in the ARRAY
		
	continue_delete:
		addi $t0, $t0, -1 # (Number of objects in array)--
		sw $t0, ($a1) # Store the number of object in the array at NUM address
		li $v0,4
		la $a0, NUMBER_DELETED_STRING
		syscall
	jr $ra

find:
	lw $t0, ($a1) # Number of integers in the array
	beq $t0, 0, ARRAY_IS_EMPTY # Check if the array is empty
	sw $a1, ($sp) # Push $a1 to stack
	move $a1, $t0 # Number of integers in the array to $a1
	
	# Print WHAT_NUM_TO_FIND_STRING String
	la $a0,WHAT_NUM_TO_FIND_STRING
	li $v0, 4
	syscall
	
	# Gets a integer number to add the array
	li $v0,5
	syscall
	
	move $t1,$v0 # Backup the integer to $t1
	la $t2,CHECK # Load CHECK address to $t2
	addiu $sp, $sp, -4
	sw $ra, ($sp) # jump and link to address in $ra(=CHECK)
	jalr $t2 # jump and link to address in $t2(=CHECK)
	lw $ra,($sp) # Restore backuped return address to $ra
	addiu $sp, $sp, 4
	lw $a1, ($sp) # Restore NUM address to $a1
	sw $t0,($a1) # Store the number of object in the array at NUM address
	beq $v0,-1,NUMBER_IS_NOT_IN_THE_ARRAY # Integer is not in the array already
	

	la $t2,NUMBER_IS_IN_THE_ARRAY # Load CHECK address to $t0
	sw $ra, ($sp) # jump and link to address in $ra(=CHECK)
	jalr $t2 # jump and link to address in $t2(=CHECK)
	lw $ra,($sp) # Restore backuped return address to $ra
	
	jr $ra

average:
	lw $t0, ($a1) # Number of integers in the array
	beq $t0, 0, ARRAY_IS_EMPTY # Check if the array is empty
	sw $a1, ($sp) # Push $a1 to stack
	addiu $sp, $sp, -4
	move $a1, $t0 # Number of integers in the array to $a1
	
	move $t0,$a2
	li $t1,0 # Loop Counter
	li $t2,0 # Sum of the integers
	average_add_loop:
		lw $t3,($t0) # Load integers from ARRAY
		add $t2,$t2,$t3 # Sum all integers from ARRAY
		addi $t0,$t0,4
		addi $t1,$t1,1
		blt $t1,$a1,average_add_loop
		
	sw $a1, ($sp) # Push $a1 to stack
	addiu $sp, $sp, -4
	sw $a2, ($sp) # Push $a2 to stack
	addiu $sp, $sp, -4
	div $a1,$t2,$a1
	
	# Print WHAT_BASE_TO_PRINT String
	li $v0,4
	la $a0,WHAT_BASE_TO_PRINT_STRING
	syscall
	
	# Gets a integer number to set base for printing integers
	li $v0,5
	syscall
	
	blt $v0,2,return_from_average # Check if the base is less than 2
	bgt $v0,10,return_from_average # Check if the base is more than 10
	move $a2,$v0 # Set $a2 to what base to print
	sw $ra, ($sp) # Push $a1 to stack
	
	# Print AVERAGE_IS_STRING String 
	li $v0,4
	la $a0,AVERAGE_IS_STRING
	syscall
	
	la $t0, print_num
	jalr $t0
	lw $ra, ($sp)
	addiu $sp, $sp, 4
	lw $a2, ($sp)
	addiu $sp, $sp, 4
	lw $a1, ($sp)
	addiu $sp, $sp, 4
	return_from_average:
		jr $ra

max:
	lw $t0, ($a1) # Number of integers in the array
	beq $t0, 0, ARRAY_IS_EMPTY # Check if the array is empty
	sw $a1, ($sp) # Push $a1 to stack
	addiu $sp, $sp, -4
	move $a1, $t0 # Number of integers in the array to $a1
	
	move $t0,$a2
	li $t1,1 # Loop Counter
	lw $t2,($t0) # Current max num
	li $t3,0 # Current max num index
	max_loop:
		lw $t4,4($t0) # Num from ARRAY to check
		bgt $t2,$t4,skip_swap
		move $t2,$t4 # Change to the new max num
		move $t3,$t1 # Change to the new max num index
		skip_swap:
			addi $t1,$t1,1
			addi $t0,$t0,4
			blt $t1,$a1,max_loop
			
	sw $a2, ($sp) # Push $a2 to stack
	addiu $sp, $sp, -4
	move $a1,$t2
	
	# Print WHAT_BASE_TO_PRINT String
	li $v0,4
	la $a0,WHAT_BASE_TO_PRINT_STRING
	syscall
	
	# Gets a integer number to set base for printing integers
	li $v0,5
	syscall
	
	blt $v0,2,return_from_max # Check if the base is less than 2
	bgt $v0,10,return_from_max # Check if the base is more than 10
	move $a2,$v0 # Set $a2 to what base to print
	sw $ra, ($sp) # Backup $ra to STACK
	
	# Print MAX_NUM_IS_1_STRING String 
	li $v0,4
	la $a0,MAX_NUM_IS_1_STRING
	syscall
	
	la $t0, print_num
	jalr $t0
	
	# Print MAX_NUM_IS_1_STRING String 
	li $v0,4
	la $a0,MAX_NUM_IS_2_STRING
	syscall
	
	# Print max num index in ARRAY
	li $v0,1
	move $a0,$t3
	syscall
	
	lw $ra, ($sp)
	addiu $sp, $sp, 4
	lw $a2, ($sp)
	addiu $sp, $sp, 4
	lw $a1, ($sp)
	return_from_max:
		jr $ra

print_array:
	lw $t0, ($a1) # Number of integers in the array
	beq $t0, 0, ARRAY_IS_EMPTY # Check if the array is empty
	sw $a1, ($sp) # Push $a1 to stack
	addiu $sp, $sp, -4
	move $a1, $t0 # Number of integers in the array to $a
	move $t1, $a2 # Move the address of $a2 to $t1 for procedure use
	sw $a2, ($sp)# Push $a2 to stack
	addiu $sp, $sp, -4

	
	# Print WHAT_BASE_TO_PRINT String
	li $v0,4
	la $a0,WHAT_BASE_TO_PRINT_STRING
	syscall
	
	# Gets a integer number to set base for printing integers
	li $v0,5
	syscall
	
	blt $v0,2,return_from_print_array # Check if the base is less than 2
	bgt $v0,10,return_from_print_array # Check if the base is more than 10
	move $a2,$v0 # Set $a2 to what base to print
	sw $ra, ($sp) # Push $ra to stack
	li $t2,0 #loop counter
	la $t3, print_num
	li $v0,4
	la $a0,THE_ARRAY_IS_STRING
	syscall
	print_array_loop:
		lw $a1 ($t1) # Load the integer
		jalr $t3
		addi $t1,$t1,4
		addi $t2,$t2,1
		li $v0,11
		la $a0, ' '
		syscall
		bne $t2,$t0,print_array_loop
	lw $ra, ($sp)
	addiu $sp, $sp, 4
	lw $a2, ($sp)
	addiu $sp, $sp, 4
	lw $a1, ($sp)
	return_from_print_array:
		jr $ra

sort:
jr $ra

	
ARRAY_IS_EMPTY:
	# Print ARRAY_IS_EMPTY_STRING String
	li $v0,4
	la $a0,ARRAY_IS_EMPTY_STRING
	syscall
	jr $ra
	
ARRAY_IS_FULL:
	# Print ARRAY_IS_FULL_STRING String
	li $v0, 4
	la $a0,ARRAY_IS_FULL_STRING
	syscall
	jr $ra

CHECK:
	move $t7,$v0 # Backup the integer needed to be checked to $t7
	li $v0,0
	move $t8,$a2
	check_loop:
		lw $t9,($t8) # Load integers from ARRAY by index $v0
		beq $t7,$t9,return_from_check # Check if the number is already in ARRAY
		addi $v0,$v0,1
		addi $t8,$t8,4 
		blt $v0,$a1,check_loop
		li $v0,-1 # Number is not in ARRAY
	return_from_check:
		jr $ra
		
NUMBER_IS_IN_THE_ARRAY:	
	move $t9, $v0 # Backup index value
	# Print NUMBER_IS_IN_ARRAY String + number index
	li $v0,4
	la $a0,NUMBER_IS_IN_ARRAY_STRING
	syscall
	move $a0,$t9
	li $v0,1
	syscall
	jr $ra

NUMBER_IS_NOT_IN_THE_ARRAY:
	# Print NUMBER_NOT_FOUND_IN_ARRAY_STRING String
	la $a0,NUMBER_NOT_FOUND_IN_ARRAY_STRING
	li $v0, 4
	syscall
	jr $ra
	
print_num:
	li $t8,0 # Number of items in the stack
	bgt $a1,$0,not_negative
	abs $a1,$a1
	li $v0,11
	la $a0, '-'
	syscall
	not_negative:
		li $v0,1
	switch_base:
		div $a1,$a2 # Divide $a1 by $a2
		mflo $a1 # Set the result of the division to $a1
		mfhi $t9 # Set the remainder to $t0
		addiu $sp,$sp,-4
		sw $t9,($sp) # Push $t1 to stack
		addi $t8,$t8,1
		bne $a1,$0,switch_base
	print_after_switch_base:
		lw $a0, ($sp) # Pop from stack to $a0
		addiu $sp,$sp,4
		syscall
		addi $t8,$t8,-1
		bne $t8,$0,print_after_switch_base
	jr $ra
	
REDUCTION:
	sw $a1, ($sp)
	lw $a1, ($a1)
	REDUCTION_LOOP:
		lw $t9, 4($t8) # Load the integer from index +1 to the one being deleted in the array
		sw $t9 ($t8) # Store the integer -1 from its original index
		addi $t8,$t8,4 
		addi $v0,$v0,1
		blt $v0,$a1,REDUCTION_LOOP
	lw $a1, ($sp)
	addiu $sp, $sp, 4
	jr $ra
