@ Filename: Berg2.s
@ Author:   Eli Berg
@ CS309-02
@ Purpose:  Show CS309 and CS413 students how to read user inputs from KB. 
@ History: 
@    Date       Purpose of change
@    ----       ----------------- 
@   Oct 5 2024 - Creating, commenting, and finished program
@
@ Use these commands to assemble, link, run and debug this program:
@    as -o Berg2.o Berg2.s
@    gcc -o Berg2 Berg2.o
@    ./Berg2 ;echo $?
@    gdb --args ./Berg2 

.equ READERROR, 0 @ Used to check for scanf read error.

.global main @ Have to use main because of C library uses. 

main:

prompt:

@ Part 1: Ask the user to enter a number.
 
   ldr r0, =strInputPrompt @ Put the address of my string into the first parameter.
   bl  printf              @ Call the C printf to display input prompt.

get_input:
   ldr r0, =numInputPattern @ Setup to read in one number.
   ldr r1, =intInput        @ Load r1 with the address of where the input value will be stored.
   bl  scanf                @ Scan the keyboard.
   cmp r0, #READERROR       @ Check for a read error.
   beq readerror            @ If there was a read error, go handle it.
   ldr r1, =intInput        @ Have to reload r1 because it gets wiped out. 
   ldr r1, [r1]             @ Read the contents of intInput and store in r1 so that it can be printed.

@ Part 2: Print the input out as a number.

   ldr r0, =strOutputNum    @ Load the string for number output
   bl  printf               @ Print the number value

@ Part 3: Ask the user to enter a character.

   ldr r0, =strInputCharPrompt @ Load the prompt for character input.
   bl  printf                   @ Print the character input prompt.

get_char_input:
   ldr r0, =charInputPattern  @ Load the format for character input.
   ldr r1, =charInput         @ Load r1 with the address of where the character input will be stored.
   bl  scanf                  @ Scan the keyboard for character input.
   ldr r1, =charInput         @ Reload r1 because it gets wiped out.
   ldrb r1, [r1]              @ Read the character input and store it in r1.

@ Part 4: Print the input character back to the screen.

   ldr r0, =strOutputChar     @ Load the string for character output.
   bl  printf                 @ Print the character value.
   b   myexit                 @ Exit the program.

@***********
readerror:
@***********

   ldr r0, =strInputPattern     @ Load the input pattern to clear the buffer.
   ldr r1, =strInputError       @ Load the error buffer to clear.
   bl  scanf                    @ Scan the keyboard again.

   b   prompt                   @ Return to the main prompt.

@*******************
myexit:
@*******************
@ End of the code. Force exit and return control to OS

   mov r7, #0x01 @ SVC call to exit
   svc 0         @ Make the system call.

.data

@ Declare the strings and data needed

.balign 4
strInputPrompt: .asciz "Input the number: \n"

.balign 4
strOutputNum: .asciz "The number value is: %d \n"

.balign 4
strInputCharPrompt: .asciz "Input a character: \n"

.balign 4
strOutputChar: .asciz "The character entered is: %c \n"

@ Format patterns for scanf calls.

.balign 4
numInputPattern: .asciz "%d"  @ integer format for read.

.balign 4
charInputPattern: .asciz " %c" @ character format for read, leading space to ignore newline.

.balign 4
strInputPattern: .asciz "%[^\n]" @ Used to clear the input buffer for invalid input.

.balign 4
strInputError: .skip 100*4  @ Used to clear the input buffer for invalid input.

.balign 4
intInput: .word 0           @ Location used to store the user input.

.balign 4
charInput: .byte 0          @ Location used to store the user character input.

@ Let the assembler know these are the C library functions.

.global printf
.global scanf

@end of code and end of file. Leave a blank line after this.
