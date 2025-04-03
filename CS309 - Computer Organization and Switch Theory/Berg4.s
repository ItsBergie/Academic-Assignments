@ Filename: Berg4.s
@ Author:   Eli Berg
@ Email: erb0023@uah.edu
@ CS309-01 2024
@ Purpose:  Prompt the user to enter a number between 1 and 12. Reject any invalid user inputs and terminate the program.
@           From 1 to the user entered number print out the number and the product (*) of all the integers to that
@           point. This is the factorial of the number.
@           Terminate the program when all the numbers from 1 to the user entered number are printed.
@ History: 
@    Date       Purpose of change
@    ----       ----------------- 
@   Oct 29 2024 - Intial creation of file and attempt of creating program

@ Use these commands to assemble, link, run and debug this program:
@    as -o Berg4.o Berg4.s
@    gcc -o Berg4 Berg4.o
@    ./Berg4 ;echo $?
@    gdb --args ./Berg4 

.equ READERROR, 0 @Used to check for scanf read error.

.global main
main: 

prompt:
@ Prompt the user for input
    ldr r0, =prompt_msg
    bl printf

get_input:

    ldr r0, = numInputPattern
    ldr r1, =intInput

    bl  scanf 
    
    cmp r0, #READERROR             
    beq readerror          
    ldr r1, =intInput       
    ldr r1, [r1]

    cmp r1, #12 @performs r1-12.
    bgt invalidInput @should break if r1 is greater than 12.
    
    cmp r1, #1
    blt invalidInput @should break if r1 is less than 1
    
    mov r6, r1

@ Will tell the value to user
    ldr r0, = strOutputNum
    bl printf
    
    mov r5, #0
    mov r4, #0

mathLoop:
    cmp r5, r6
    bge myexit
    mul r4, r5, r4
    add r5, r5, #1

@ print indexer then sum
    mov r1, r5
    bl printf

    mov r1, r4
    bl printf

    b mathLoop

invalidInput:
    ldr r0, = isGreater
    bl printf
    bl myexit

readerror:

    ldr r0, = strInputPattern
    ldr r1, = strInputError
    bl scanf

    b prompt
myexit:
    mov r7, #0x01 //Satisfies requirement 8
    svc 0

.data
    .balign 4
    isGreater: .asciz "Invalid input, terminating.\n"

    .balign 4
    isLess: .asciz "The number is less than or equal to 12.\n"

    .balign 4
    prompt_msg: .asciz "This program will print the product of the integers from 1 to a number you enter. Please enter an integer from 1 to 12: \n"

    .balign 4
    strInputError: .skip 100*4  @ User to clear the input buffer for invalid input.

    .balign 4
    strOutputNum: .asciz "You entered %d. Below is the number and the product of the integers from 1 to n.  \n"

    .balign 4
    numInputPattern: .asciz "%d"  @ integer format for read. 

    .balign 4
    intInput: .word 0

    .balign 4
    strInputPattern: .asciz "%[^\n]" @ Used to clear the input buffer for invalid input.


@ Let the assembler know these are the C library functions. 

.global printf

.global scanf

@ End of code and end of file. Leave a blank line after this.
