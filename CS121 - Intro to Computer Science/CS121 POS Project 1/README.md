# CS121-POS-Project-1
Simple POS system for furniture store. 

Problem Statement:
Design a simple point of sale program that can perform sales for a furniture company.   The user should be able to pull up a list of furniture for sale, select one, and it will calculate the price with taxes and save the transaction. 

System Requirements:
Must be in C++.  You are encouraged to use VSCode but you don’t have to.  
The list of items and their prices should be read from a text file. You can format it however you want.  
The list of transactions should be written to a text file, but it should save all transactions.  In other words, if I run it once and buy a table, then run it an hour later and buy a chair the transaction file should have both the table and the chair.  

User Requirements
The User should have a menu (in the console, no graphical user interface unless you want to).  
The menu should allow the user to buy an item or quit (at a minimum)
The menu should continue prompting the user until they quit.
If the user choices buy, the menu should show a list of available furniture and the prices 
Once the user selects an item, it should calculate the total with tax and show the user (as well as save the transaction) and return to the main menu. 
