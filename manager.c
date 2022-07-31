#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

int main(){
    // size of the max characters
    const int SIZE = 100;
    // the line gotten from the file
    char line[SIZE];
    // total number of lines in the file
    int num_of_lines = 0;

    char path[100] = "~/'";
    char previous_path[100]; 

    // current line
    char current_line[SIZE];
    // input from getch
    char current_input;
    // position
    int current_position = 0;
    int cursor_position = 0;

    // path stuff
    char current_path[200];

    // start the screen
    initscr();
    
    // print the screen
    system("cd ~ && ls > /Users/nacimkhelifi/Documents/Programs/dir_out/out.txt");
                          
    FILE *dir_file = fopen("/Users/nacimkhelifi/Documents/Programs/dir_out/out.txt", "r");
    

    int write = 0;
     
    while (current_input != 'q'){
        // reset the number of lines
        num_of_lines = 0;
        // open the file containing a list of the current directories
        dir_file = fopen("/Users/nacimkhelifi/Documents/Programs/dir_out/out.txt", "r");

        // count the number of lines
        while(fgets(line, SIZE, dir_file)){
        num_of_lines++;
        }

        dir_file = fopen("/Users/nacimkhelifi/Documents/Programs/dir_out/out.txt", "r");

        // format print
        printw("----------------------------------------------------------------------------------\n(N)ew Directory\t\t(R)Delete Directory\t\t(P)revious Directory\n----------------------------------------------------------------------------------\n");
        printw("%d items in directory\n----------------------------------------------------------------------------------\n", num_of_lines);

        // current position in the file being read
        current_position = 0;

        // read through every line in the file
        while(fgets(line, SIZE, dir_file)){
            // get the contents of the line and put it in a formated string
            for (int i = 0; i < SIZE; i++){
                // leave a space for the cursor
                current_line[0] = ' ';
                current_line[i + 1] = line[i];
            }


            // put the cursor in front of the right item
            if (current_position == cursor_position){
                // postion the cursor
                current_line[0] = '#';



                // FOR GOING BACK
                if (write == 2){
                    
                     // format print
        printw("----------------------------------------------------------------------------------\n(N)ew Directory\t\t(R)Delete Directory\t\t(P)revious Directory\n----------------------------------------------------------------------------------\n");

                    strcpy(path, previous_path);

                    // stitch together all the different strings
                    char com2[SIZE] = "cd ";
                    strcat(com2, path);
                    char after2[SIZE] = "' && ls > /Users/nacimkhelifi/Documents/Programs/dir_out/out.txt";
                    strcat(com2, after2);

                    // call system 
                    system(com2);
                    
                    cursor_position = 0;

                    write = 0;
                }


                // FOR GOING FORWARD
                while (write == 1){
                     for (int i = 0; i < sizeof(line); i++){
                        while(line[i] == '\n'){
                            line[i] = line[i+1];
                        }
                    }

                    // add the line name to the path
                        strcpy(previous_path, path);
                        strcat(path, line);
                        
                    
                    if (path[-1] == 'c' && path[-2] == '.' ){
                        
                        char run[] = "vim ";
                        
                        strcat(run, path);
                        
                        system(run);
                    }

                    if (path[-1] == 't' && path[-2] == 'x' && path[-3] == 't' && path[-4] == '.'){
                        char run[] = "vim ";
                        strcat(run, line);
                        system(run);
                    }

                    
                    else {
                        strcat(path, "'/'");
                        // format print
        printw("----------------------------------------------------------------------------------\n(N)ew Directory\t\t(R)Delete Directory\t\t(P)revious Directory\n----------------------------------------------------------------------------------\n");
        
                        // stitch together all the different strings
                        char com2[SIZE] = "cd ";
                        strcat(com2, path);
                        char after2[SIZE] = "' && ls > /Users/nacimkhelifi/Documents/Programs/dir_out/out.txt";
                        strcat(com2, after2);


                        // call system 
                        system(com2);

                        cursor_position = 0;

                        write = 0;
                    }
                }
            }
            
            printw(current_line);
            current_position++;
        }
    
    // get user input
    current_input = getch();

    if (current_input == 's'){
        cursor_position++;
    }

    if (current_input == 'w'){
        cursor_position--;
    }

    if (current_input == ' ' || current_input == '\n'){
        write = 1;
    }

    if (current_input == 'p'){
        write = 2;
    }

    if (cursor_position > num_of_lines-1){
        cursor_position = num_of_lines;
    }
    
    if (cursor_position < 0){
        cursor_position = 0;
    }

    // clear the screen
    clear();
    // close the file
    fclose(dir_file);
    }

    endwin();
    return 0;
}