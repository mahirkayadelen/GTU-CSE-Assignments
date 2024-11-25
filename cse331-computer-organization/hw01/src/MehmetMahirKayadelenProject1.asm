.data
    charArray:  .space 40001   # Assuming a maximum size of 100 (adjust as needed)
    newline:    .asciiz "\n"
    input_size_prompt:      .asciiz "Enter the size of the grid (format: rows columns): "
    input_grid_prompt:      .asciiz "Enter the initial state of the grid (format: row1col1,row1col2,row2col1...): "

.text

main:
    li $v0, 4
    la $a0, input_size_prompt # asks the user for row and column of grid
    syscall

    # Get array dimensions from the user
    li $v0, 5            # System call code for read_int
    syscall
    move $t4, $v0        # $t4 holds the number of rows

    li $v0, 5            # System call code for read_int
    syscall
    move $t5, $v0        # $t5 holds the number of columns

    # Check if the array size is within bounds
    blt $t4, 1, exit      # Exit if the number of rows is less than 1
    blt $t5, 1, exit      # Exit if the number of columns is less than 1
    bgt $t4, 10, exit     # Exit if the number of rows is greater than 10
    bgt $t5, 10, exit     # Exit if the number of columns is greater than 10

    # Fill the 2D array with characters
    la $t0, charArray    # $t0 holds the base address of the array

    # Call fill_loop function
    jal fill_loop
    
    #Call print_array function
    jal print_array
    
    # Call modify_array function
    jal modify_array

    # Call print_array function to print the modified array
    jal print_array
    
    # find 'O' if there is 'o' in neighbors =>  'O' to '.'
    jal update_array
    
    # Call replace_o_with_dot function
    jal replace_o_with_dot

    # Call print_array function
    jal print_array

exit:
    li $v0, 10            # System call code for exit
    syscall
        	
# Function to fill the 2D array with characters
fill_loop:
    # Argument: $t4 = number of rows, $t5 = number of columns
    # Result: Array filled with characters
    la $t0, charArray    # $t0 holds the base address of the array
    li $t1, 0            # $t1 holds the row index
    li $t2, 0            # $t2 holds the column index

fill_row_loop:
    bge $t1, $t4, return_to_caller   # Exit if all rows are processed

    # Calculate the index in the 1D array (index = row * number_of_columns + column)
    mul $t3, $t1, $t5   # Multiply the row index by the number of columns
    add $t3, $t3, $t2   # Add the column index to get the total index
    add $t3, $t3, $t0   # Add the base address of the array

    # Prompt user for input character
    li $v0, 12           # System call code for read_char
    syscall
    sb $v0, 0($t3)       # Store the character in the array

    addi $t2, $t2, 1     # Increment the column index

    # Check if we've reached the end of the current row
    bge $t2, $t5, fill_next_row

    j fill_row_loop

fill_next_row:
    li $t2, 0            # Reset the column index
    addi $t1, $t1, 1      # Increment the row index
    j fill_row_loop

print_array:
    # print newline
    li $v0, 4
    la $a0, newline
    syscall
    
    # Print the filled array
    la $t0, charArray    # $t0 holds the base address of the array
    li $t1, 0            # $t1 holds the row index
    li $t2, 0            # $t2 holds the column index

    outer_loop:
        bge $t1, $t5, return_to_caller

        li $t2, 0            # $t2 holds the column index

    inner_loop:
        bge $t2, $t4, print_next_row # Go to the next row if all columns are processed

        # Calculate the index in the 1D array (index = row * number_of_columns + column)
        mul $t3, $t1, $t5   # Multiply the row index by the number of columns
        add $t3, $t3, $t2   # Add the column index to get the total index
        add $t3, $t3, $t0   # Add the base address of the array

        lb $a0, 0($t3)      # Load the character at the calculated index

        # Check if the character is 'o' and replace it with 'O' for printing
        li $t6, 111          # ASCII code for 'o'
        beq $a0, $t6, print_O
        j print_char

    print_O:
        li $a0, 79           # ASCII code for 'O'
        j print_char

    print_char:
        # Print the character
        li $v0, 11           # System call code for print_char
        syscall

        addi $t2, $t2, 1    # Increment the column index
        j inner_loop

    print_next_row:
        li $v0, 11           # System call code for print_char
        li $a0, 10           # Print a newline character
        syscall

        addi $t1, $t1, 1     # Increment the row index
        j outer_loop
        
        
        
        # Function to modify the characters in the array
modify_array:
    # Argument: $t4 = number of rows, $t5 = number of columns
    # Result: Array modified according to the specified rules
    la $t0, charArray    # $t0 holds the base address of the array
    li $t1, 0            # $t1 holds the row index
    li $t2, 0            # $t2 holds the column index

modify_row_loop:
    bge $t1, $t4, return_to_caller   # Exit if all rows are processed

    li $t2, 0            # $t2 holds the column index

modify_col_loop:
    bge $t2, $t5, modify_next_row # Go to the next row if all columns are processed

    # Calculate the index in the 1D array (index = row * number_of_columns + column)
    mul $t3, $t1, $t5   # Multiply the row index by the number of columns
    add $t3, $t3, $t2   # Add the column index to get the total index
    add $t3, $t3, $t0   # Add the base address of the array

    lb $a0, 0($t3)      # Load the character at the calculated index

    # Compare the character with 'O' and '.'
    li $t6, 'O'
    li $t7, '.'
    beq $a0, $t6, replace_o
    beq $a0, $t7, replace_dot
    j continue_modify

replace_o:
    # Replace 'O' with 'o'
    li $a0, 'o'
    sb $a0, 0($t3)      # Store the modified character in the array
    j continue_modify

replace_dot:
    # Replace '.' with 'O'
    li $a0, 'O'
    sb $a0, 0($t3)      # Store the modified character in the array

continue_modify:
    addi $t2, $t2, 1    # Increment the column index
    j modify_col_loop

modify_next_row:
    addi $t1, $t1, 1     # Increment the row index
    j modify_row_loop


####
# Function to update the array based on 'O' characters and their surroundings
update_array:
    # Arguments: $t4 = number of rows, $t5 = number of columns
    # Result: Array updated with '.' characters around 'O'

    la $t0, charArray    # $t0 holds the base address of the array
    li $t1, 0            # $t1 holds the row index

update_row_loop:
    bge $t1, $t4, return_to_caller   # Exit if all rows are processed

    li $t2, 0            # $t2 holds the column index

update_column_loop:
    bge $t2, $t5, update_next_row   # Go to the next row if all columns are processed

    # Calculate the index in the 1D array (index = row * number_of_columns + column)
    mul $t3, $t1, $t5   # Multiply the row index by the number of columns
    add $t3, $t3, $t2   # Add the column index to get the total index
    add $t3, $t3, $t0   # Add the base address of the array

    lb $a0, 0($t3)      # Load the character at the calculated index

    # Check if the character is 'O'
    li $t6, 'O'
    beq $a0, $t6, check_neighbors

    j update_next_column

check_neighbors:
    sub $t7, $t1, 1     # Calculate the row above
    sub $t8, $t2, 1     # Calculate the column to the left
    add $t9, $t1, 1     # Calculate the row below
    add $s0, $t2, 1     # Calculate the column to the right

    # Calculate the indices for neighboring elements
    mul $s1, $t7, $t5  # Index for the element above
    add $s1, $s1, $t2
    add $s1, $s1, $t0

    mul $s2, $t1, $t5  # Index for the element to the left
    sub $s2, $s2, 1
    add $s2, $s2, $t0

    mul $s3, $t9, $t5  # Index for the element below
    add $s3, $s3, $t2
    add $s3, $s3, $t0

    mul $s4, $t1, $t5  # Index for the element to the right
    add $s4, $s4, 1
    add $s4, $s4, $t0

    # Load neighbors
    lb $s1, 0($s1)    # Load the character above
    lb $s2, 0($s2)    # Load the character to the left
    lb $s3, 0($s3)    # Load the character below
    lb $s4, 0($s4)    # Load the character to the right

    # Check if any neighbor is 'o'
    li $t6, 'o'
    beq $s1, $t6, update_character
    beq $s2, $t6, update_character
    beq $s3, $t6, update_character
    beq $s4, $t6, update_character

    j update_next_column

update_character:
    # Update the central 'O' with '.'
    li $t6, '.'        # Load the ASCII code for '.'
    sb $t6, 0($t3)

update_next_column:
    addi $t2, $t2, 1    # Increment the column index
    j update_column_loop

update_next_row:
    addi $t1, $t1, 1    # Increment the row index
    j update_row_loop



# Function to replace 'o' with '.'
replace_o_with_dot:
    # Arguments: $t4 = number of rows, $t5 = number of columns
    # Result: 'o' replaced with '.' in the array
    la $t0, charArray    # $t0 holds the base address of the array
    li $t1, 0            # $t1 holds the row index
    li $t2, 0            # $t2 holds the column index

replace_row_loop:
    bge $t1, $t4, return_to_caller   # Exit if all rows are processed

replace_col_loop:
    bge $t2, $t5, replace_next_row   # Go to the next row if all columns are processed

    # Calculate the index in the 1D array (index = row * number_of_columns + column)
    mul $t3, $t1, $t5   # Multiply the row index by the number of columns
    add $t3, $t3, $t2   # Add the column index to get the total index
    add $t3, $t3, $t0   # Add the base address of the array

    lb $t6, 0($t3)      # Load the character at the calculated index
    li $t7, 111         # ASCII code for 'o'

    # Check if the character is 'o'
    beq $t6, $t7, replace_with_dot

    j not_replace_with_dot

replace_with_dot:
    # Replace 'o' with '.'
    li $t6, 46          # ASCII code for '.'
    sb $t6, 0($t3)      # Store the new character in the array

not_replace_with_dot:
    addi $t2, $t2, 1    # Increment the column index
    j replace_col_loop

replace_next_row:
    li $t2, 0            # Reset the column index
    addi $t1, $t1, 1      # Increment the row index
    j replace_row_loop

return_to_caller:
    jr $ra               # Return to the calling function
