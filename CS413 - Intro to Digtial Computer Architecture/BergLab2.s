@ Filename: BergLab2.s
@ Author:   Eli Berg
@ Email:    erb0023@uah.edu
@           CS413-02 2025
@
@ Purpose:  The purpose of this assignment is to get the student to use the stack to pass parameters to and from their 
@           own defined subroutines/functions in ARM Assembly.
@ 
@ History: 
@    Date       Purpose of change
@    ----       ----------------- 
@   11-Feb-2025  Student edited code 
@   12-Feb-2025  Student edited code and finished code
@
@ Use these commands to assemble, link, run and debug this program:
@    as -o BergLab2.o BergLab2.s
@    gcc -o BergLab2 BergLab2.o
@    ./BergLab2 ;echo $?
@    gdb --args ./BergLab2 

@ ***********************************************************************
@ The = (equal sign) is used in the ARM Assembler to get the address of a
@ label declared in the .data section. This takes the place of the ADR
@ instruction used in the textbook. 
@ ***********************************************************************

.equ READERROR, 0  @ Used to check for scanf read error. 

.global main       @ Have to use main because of C library uses. 

@*******************
main:
@*******************
    @ Welcome message
    ldr r0, =welcomeMessage
    bl printf

@*******************
get_first_number:
@*******************
    @ Prompt for the first number
    ldr r0, =instructionMessage
    bl printf
    ldr r0, =numInputPattern
    ldr r1, =intInput
    bl scanf
    cmp r0, #READERROR          @ Check if scanf failed
    beq invalid_input           @ If failed, prompt again
    ldr r1, =intInput
    ldr r5, [r1]                @ Store first number in r5
    cmp r5, #0                  @ Check if input is negative
    blt invalid_input           @ If negative, prompt again

@*******************
get_operation:
@*******************
    @ Prompt for the operation
    ldr r0, =operation
    bl printf
    ldr r0, =charPattern
    ldr r1, =charInput
    bl scanf
    cmp r0, #READERROR          @ Check if scanf failed
    beq invalid_operation       @ If failed, prompt again
    ldr r1, =charInput
    ldr r6, [r1]                @ Store operation in r6
    bl operationValid           @ Check if operation is valid
    bne invalid_operation       @ If invalid, prompt again

@*******************
get_second_number:
@*******************
    @ Prompt for the second number
    ldr r0, =instructionMessage
    bl printf
    ldr r0, =numInputPattern
    ldr r1, =intInput
    bl scanf
    cmp r0, #READERROR          @ Check if scanf failed
    beq invalid_input           @ If failed, prompt again
    ldr r1, =intInput
    ldr r7, [r1]                @ Store second number in r7
    cmp r7, #0                  @ Check if input is negative
    blt invalid_input           @ If negative, prompt again

    @ Push operands onto the stack
    push {r5, r7}

    @ Perform the operation
    cmp r6, #'a'
    beq addition
    cmp r6, #'b'
    beq subtraction
    cmp r6, #'c'
    beq multiplication
    cmp r6, #'d'
    beq division
    cmp r6, #'A'
    beq addition
    cmp r6, #'B'
    beq subtraction
    cmp r6, #'C'
    beq multiplication
    cmp r6, #'D'
    beq division

@*******************
addition:
@*******************
    pop {r1, r2}
    adds r1, r1, r2
    bvs overflow
    push {r1}
    b print_result

@*******************
subtraction:
@*******************
    pop {r1, r2}
    subs r1, r1, r2
    bvs overflow
    push {r1}
    b print_result

@*******************
multiplication:
@*******************
    pop {r1, r2}
    umull r0, r4, r1, r2
    cmp r4, #0
    bgt overflow
    push {r0}
    b print_result

@*******************
division:
@*******************
    pop {r1, r2}
    cmp r2, #0
    beq division_by_zero
    mov r3, #0                  @ Initialize quotient

@*******************
division_loop:
@*******************
    cmp r1, r2
    blt division_done
    sub r1, r1, r2
    add r3, r3, #1
    b division_loop

@*******************
division_done:
@*******************
    push {r1}                   @ Push quotient
    push {r3}                   @ Push remainder
    b print_division_result

@*******************
division_by_zero:
@*******************
    ldr r0, =divisionErrorMsg
    bl printf
    b get_second_number

@*******************
print_result:
@*******************
    pop {r1}
    ldr r0, =resultMessage
    bl printf
    b repeat

@*******************
print_division_result:
@*******************
    pop {r1}                    @ Remainder
    pop {r2}                    @ Quotient
    ldr r0, =divisionResultMsg
    bl printf
    b repeat

@*******************
invalid_input:
@*******************
    ldr r0, =invalidInputMessage
    bl printf
    b get_first_number

@*******************
invalid_operation:
@*******************
    ldr r0, =invalidOperationMessage
    bl printf
    b get_operation

@*******************
overflow:
@*******************
    ldr r0, =overflowMsg
    bl printf
    b repeat

@*******************
repeat:
@*******************
    @ Ask if the user wants to perform another calculation
    ldr r0, =continuePrompt
    bl printf
    ldr r0, =charPattern
    ldr r1, =charInput
    bl scanf
    cmp r0, #READERROR
    beq repeat
    ldr r1, =charInput
    ldr r1, [r1]
    cmp r1, #'y'
    beq main
    cmp r1, #'Y'
    beq main
    b done

@*******************
done:
@*******************
    ldr r0, =exitMessage
    bl printf
    mov r7, #0x01
    svc 0

@*******************
operationValid:
@*******************
    @ Check if the operation is valid
    cmp r6, #'a'
    beq valid
    cmp r6, #'b'
    beq valid
    cmp r6, #'c'
    beq valid
    cmp r6, #'d'
    beq valid
    cmp r6, #'A'
    beq valid
    cmp r6, #'B'
    beq valid
    cmp r6, #'C'
    beq valid
    cmp r6, #'D'
    beq valid
    b invalid_operation

@*******************
valid:
@*******************
    mov pc, lr

.data
@ Declare the strings and data needed

.balign 4
welcomeMessage: .asciz "Welcome to the four function Calculator.\n"
.balign 4
instructionMessage: .asciz "Please enter a positive integer or zero: \n"
.balign 4
invalidInputMessage: .asciz "Invalid input. Please enter a positive integer.\n"
.balign 4
invalidOperationMessage: .asciz "Invalid operation. Please enter A, B, C, or D.\n"
.balign 4
operation: .asciz "Please select what operation you want to use: A (+), B (-), C(*), D(/) (Uppercase or Lowercase)\n"
.balign 4
resultMessage: .asciz "Result: %d\n"
.balign 4
divisionResultMsg: .asciz "Quotient: %d, Remainder: %d\n"
.balign 4
continuePrompt: .asciz "Would you like to perform another operation (y/n)?\n"
.balign 4
exitMessage: .asciz "Thank you for using the four function calculator!\n"
.balign 4
overflowMsg: .asciz "Overflow occurred.\n"
.balign 4
divisionErrorMsg: .asciz "Error: Division by zero.\n"

@ Format pattern for scanf call.

.balign 4
numInputPattern: .asciz "%d"
.balign 4
charPattern: .asciz " %c"
.balign 4
intInput: .word 0
.balign 4
charInput: .asciz " "

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
