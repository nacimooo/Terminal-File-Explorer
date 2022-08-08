#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>


// size of the max characters
const int SIZE = 100;
// the line gotten from the file
char line[SIZE];
// total number of lines in the file
int num_of_lines = 0;

char path[100] = "~/'";
char previous_path[100]; 
char previous_previous_path[100];

// current line
char current_line[SIZE];
// input from getch
char current_input;
// position
int current_position = 0;
int cursor_position = 0;

// path stuff
char current_path[200];

int write = 0;

char options[] = "----------------------------------------------------------------------------------\n(N)ew Directory\t\t(P)revious Directory\t\t(Q)uit\n----------------------------------------------------------------------------------\n";

// checks if the given string is a file
int check_for_file(char string[]){
    for (int i = 0; i < strlen(string); i++){
        if (string[i] == '.' && string[i + 1] == 'c'){
            return 1;
        }
        if (string[i] == '.' && string[i + 1] == 't' && string[i + 2] == 'x' && string[i+3] == 't'){
            return 1;
        }
        if (string[i] == '.' && string[i + 1] == 'j' && string[i + 2] == 'a' && string[i+3] == 'v' && string[i+4] == 'a' ){
            return 1;
        }
    }

    return 0;
}

// refreshes the screen
void refresh_screen(){

    // stitch together all the different strings
    char com2[SIZE] = "cd ";
    strcat(com2, path);
    char after2[SIZE] = "' && ls > /Users/$(whoami)/Documents/Term_Manager/out.txt";
    strcat(com2, after2);

    // call system 
    system(com2);
    strcat(path, "/");
}


// edits the path string and returns its previous directory
char* go_back (char *String){

    // get the size of the string
    int size = 0;
    int i = 0;
    while (String[i] != '\0'){
        i++;
        size++;
    }
    
    // count down from the end of the string until we find '/' while moving the '\0' character down
    int times = 0;
    size = size -2;
    while (String[size] != '/' && times != 2){
        if (String[size] == '/'){
            times++;
        }
        if (String[size - 1] == '/'){
            times++;
        }
        
        String[size] = '\0';
        size--;
    }



    return String;
}

int main(){

    // start the screen
    initscr();

    // The followig section will get the name of the user to be used for file opening
    // create temporary file in the root directory
    system("touch temp.txt");
    // send the name of the user over to a file
    system("whoami > temp.txt");

    
    // this block of code basically gets the name of the user
    char whoami[100];
    FILE *whoami_file = fopen("./temp.txt", "r");
    while(fgets(line, SIZE, whoami_file)){
        strcpy(whoami, line);    
    }

    // this code stiches together the command that requests the directory names
    char master_dir[1000] = "/Users/";
    strcat(master_dir, whoami);
    strcat(master_dir, "/Documents/Term_Manager/out.txt");

    // this trims out the new line character
    for (int i = 0; i < sizeof(master_dir); i++){
        while(master_dir[i] == '\n'){
            master_dir[i] = master_dir[i+1];
            }
        }
    
    // remove the temp file
    system("rm temp.txt");


    // attempt to open the file
    FILE *dir_file = fopen(master_dir, "r");
    

    // if the file was not opened successfully, then the issue is probably the missing directory
    // create a directory.
    if ( dir_file == NULL){
        system("cd /Users/$(whoami)/Documents && mkdir Term_Manager && cd /Users/$(whoami)/Documents/Term_Manager && touch out.txt");
        clear();
        printw("----------------------------------------------------------------------------------\n\t\t\t\tAttention:\n----------------------------------------------------------------------------------\n\n\t\tRoot File Was Not Found, Created Dir and File\n\n\t\t\t\t   <ok>\n\n\n----------------------------------------------------------------------------------");
        getch();
        clear();
    }
    
    // get the dir infor 
    system("cd ~ && ls > /Users/$(whoami)/Documents/Term_Manager/out.txt");

    // reopen the file
    dir_file = fopen(master_dir, "r");
    

     
    while (current_input != 'q'){
        // reset the number of lines
        num_of_lines = 0;
        // open the file containing a list of the current directories
        dir_file = fopen(master_dir, "r");

        // count the number of lines
        while(fgets(line, SIZE, dir_file)){
        num_of_lines++;
        }

        dir_file = fopen(master_dir, "r");

        // format print
        printw("----------------------------------------------------------------------------------\nCurrent Directory: %s\n", path);
        printw("%s", options);
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
                current_line[0] = '>';



                // FOR GOING BACK
                if (write == 2){
                    
                     // format print
                    
                    strcpy(path, previous_path);
                    strcpy(previous_path, previous_previous_path);



                    // stitch together all the different strings
                    char com2[SIZE] = "cd ";
                    strcat(com2, path);
                    char after2[SIZE] = "' && ls > /Users/$(whoami)/Documents/Term_Manager/out.txt";
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
                        strcpy(previous_previous_path, previous_path);
                        strcpy(previous_path, path);
                        strcat(path, line);


                    if (check_for_file(path) == 1){
                        char vim[1000] = "vim ";
                        strcat(vim, path);
                        strcat(vim, "'");
                        system(vim);
                        strcpy(path, previous_path);
                        write = 0;
                        break;
                    }
                    
                    else{
                        // stitch together all the different strings
                        char com2[SIZE] = "cd ";
                        strcat(com2, path);
                        char after2[SIZE] = "' && ls > /Users/$(whoami)/Documents/Term_Manager/out.txt";
                        strcat(com2, after2);


                        // call system 
                        system(com2);
                        strcat(path, "/");

                        cursor_position = 0;

                        write = 0;}
                }

                if (write == 3){
                    // clear the screen for special action
                    clear();
                    // print prompts
                    printw("-----------------------------------\n\tCreating Directory\n-----------------------------------\n");
                    printw("Name of Directory: ");

                    // name of directory
                    char dir_name[100];
                    // get the name
                    scanw("%s", dir_name);
                    // current path
                    char dir_path[1000] = "";
                    strcpy(dir_path, path);

                    // add the directory name to the overall path
                    strcat(dir_path, dir_name);
                    // get the mk dir string to passed to the system command
                    char mkdir[1000] = "mkdir ";
                    strcat(mkdir, dir_path);
                    strcat(mkdir, "'");

                    // create the dir
                    system(mkdir);
                    printw("Directory Created Successfully");

                    // wait for user input
                    getch();
                    clear();


                    refresh_screen();
                    
                    write = 0;
                    
                }

                // custom command
                if (write == 4){
                    // clear the screen for special action
                    clear();
                    // print prompts
                    printw("-----------------------------------\n\tCustom Command\n-----------------------------------\n");
                    printw("Command: ");

                    // name of directory
                    char dir_name[100];
                    // get the name
                    scanw("%s", dir_name);
                    
                    getch();
                    clear();
                    refresh_screen();
                    write = 0;
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

    if (current_input == 'n' || current_input == 'N'){
        write = 3;
    }

    if (current_input == 'C' || current_input == 'c'){
        write = 4;
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