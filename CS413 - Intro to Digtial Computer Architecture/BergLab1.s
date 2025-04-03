@ Filename: BergLab1.s
@ Author:   Eli Berg
@ Email:    erb0023@uah.edu
@           CS413-02 2025
@
@ Purpose:  The objective of this lab is to have the students use the ARM Auto-Indexing to access array elements and to @	    do nested subroutine calls.
@ 
@ History: 
@    Date       Purpose of change
@    ----       ----------------- 
@   2-Feb-2025  Student edited code to complete homework assignment
@
@ Use these commands to assemble, link, run and debug this program:
@    as -o BergLab1.o BergLab1.s
@    gcc -o BergLab1 BergLab1.o
@    ./BergLab1 ;echo $?
@    gdb --args ./BergLab1 

@ ***********************************************************************
@ The = (equal sign) is used in the ARM Assembler to get the address of a
@ label declared in the .data section. This takes the place of the ADR
@ instruction used in the textbook. 
@ ***********************************************************************

.equ READERROR, 0  @ Used to check for scanf read error. 

.global main       @ Have to use main because of C library uses. 

main:

@*******************
prompt:
@*******************

@ Print out a welcome.
 
   ldr r0, =strWelcome     @ Put the address of my string into the first parameter
   bl  printf              @ Call the C printf to display input prompt. 

   mov r4, #10             @ loop counter 
   ldr r5, =array2 + 40    @ Pointer to second hald of array2 

@*******************
input:
@*******************

@ Prompt user for input

    ldr r0, =strFormat
    mov r1, r5           @ Address to store the input
    bl scanf

                         @ Auto-indexing: Increment pointer and decrement counter
    add r5, r5, #4       @ Move to the next element in array2
    subs r4, r4, #1      @ Decrement loop counter
    bne input      	 @ Repeat until counter is zero

                         @ Calculate sumarray = array1 + array2
    mov r4, #20          @ Loop counter for 20 elements
    ldr r5, =array1      @ Pointer to array1
    ldr r6, =array2      @ Pointer to array2
    ldr r7, =sumarray    @ Pointer to sumarray

@*******************
sum_loop:
@*******************

    ldr r0, [r5], #4       @ Load array1[i] and auto-increment pointer
    ldr r1, [r6], #4       @ Load array2[i] and auto-increment pointer
    add r2, r0, r1         @ sumarray[i] = array1[i] + array2[i]
    str r2, [r7], #4       @ Store result in sumarray and auto-increment pointer

    subs r4, r4, #1        @ Decrement loop counter
    bne sum_loop           @ Repeat until counter is zero

    ldr r0, =array1_msg    @ Print array1
    bl printf
    ldr r0, =array1
    bl printarray

    ldr r0, =array2_msg    @ Print array2
    bl printf
    ldr r0, =array2
    bl printarray

    ldr r0, =sumarray_msg  @ Print array3
    bl printf
    ldr r0, =sumarray
    bl printarray

    @ Exit program
    mov r7, #1             @ syscall: exit
    svc 0

@*******************
printarray:
@*******************
    @ Subroutine: Printarray
    @ Input: r0 = starting address of the array
    @ Prints all elements of the array

    push {r4, r5, lr}    @ Save registers
    mov r4, r0           @ Save array pointer
    mov r5, #20          @ Loop counter for 20 elements

@*******************
print_loop:
@*******************
    ldr r0, =strFormat   @ Load format string for printf
    ldr r1, [r4], #4     @ Load array element and auto-increment pointer
    bl printf            @ Print the element

    subs r5, r5, #1      @ Decrement loop counter
    bne print_loop       @ Repeat until counter is zero

    ldr r0, =newline     @ Prints new line just for visual appeal
    bl printf

    pop {r4, r5, lr}     @ Restore registers
    bx lr                @ Return to caller

.data

@ Declare the strings and data needed

.balign 4
strWelcome: .asciz "Please enter 10 integers (After each integer press Enter).\n"
.balign 4
array1_msg:  .asciz "Array 1:"
.balign 4
array2_msg:  .asciz "Array 2:"
.balign 4
sumarray_msg: .asciz "Array 3:"
.balign 4
newline: .asciz "\n"  @newline to add between each array output


@ Format pattern for scanf call.

.balign 4
strFormat: .asciz "%d,"  @ Format string for scanf/printf and comma for visual.

@ Arrays (20 elements each)

array1:      .word -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
array2:      .word -5, -4, -3, -2, -1, 0, 5, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  	@ First half initialized
sumarray:    .space 80  @ 20 elements * 4 bytes each

@ Let the assembler know these are the C library functions. 

.global printf
@  To use printf:
@     r0 - Contains the starting address of the string to be printed. The string
@          must conform to the C coding standards.
@     r1 - If the string contains an output parameter i.e., %d, %c, etc. register
@          r1 must contain the value to be printed. 
@ When the call returns registers: r0, r1, r2, r3 and r12 are changed. 

.global scanf
@  To use scanf:
@      r0 - Contains the address of the input format string used to read the user
@           input value. In this example it is numInputPattern.  
@      r1 - Must contain the address where the input value is going to be stored.
@           In this example memory location intInput declared in the .data section
@           is being used.  
@ When the call returns registers: r0, r1, r2, r3 and r12 are changed.
@ Important Notes about scanf:
@   If the user entered an input that does NOT conform to the input pattern, 
@   then register r0 will contain a 0. If it is a valid format
@   then r0 will contain a 1. The input buffer will NOT be cleared of the invalid
@   input so that needs to be cleared out before attempting anything else.
@
@ Additional notes about scanf and the input patterns:
@    1. If the pattern is %s or %c it is not possible for the user input to generate
@       and error code. Anything that can be typed by the user on the keyboard
@       will be accepted by these two input patterns. 
@    2. If the pattern is %d and the user input 12.123 scanf will accept the 12 as
@       valid input and leave the .123 in the input buffer. 
@    3. If the pattern is "%c" any white space characters are left in the input
@       buffer. In most cases user entered carrage return remains in the input buffer
@       and if you do another scanf with "%c" the carrage return will be returned. 
@       To ignore these "white" characters use " $c" as the input pattern. This will
@       ignore any of these non-printing characters the user may have entered.
@

@ End of code and end of file. Leave a blank line after this.
