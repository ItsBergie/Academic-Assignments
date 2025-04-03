@ Filename: BergLab3.s
@ Author:   Eli Berg
@ Email:    erb0023@uah.edu
@           CS413-02 2025
@
@ Purpose:  Simulates the operation of a Keurig-style coffee machine.
@
@ History:
@    Date       Purpose of change
@    ----       -----------------
@   3-March-2025  Student created outline for code 
@   4-March-2025  Student implemented code and test
@   5-March-2025  Student bug fixed code according to Proffesors input and finished code
@
@ Use these commands to assemble, link, run and debug this program:
@    as -o BergLab3.o BergLab3.s
@    gcc -o BergLab3 BergLab3.o
@    ./BergLab3 ;echo $?
@    gdb --args ./BergLab3 

@ ***********************************************************************
@ The = (equal sign) is used in the ARM Assembler to get the address of a
@ label declared in the .data section. This takes the place of the ADR
@ instruction used in the textbook. 
@ ***********************************************************************

.equ READERROR, 0

.global main

@*******************
main:
@*******************
    mov r5, #48               @ Initialize water level to 48 oz
    mov r6, #0                @ Initialize small cup count to 0
    mov r7, #0                @ Initialize medium cup count to 0
    mov r8, #0                @ Initialize large cup count to 0

    ldr r0, =welcomeMessage   @ Load address of welcome message
    bl printf                 @ Print welcome message

@*******************
menu:
@*******************
    ldr r0, =insertMessage  @ Load address of insert cup message
    bl printf               @ Print message
    ldr r0, =charPattern    @ Load format pattern for character input
    ldr r1, =charInput      @ Load address where input will be stored
    bl scanf                @ Read user input

    cmp r0, #READERROR      @ Check if input was invalid
    beq invalid_input       @ If invalid, go to error handling

    ldr r1, =charInput      @ Load input character
    ldrb r1, [r1]           @ Read the character

    cmp r1, #'B'            @ Check if input is 'B' (start brewing)
    beq select_cup
    cmp r1, #'b'            @ Check for lowercase 'b'
    beq select_cup
    cmp r1, #'T'            @ Check if input is 'T' (turn off)
    beq done
    cmp r1, #'t'            @ Check for lowercase 't'
    beq done
    cmp r1, #'H'            @ Check if input is 'H' (hidden inventory)
    beq hidden_inv
    cmp r1, #'h'            @ Check for lowercase 'h'
    beq hidden_inv

@*******************
invalid_input:
@*******************
    ldr r0, =invalidInputMessage  @ Load error message address
    bl printf                     @ Print error message
    b menu                        @ Return to menu loop

@*******************
select_cup:
@*******************
    ldr r0, =cupSizePrompt  @ Prompt user for cup size
    bl printf
    ldr r0, =numPattern     @ Load number pattern for input
    ldr r1, =numInput       @ Load address to store input
    bl scanf                @ Read input

    cmp r0, #READERROR      @ Check if input was invalid
    beq invalid_cup         @ If invalid, handle error

    ldr r1, =numInput       @ Load cup size input
    ldrb r1, [r1]           @ Read input value

    cmp r1, #1              @ If input is 1, set small cup size
    beq set_small
    cmp r1, #2              @ If input is 2, set medium cup size
    beq set_medium
    cmp r1, #3              @ If input is 3, set large cup size
    beq set_large

@*******************
invalid_cup:
@*******************
    ldr r0, =invalidInputMessage  @ Load error message address
    bl printf                     @ Print error message
    b select_cup                  @ Return to cup selection

@*******************
set_small:
@*******************
    mov r9, #6       @ Set cup size to 6 oz
    b check_water

@*******************
set_medium:
@*******************
    mov r9, #8       @ Set cup size to 8 oz
    b check_water

@*******************
set_large:
@*******************
    mov r9, #10      @ Set cup size to 10 oz
    b check_water

@*******************
check_water:
@*******************
    cmp r5, r9       @ Compare water level with cup size
    blt low_water    @ If not enough water, handle error
    b ready_to_brew

@*******************
low_water:
@*******************
    ldr r0, =notEnoughWater  @ Load error message address
    bl printf                @ Print error message
    b select_cup

@*******************
ready_to_brew:
@*******************
    ldr r0, =readyMessage  @ Prompt user to start brewing
    bl printf
    ldr r0, =charPattern  @ Load pattern for input
    ldr r1, =charInput    @ Load input address
    bl scanf              @ Read user input

    cmp r0, #READERROR    @ Check if input was invalid
    beq invalid_brew      @ Handle error if necessary

    ldr r1, =charInput    @ Load input character
    ldrb r1, [r1]

    cmp r1, #'B'          @ If input is 'B', start brewing
    beq brew
    cmp r1, #'b'          @ Check for lowercase 'b'
    beq brew

@*******************
invalid_brew:
@*******************
    ldr r0, =invalidInputMessage  @ Load error message address
    bl printf                     @ Print error message
    b ready_to_brew               @ Prompt user again

@*******************
brew:
@*******************
    sub r5, r5, r9    @ Subtract selected cup size from water level

                      @ Update cup count based on size selected
    cmp r9, #6
    beq update_small
    cmp r9, #8
    beq update_medium
    cmp r9, #10
    beq update_large
    b post_brew

@*******************
update_small:
@*******************
    add r6, r6, #1  @ Increment small cup count
    b post_brew

@*******************
update_medium:
@*******************
    add r7, r7, #1  @ Increment medium cup count
    b post_brew

@*******************
update_large:
@*******************
    add r8, r8, #1  @ Increment large cup count
    b post_brew

@*******************
post_brew:
@*******************
    ldr r0, =brewingComplete  @ Load message address
    bl printf                 @ Print brewing complete message

    cmp r5, #6                @ Check if water is too low
    blt refill_needed         @ If yes, prompt for refill
    b menu                    @ Otherwise, return to menu

@*******************
refill_needed:
@*******************
    ldr r0, =refillMessage  @ Load refill message
    bl printf               @ Print message
    b done

@*******************
done:
@*******************
    ldr r0, =exitMessage  @ Load exit message
    bl printf             @ Print exit message
    mov r7, #0x01         @ Exit status
    svc 0                 @ End program

@*******************
hidden_inv:
@*******************
    ldr r0, =hiddenWaterMessage  @ Load water level message
    mov r1, r5                   @ Load water level
    bl printf

    ldr r0, =hiddenCupMessage  @ Load cup count message
    mov r1, r6                 @ Load small cup count
    mov r2, r7                 @ Load medium cup count
    mov r3, r8                 @ Load large cup count
    bl printf
    b menu                     @ Return to menu

.data
@ Declare the strings and data needed

.balign 4
welcomeMessage: .asciz "Welcome to the Coffee Maker\n"
.balign 4
insertMessage: .asciz "Insert K-cup and press B to begin making coffee.\nPress T to turn off the machine.\nPress H or h to display secret menu.\n"
.balign 4
cupSizePrompt: .asciz "Select cup size: 1. Small (6 oz)  2. Medium (8 oz)  3. Large (10 oz)\n"
.balign 4
readyMessage: .asciz "Ready to Brew. Place cup and press B to start brewing.\n"
.balign 4
brewingComplete: .asciz "Brewing complete. Enjoy your coffee!\n"
.balign 4
notEnoughWater: .asciz "Not enough water. Select a smaller cup size.\n"
.balign 4
refillMessage: .asciz "Water too low. Please refill the reservoir.\nMachine turning off...\n"
.balign 4
hiddenWaterMessage: .asciz "Water left: %d oz\n"
.balign 4
hiddenCupMessage: .asciz "Small cups: %d, Medium cups: %d, Large cups: %d\n"
.balign 4
exitMessage: .asciz "Turning off the coffee machine. Goodbye!\n"
.balign 4
invalidInputMessage: .asciz "Invalid input. Please enter a valid option.\n"

@ Format pattern for scanf call.

.balign 4
charPattern: .asciz " %c"
.balign 4
numPattern: .asciz " %d"

.balign 4
charInput: .byte 0
.balign 4
numInput: .word 0

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

