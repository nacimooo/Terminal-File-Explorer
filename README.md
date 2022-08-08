# Terminal-File-Explorer
A file explorer for bash

# Change Log:
- added a Create File feature
- added a Remove File feature that safely deletes files
- added a modular confirmation menu


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
There are things that I would still like to add, such as a Custom Command feature, a smarter implementation of the "previous directory" feature.

# How to Install:
Go to the directory where you downloaded the source file and run the following command in terminal:
gcc manager.c -o manager.out -lncurses

# Screenshots

<img width="991" alt="Screen Shot 2022-08-08 at 3 41 13 PM" src="https://user-images.githubusercontent.com/105907112/183520513-9173ccf2-8c3e-4b95-a64f-f2e8db6a8298.png">

<img width="886" alt="Screen Shot 2022-08-08 at 3 41 47 PM" src="https://user-images.githubusercontent.com/105907112/183520522-c68514ec-ad73-45b5-9d2b-6a3075b785f1.png">

<img width="989" alt="Screen Shot 2022-08-08 at 3 42 05 PM" src="https://user-images.githubusercontent.com/105907112/183520524-3e5c08ec-6834-40d1-9390-94377b012a82.png">

<img width="991" alt="Screen Shot 2022-08-08 at 3 42 53 PM" src="https://user-images.githubusercontent.com/105907112/183520526-e38565d9-0538-48c0-96ae-e505ddb5e579.png">

