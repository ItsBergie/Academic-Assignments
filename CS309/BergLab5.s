@ Filename: BergLab5.s
@ Author:   Eli Berg
@ Email:    erb0023@uah.edu
@           CS309-02 2024
@
@ Purpose:  Create an example of a working gas pump in ARM assembly
@ 
@ History: 
@    Date       Purpose of change
@    ----       ----------------- 
@   13-Nov-2024  Student edited code to complete homework assignment
@
@ Use these commands to assemble, link, run and debug this program:
@    as -o BergLab5.o BergLab5.s
@    gcc -o BergLab5 BergLab5.o
@    ./BergLab5 ;echo $?
@    gdb --args ./BergLab5 

@ ***********************************************************************
@ The = (equal sign) is used in the ARM Assembler to get the address of a
@ label declared in the .data section. This takes the place of the ADR
@ instruction used in the textbook. 
@ ***********************************************************************

.equ READERROR, 0 @Used to check for scanf read error. 

.global main @ Have to use main because of C library uses. 

main:

@*******************
prompt:
@*******************

@ Print out a welcome.
 
   ldr r0, =strWelcome @ Put the address of my string into the first parameter
   bl  printf              @ Call the C printf to display input prompt. 

   mov r4, #500  @ set the regular gas ammount to 50 gallons or 500 tenths 
   mov r5, #500  @ set the medium gas ammount to 50 gallons or 500 tenths 
   mov r6, #500  @ set the premium gas ammount to 50 gallons or 500 tenths 

   mov r7, #0    @ set the regular money total ammount to 0 cents? dollars?
   mov r8, #0    @ set the medium money total ammount to 0 cents? dollars?
   mov r9, #0    @ set the premium money total ammount to 0 cents? dollars?

@*******************
Inventory:
@*******************

   ldr r0, =strInventoryHeader
   bl printf

   mov r1, r4
   ldr r0, =strRegularInventory
   bl printf

   mov r1, r5
   ldr r0, =strMediumInventory
   bl printf

   mov r1, r6
   ldr r0, =strPremiumInventory
   bl printf   

   ldr r0, =strDollarHeader
   bl printf

   mov r1, r7
   ldr r0, =strRegularTotal
   bl printf

   mov r1, r8
   ldr r0, =strMediumTotal
   bl printf

   mov r1, r9
   ldr r0, =strPremiumTotal
   bl printf

@*******************
get_input:
@*******************

@ Set up r0 with the address of input pattern.
@ scanf puts the input value at the address stored in r1. We are going
@ to use the address for our declared variable in the data section - intInput. 
@ After the call to scanf the input is at the address pointed to by r1 which 
@ in this case will be intInput. 

   ldr r0, =strSelectGrade
   bl printf

   ldr r0, =strGradeInput   @ Setup to read in one number.
   ldr r1, =gradeInput      @ load r1 with the address of where the
                            @ input value will be stored. 
   bl  scanf                @ scan the keyboard.
   cmp r0, #READERROR       @ Check for a read error.
   beq readerror            @ If there was a read error go handle it. 
   ldr r1, =gradeInput      @ Have to reload r1 because it gets wiped out. 
   ldr r10, [r1]            @ Read the contents of intInput and store in r1 so that
                            @ it can be printed. 

   adds r11, r4, r5
   adds r11, r11, r6
   cmp r11, #31
   bmi myexit

   cmp r10, #'R'
   beq Regular

   cmp r10, #'M'
   beq Medium

   cmp r10, #'P'
   beq Premium

   cmp r10, #'I'
   beq Inventory

   @ldr r0, =strInvalidInput
   @bl printf
   b get_input 
   

@*******************
Regular:
@*******************

   cmp r4, #4
   blt insufficent   

   ldr r0, =strRegularSelection
   bl printf

   ldr r0, =strDollarDispense
   bl printf

   ldr r0, =strDollarInput   @ Setup to read in one number.
   ldr r1, =dollarInput      @ load r1 with the address of where the
                             @ input value will be stored. 
   bl  scanf                 @ scan the keyboard.
   cmp r0, #READERROR        @ Check for a read error.
   beq readerror             @ If there was a read error go handle it. 
   ldr r1, =dollarInput      @ Have to reload r1 because it gets wiped out. 
   ldr r1, [r1]              @ Read the contents of intInput and store in r1 so that
                             @ it can be printed. 

   cmp r1, #1  @ compair with 1 to not be less than
   blt Regular

   mov r2, r1
   mov r10, r1
   mov r11, #4
   mul r2, r11  @ multiply input with 4 for the regular dispense
   cmp r2, r4
   bgt Regular
   
   cmp r1, #50  @ compair with 50 to not exceed
   bgt Regular

   cmp r1, #'A'
   bge Regular

   cmp r1, #'z'
   ble Regular

   mov r11, r2
   mov r1, r2
   
   ldr r0, =dispenseOutput
   bl printf

@ do calculations to keep up with everything
   sub r4, r11

   @mov r12, #250
   @mul r11, r12   @ multiplies the tenths of a gallon by the cents per thenth of a gallon
   add r7, r10
   
   b get_input

@*******************
Medium:
@*******************

   cmp r5, #3
   blt insufficent   

   ldr r0, =strMediumSelection
   bl printf

   ldr r0, =strDollarDispense
   bl printf

   ldr r0, =strDollarInput   @ Setup to read in one number.
   ldr r1, =dollarInput      @ load r1 with the address of where the
                             @ input value will be stored. 
   bl  scanf                 @ scan the keyboard.
   cmp r0, #READERROR        @ Check for a read error.
   beq readerror             @ If there was a read error go handle it. 
   ldr r1, =dollarInput      @ Have to reload r1 because it gets wiped out. 
   ldr r1, [r1]              @ Read the contents of intInput and store in r1 so that
                             @ it can be printed. 

   cmp r1, #1  @ compair with 1 to not be less than
   blt Medium

   mov r2, r1
   mov r10, r1
   mov r11, #3
   mul r2, r11  @ multiply input with 4 for the regular dispense
   cmp r2, r5
   bgt Medium
   
   cmp r1, #50  @ compair with 50 to not exceed
   bgt Medium

   mov r11, r2
   mov r1, r2
   
   ldr r0, =dispenseOutput
   bl printf

@ do calculations to keep up with everything
   sub r5, r11

   @mov r12, #33   @ 333 is out of range of size
   @mul r11, r12   @ multiplies the tenths of a gallon by the cents per thenth of a gallon
   add r8, r10
   
   b get_input

@*******************
Premium:
@*******************
   
   cmp r6, #2
   blt insufficent

   ldr r0, =strPremiumSelection
   bl printf

   ldr r0, =strDollarDispense
   bl printf

   ldr r0, =strDollarInput   @ Setup to read in one number.
   ldr r1, =dollarInput      @ load r1 with the address of where the
                             @ input value will be stored. 
   bl  scanf                 @ scan the keyboard.
   cmp r0, #READERROR        @ Check for a read error.
   beq readerror             @ If there was a read error go handle it. 
   ldr r1, =dollarInput      @ Have to reload r1 because it gets wiped out. 
   ldr r1, [r1]              @ Read the contents of intInput and store in r1 so that
                             @ it can be printed. 

   cmp r1, #1  @ compair with 1 to not be less than
   blt Premium

   mov r2, r1
   mov r10, r1
   mov r11, #2
   mul r2, r11  @ multiply input with 4 for the regular dispense
   cmp r2, r6
   bgt Premium
   
   cmp r1, #50  @ compair with 50 to not exceed
   bgt Premium

   mov r11, r2
   mov r1, r2
   
   ldr r0, =dispenseOutput
   bl printf

@ do calculations to keep up with everything
   sub r6, r11

   @mov r12, #5@#500
   @mul r11, r12   @ multiplies the tenths of a gallon by the cents per thenth of a gallon
   add r9, r10
   
   b get_input

@***********
insufficent:
@***********
   ldr r0, =strInsufficent
   bl printf
   b get_input

@***********
readerror:
@***********
@ Got a read error from the scanf routine. Clear out the input buffer then
@ branch back for the user to enter a value. 
@ Since an invalid entry was made we now have to clear out the input buffer by
@ reading with this format %[^\n] which will read the buffer until the user 
@ presses the CR. 

   ldr r0, =strInputPattern
   ldr r1, =strInputError   @ Put address into r1 for read.
   bl scanf                 @ scan the keyboard.

@  Not going to do anything with the input. This just cleans up the input buffer.  
@  The input buffer should now be clear so get another input.

   b prompt

@*******************
myexit:
@*******************
@ End of my code. Force the exit and return control to OS


   ldr r0, =strInventoryHeader
   bl printf

   mov r1, r4
   ldr r0, =strRegularInventory
   bl printf

   mov r1, r5
   ldr r0, =strMediumInventory
   bl printf

   mov r1, r6
   ldr r0, =strPremiumInventory
   bl printf   

   ldr r0, =strDollarHeader
   bl printf

   mov r1, r7
   ldr r0, =strRegularTotal
   bl printf

   mov r1, r8
   ldr r0, =strMediumTotal
   bl printf

   mov r1, r9
   ldr r0, =strPremiumTotal
   bl printf

   mov r7, #0x01 @ SVC call to exit
   svc 0         @ Make the system call. 

.data

@ Declare the strings and data needed

.balign 4
strWelcome: .asciz "Welcome to gasoline pump.\n"

.balign 4
strInventoryHeader: .asciz "Current inventory of gasoline (in tenths of gallons) is: \n\n"

.balign 4
strRegularInventory: .asciz "Regular    %d\n"

.balign 4
strMediumInventory:  .asciz "Mid-Grade  %d\n" 

.balign 4
strPremiumInventory: .asciz "Premium    %d\n"

.balign 4         
strDollarHeader: .asciz "\nDollar amount dispensed by grade:\n\n"

.balign 4
strRegularTotal:     .asciz "Regular    $%d\n"

.balign 4
strMediumTotal:      .asciz "Mid-Grade  $%d\n"

.balign 4
strPremiumTotal:     .asciz "Premium    $%d\n"

.balign 4
strSelectGrade: .asciz "\nSelect Grade of gas to dispense (R, M, or P): \n"

.balign 4
strInsufficent: .asciz "There are insufficent amount of gas in the pump\n\n"

.balign 4
strRegularSelection: .asciz "You selected Regular.\n\n"

.balign 4
strMediumSelection: .asciz "You selected Mid-Grade.\n\n"

.balign 4
strPremiumSelection: .asciz "You selected Premium.\n\n"

.balign 4
strDollarDispense: .asciz "Enter Dollar ammount to dispense (At least 1 and no more than 50): \n"

.balign 4
dispenseOutput: .asciz "%d tenths of gallons have been dispensed. \n\n"



@ Format pattern for scanf call.

.balign 4
strGradeInput: .asciz "%c"  @ char format for read. 

.balign 4
strDollarInput: .asciz "%d"

.balign 4
strInputPattern: .asciz "%[^\n]" @ Used to clear the input buffer for invalid input. 

.balign 4
strInputError: .skip 100*4  @ User to clear the input buffer for invalid input. 

.balign 4
gradeInput: .word 0   @ Location used to store the user input. 

.balign 4
dollarInput: .word 0

.balign 4
CODE: .asciz "code"


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
