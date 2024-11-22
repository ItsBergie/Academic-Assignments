@ File:    Berg1.s
@ Author:  Eli Berg
@ Email: erb0023@uah.edu
@ CS309-02 2024
@ Purpose: Provide enough assembly to allow students to complete an assignment. 
@ History: 
@    29-Sep-2024 Created, Commented, and Finished ARM Hello World (ARM1) Assignment 
@    
@ Use these commands to assemble, link, run and debug the program
@
@  as -o Berg1.o Berg1.s
@  gcc -o Berg1 Berg1.o
@  ./Berg1 ;echo $?
@  gdb --args ./Berg1

.global main 
main:        @Must use this label where to start executing the code.

@ Part 1 - Print name message using the system call.
@
@ Use system call to write string to the STDIO
@   r0 - Must contain 1 to output to the standard output device (screen).
@   r1 - Must contain the starting address of the string to be printed. The string
@        has to comply with C coding standards. The string must be declared as a
@        .asciz so that it termimates with a \0 (null) character. 
@   r2 - Length of the string to be printed.
@   r7 - Must contain a 4 to write. 

    MOV   r7, #0x04    @ A 4 is a write command and has to be in r7.
    MOV   r0, #0x01    @ 01 is the STD (standard) output device. 
    MOV   r2, #0x09    @ Length of string to print (in Hex).
    LDR   r1, =string1 @ Put address of the start of the string in r1
    SVC   0            @ Do the system call

@ Part 2 - Print UAH email using the C function printf
@
@ Use the C library call printf to print the second string. Details on 
@ how to use this function is given in the .data section.

    LDR  r0, =string2 @ Put address of string in r0
    BL   printf       @ Make the call to printf

@ Part 3 - Print "This is my first ARM Assembly program for CS309-02 2024." using System Service Call

MOV   r7, #0x04    @ A 4 is a write command and has to be in r7.
    MOV   r0, #0x01    @ 01 is the STD (standard) output device. 
    MOV   r2, #0x39    @ Length of string to print (in Hex).
    LDR   r1, =string3 @ Put address of the start of the string in r1
    SVC   0            @ Do the system call

@ Force the exit of this program and return command to OS.

    MOV  r7, #0X01
    SVC  0

.data       @ Lets the OS know it is OK to write to this area of memory. 
.balign 4   @ Force a word boundry.
string1: .asciz "Eli Berg\n"  @Length 0x09

.balign 4   @ Force a word boundry
string2: .asciz "erb0023@uah.edu\n" @Length 0x10

string3: .asciz "This is my first ARM Assembly program for CS309-02 2024.\n" @Length 0x39

.global printf
