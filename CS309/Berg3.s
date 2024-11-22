@ Filename: Berg3.s
@ Author:   Eli Berg
@ Email: erb0023@uah.edu
@ CS309-01 2024
@ Purpose:  Prompt user for integer and display < or > 100 and prompt user
@           for character and display if user input is Upper, Lower, or Special
@ History: 
@    Date       Purpose of change
@    ----       ----------------- 
@   Oct 9 2024 - Intial creation of file and attempt of creating program
@   Oct 14 2024 - Finished, commented, and tested code

@ Use these commands to assemble, link, run and debug this program:
@    as -o Berg3.o Berg3.s
@    gcc -o Berg3 Berg3.o
@    ./Berg3 ;echo $?
@    gdb --args ./Berg2 

.global _start

.section .data
prompt_number:    .asciz "Enter a number:\n"
less_than_100:    .asciz "The input number is less than 100.\n"
greater_or_equal: .asciz "The input number is greater than or equal to 100.\n"
prompt_char:      .asciz "Enter a single character:\n"
lower_case_msg:   .asciz "Lower case letter entered.\n"
upper_case_msg:   .asciz "Upper case letter entered.\n"
special_char_msg: .asciz "Special character entered.\n"
fmt_int:          .asciz "%d"
fmt_char:         .asciz " %c"    @ Space added before %c to handle newline from previous input

.section .bss
    .lcomm number, 4    @ Reserve 4 bytes for storing the number
    .lcomm character, 1 @ Reserve 1 byte for storing the character

.section .text
.global main

main:

    @ Prompt for the number
    ldr r0, =prompt_number  @ Load address of the prompt message
    bl printf               @ Print "Enter a number"
    
    ldr r0, =fmt_int        @ Load the format specifier for integer input
    ldr r1, =number         @ Load address where the input number will be stored
    bl scanf                @ Get user input for the number

    @ Check if the number is < 100
    ldr r1, =number         @ Load the address of the number
    ldr r2, [r1]            @ Load the number into r2
    cmp r2, #100            @ Compare the number with 100
    blt print_less_than_100 @ Branch if number < 100
    bge print_greater_equal @ Branch if number >= 100

print_less_than_100:
    ldr r0, =less_than_100  @ Load address of the "less than 100" message
    bl printf               @ Print "The input number is less than 100."
    b prompt_for_char        @ Go to the character input part

print_greater_equal:
    ldr r0, =greater_or_equal  @ Load address of the "greater than or equal to 100" message
    bl printf                  @ Print "The input number is greater than or equal to 100."
    b prompt_for_char        @ Go to the character input part

prompt_for_char:
    @ Prompt for the character
    ldr r0, =prompt_char       @ Load address of the prompt message
    bl printf                  @ Print "Enter a single character"

    ldr r0, =fmt_char          @ Load the format specifier for char input
    ldr r1, =character         @ Load address where the input character will be stored
    bl scanf                   @ Get user input for the character

    @ Check if the character is lowercase
    ldr r1, =character         @ Reload r1 with address of character
    ldrb r2, [r1]              @ Load the character into r2 using byte load (ldrb)
    cmp r2, #'a'               @ Compare the character with 'a'
    blt check_upper_case       @ If character < 'a', check for uppercase
    cmp r2, #'z'               @ Compare with 'z'
    ble print_lower_case       @ If character <= 'z', it's a lowercase letter

check_upper_case:
    cmp r2, #'A'               @ Compare with 'A'
    blt print_special_char     @ If character < 'A', it's a special character
    cmp r2, #'Z'               @ Compare with 'Z'
    ble print_upper_case       @ If character <= 'Z', it's an uppercase letter

print_special_char:
    ldr r0, =special_char_msg  @ Load address of "Special character entered."
    bl printf                  @ Print "Special character entered."
    b end_program              @ End program

print_lower_case:
    ldr r0, =lower_case_msg    @ Load address of "Lower case letter entered."
    bl printf                  @ Print "Lower case letter entered."
    b end_program              @ End program

print_upper_case:
    ldr r0, =upper_case_msg    @ Load address of "Upper case letter entered."
    bl printf                  @ Print "Upper case letter entered."
    b end_program              @ End program

end_program:
    mov r0, #0                 @ Return 0 as the exit status
    mov r7, #1                 @ Syscall number for exit
    svc 0                      @ Make syscall to exit
