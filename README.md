# Terminal-File-Explorer
A file explorer for bash

# Features:
- It allows the user to view and interact with their files directly from terminal without having to "cd" and "ls" their way around
- It allows the user to view and edit some files (.txt, .c and .java to be exact)
- it is smart enough to make its own directory when first run and if the directory itself is not available
- it allows the user to create sub directories directly.

# About:
This program is a files explorer that that allows for a more interactive and graphical interaction with terminal, it is made entirely in C and uses enlements from bash that are called directly from the program itself in order to be able to do changes to the directory.

# How it works:
The program relies heavily on the "system()" function present in the stdlib.h library, and passes it carefully constructed strings in order to get the desired effects. it also also uses elements I learned from making the Terminal Movement Game (Fruit Basket) to make the menues


# Limitations:
There are things that I would still like to add, such as a Custom Command feature, a smarter implementation of the "previous directory" feature, a way to create and delete files.

# How to Install:
Go to the directory where you downloaded the source file and run the following command in terminal:
gcc manager.c -o manager.out -lncurses

# Screenshots

<img width="938" alt="Screen Shot 2022-08-07 at 8 55 53 PM" src="https://user-images.githubusercontent.com/105907112/183329556-5757882a-8f31-4166-a04e-c7e5e77520be.png">

<img width="915" alt="Screen Shot 2022-08-07 at 8 56 50 PM" src="https://user-images.githubusercontent.com/105907112/183329560-c4259302-e438-4bc6-ac26-ab4ef6957bb6.png">

<img width="399" alt="Screen Shot 2022-08-07 at 8 56 21 PM" src="https://user-images.githubusercontent.com/105907112/183329558-97639678-b586-49e4-87f2-f401e8aac3ef.png">
