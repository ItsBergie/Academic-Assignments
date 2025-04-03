@ Filename: BergLab5.s
@ Author:   Eli Berg
@ Email: erb0023@uah.edu
@ CS309-01 2024
@ Purpose:  Program will have to track multiple items forcing the use of memory 
@           or the stack to save and restore data values.
@           This program will simulate operation of a gasoline pump.
@ History: 
@    Date       Purpose of change
@    ----       ----------------- 
@   Nov 11 2024 - Intial creation of file and attempt of creating program

@ Use these commands to assemble, link, run and debug this program:
@    as -o BergLab5.o BergLab5.s
@    gcc -o BergLab5 BergLab5.o
@    ./BergLab5 ;echo $?
@    gdb --args ./BergLab5 

.equ READERROR, 0        @ Used to check for scanf read error. 

.global main             @ Have to use main because of C library uses. 

main:
    @ Initialize inventory levels
    mov r4, #500         @ Regular inventory in tenths of gallons
    mov r5, #500         @ Mid-Grade inventory in tenths of gallons
    mov r6, #500         @ Premium inventory in tenths of gallons

    @ Initialize dollar amounts dispensed
    mov r7, #0           @ Regular dollar amount
    mov r8, #0           @ Mid-Grade dollar amount
    mov r9, #0           @ Premium dollar amount

    @ Display welcome message and initial inventory
    ldr r0, =strWelcome
    bl  printf
    bl  displayInventory

prompt:
    @ Grade selection prompt
    ldr r0, =strGradePrompt
    bl  printf
    ldr r0, =gradeInputPattern
    ldr r1, =gradeInput
    bl  scanf

    @ Check for valid grade
    ldr r1, =gradeInput
    ldrb r1, [r1]           @ Load first character from input
    cmp r1, #'R'
    beq selectRegular
    cmp r1, #'G'
    beq selectMidGrade
    cmp r1, #'P'
    beq selectPremium
    cmp r1, #'S'
    beq displayInventory:

    @ Invalid grade selection
    ldr r0, =strInvalidGrade
    bl  printf
    b   prompt

selectRegular:
    ldr r0, =strRegularSelected
    bl  printf
    mov r10, #250         @ Price per gallon for Regular
    mov r11, #4           @ Gallons dispensed per dollar
    
    @ Prompt for dollar amount
    ldr r0, =strDollarPrompt
    bl  printf
    ldr r0, =numInputPattern
    ldr r1, =dollarAmount
    bl  scanf

    CMP r0, #READERROR		@ Check r0 for a readerror
    BEQ readerror               @ If r0 has a readerror, branch to readerror handler

    @ Validate dollar amount (1 <= amount <= 50)
    ldr r1, =dollarAmount
    ldr r1, [r1]
    cmp r1, #1
    blt invalidDollar
    cmp r1, #50
    bgt invalidDollar

    @ Calculate gallons to dispense and update inventory
    mul r2, r1, r11           @ Gallons in tenths
    cmp r4, r2
    blt insufficientInventory
    sub r4, r4, r2          @ Update inventory
    @ Update inventory and amount dispensed
    add r7, r7, r1            @ Update dollar total for grade
    b   update


selectMidGrade:
    ldr r0, =strMidGradeSelected
    bl  printf
    mov r10, #333         @ Price per gallon for Mid-Grade
    mov r11, #3           @ Gallons dispensed per dollar
    @ Prompt for dollar amount
    ldr r0, =strDollarPrompt
    bl  printf
    ldr r0, =numInputPattern
    ldr r1, =dollarAmount
    bl  scanf

    CMP r0, #READERROR		@ Check r0 for a readerror
    BEQ readerror               @ If r0 has a readerror, branch to readerror handler

    @ Validate dollar amount (1 <= amount <= 50)
    ldr r1, =dollarAmount
    ldr r1, [r1]
    cmp r1, #1
    blt invalidDollar
    cmp r1, #50
    bgt invalidDollar

    @ Calculate gallons to dispense and update inventory
    mul r2, r1, r11           @ Gallons in tenths
    cmp r5, r2
    blt insufficientInventory
    sub r5, r5, r2          @ Update inventory
    @ Update inventory and amount dispensed
    add r8, r8, r1            @ Update dollar total for grade
    b   update

selectPremium:
    ldr r0, =strPremiumSelected
    bl  printf
    mov r10, #500         @ Price per gallon for Premium
    mov r11, #2           @ Gallons dispensed per dollar
    @ Prompt for dollar amount
    ldr r0, =strDollarPrompt
    bl  printf
    ldr r0, =numInputPattern
    ldr r1, =dollarAmount
    bl  scanf

    CMP r0, #READERROR		@ Check r0 for a readerror
    BEQ readerror               @ If r0 has a readerror, branch to readerror handler

    @ Validate dollar amount (1 <= amount <= 50)
    ldr r1, =dollarAmount
    ldr r1, [r1]
    cmp r1, #1
    blt invalidDollar
    cmp r1, #50
    bgt invalidDollar

    @ Calculate gallons to dispense and update inventory
    mul r2, r1, r11           @ Gallons in tenths
    cmp r6, r2
    blt insufficientInventory
    sub r6, r6, r2          @ Update inventory
    @ Update inventory and amount dispensed
    add r9, r9, r1            @ Update dollar total for grade
    b   update

invalidDollar:
    ldr r0, =strInvalidDollar
    bl  printf
    b   prompt

insufficientInventory:
    ldr r0, =strInsufficient
    bl  printf
    b   prompt

update:
    @ Check if all grades are below threshold
    cmp r4, #10
    blt checkMid
    b   prompt

checkMid:
    cmp r5, #10
    blt checkPremium
    b   prompt

checkPremium:
    cmp r6, #10
    blt terminate
    b   prompt

terminate:
    ldr r0, =strTerminate
    bl  printf
    mov r7, #0x01           @ Exit system call
    svc 0

displayInventory:
    @ Display current inventory and dispensed totals
    ldr r0, =strInventory
    mov r1, r4
    mov r2, r5
    mov r3, r6
    bl  printf
    ldr r0, =strDollarAmounts
    mov r1, r7
    mov r2, r8
    mov r3, r9
    bl  printf
    bx lr

readerror:
    LDR r0, =strInputPattern	@ Load capture pattern to clear input buffer
    LDR r1, =strInputError		@ Load skip pattern to clear input buffer
    BL scanf			@ Call scanf (to clear input buffer)

.data
.balign 4
strWelcome: .asciz "Welcome to the Gasoline Pump. \n"
.balign 4
strGradePrompt: .asciz "Select Grade of gas to dispense (R, G, P): \n"
.balign 4
strRegularSelected: .asciz "You selected Regular. \n"
.balign 4
strMidGradeSelected: .asciz "You selected Mid-Grade. \n"
.balign 4
strPremiumSelected: .asciz "You selected Premium. \n"
.balign 4
strInvalidGrade: .asciz "Invalid dollar amount. Please try again.\n"
.balign 4
strDollarPrompt: .asciz "Enter Dollar amount to dispense (1-50): \n"
.balign 4
strInventory: .asciz "Current inventory (tenths of gallons):\nRegular: %d\nMid-Grade: %d\nPremium: %d\n"
.balign 4
strDollarAmounts: .asciz "Dollar amount dispensed by grade:\nRegular: $%d\nMid-Grade: $%d\nPremium: $%d\n"
.balign 4
strInvalidDollar: .asciz "Invalid dollar amount. Please try again.\n"
.balign 4
strInsufficient: .asciz "Not enough gasoline to meet the request. Enter a lower amount.\n"
.balign 4
strTerminate: .asciz "All grades are below 1 gallon. Shutting down.\n"
.balign 4
gradeInputPattern: .asciz "%c"
.balign 4
numInputPattern: .asciz "%d"
.balign 4
gradeInput: .space 4
.balign 4
dollarAmount: .word 0
.balign 4
strInputPattern: .asciz "%[^\n]"
.balign 4
strInputError: .skip 100*4

.global printf
.global scanf
