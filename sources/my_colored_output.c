/*
**
** ETNA PROJECT, 03/01/2022 by habert_j && hamia_r
** my_colored_output
** File description: all functions needed to check files and print good color on output depending is type (dir,file,executable,sym link)
** entered in the command line by the user.
**
*/
#include "../headers/extlib.h"
#include "../headers/libmy.h"
#include "../headers/flags.h"
//define colors macro 
#define ANSI_COLOR_GREEN "\x1b[32m" //set color green for executable
#define ANSI_COLOR_BLUE "\x1b[34m" //set color blue for Directory 
#define ANSI_COLOR_CYAN "\x1b[36m" //set color cyan for symbolyc link
#define ANSI_COLOR_RESET "\x1b[0m" // reset color
//check files type en send a char with first letter of my file type 
char check_targeted_file_type(Flags * params,char * path)
{
    char type_file;
    struct stat st; // create a stat to recover informations
    if(params->ls_L == 0 ? lstat(path, &st) == -1 : stat(path, &st)== -1)
        {   
            perror("stat"); //catch unexpected error
            exit(EXIT_FAILURE);
        }
        else
        {
            switch (st.st_mode & S_IFMT) 
            {
                case S_IFDIR:
                    type_file = 'd';
                    break;
                case S_IFLNK:
                    type_file = 'l';
                break;
                case S_IFREG:
                    type_file = '-';
                    break;
                default:
                    type_file = '?';
                break;
            }

            int is_exe = 0;

            if(type_file == '-')
            {
                if(st.st_mode & S_IXUSR)
                {
                    is_exe = 1;
                }
                else if(st.st_mode & S_IXGRP)
                {
                    is_exe = 1;
                }
                else if(st.st_mode & S_IXOTH)
                {
                    is_exe = 1;
                }
                if(is_exe)
                {
                    type_file = 'e';
                }
            }
        }
    return type_file;
}
//function that set color in function of file type
void my_colored_output(char * file_name,char * path,Flags * params)
{
    char file_type = check_targeted_file_type(params,path);
    switch(file_type)
    {
        case 'e':
            my_putstr(ANSI_COLOR_GREEN);
            my_putstr(file_name);
            my_putstr(ANSI_COLOR_RESET);
            break;
        case 'l':
            my_putstr(ANSI_COLOR_CYAN);
            my_putstr(file_name);
            my_putstr(ANSI_COLOR_RESET);
            break;
        case 'd':
            my_putstr(ANSI_COLOR_BLUE);
            my_putstr(file_name);
            my_putstr(ANSI_COLOR_RESET);
            break;
        default :
            my_putstr(file_name);
            break;
    }
}