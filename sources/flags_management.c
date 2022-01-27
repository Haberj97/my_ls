/*
**
** ETNA PROJECT, 01/2022 by habert_j && hamia_r
** flags_management
** File description: in this file we find functions relating to the verification of all args  
** entered in the command line by the user.
**
*/
#include "../headers/flags.h"
#include "../headers/libmy.h"
#include "../headers/extlib.h"

// Function used to initialize all value of our struct Flags to avoid random values
void clear_flags_struct_params(Flags * params)
{
    params->ls1 = 0;
    params->ls_l = 0;
    params->ls_a = 0;
    params->ls_r = 0;  
    params->ls_t = 0;
    params->n_dir = 0;
    params->ls_A = 0; 
    params->ls_d = 0; 
    params->ls_L = 0;
    params->ls_R = 0;
}
//function to check flags inserted by user 
char ** checkFlagsParameters(int argc , char **argv , Flags * params)
{
    // Variables declaration
    int last_dir = 0;
    char ** tab = NULL;

    //loop used to count args that can be path 
    for(int i = 1 ; i<argc ; i++)
    {
        if(argv[i][0] != '-')
        {
            params->n_dir ++;
        }
    }

    //memory allocation of our char ** in function of number of possibles path counted
    tab = malloc(sizeof(char*)*params->n_dir);

    //loop for flags checkings and files names storage
    for(int i = 1 ; i<argc ; i++)
    {
            //here if were see a path we store him into tab
            if(argv[i][0] != '-')
            {
                tab[last_dir] = my_strdup(argv[i]);
                last_dir++;
            }
            else
            {
                //here in function a flag (case of first char in the string is == - we initialize 
                // value into struc to one or reporting error if any unknow arg)
                switch(argv[i][1])
                {
                    case '1':
                        params->ls1 = 1;
                        break;
                    case 'l':
                        params->ls_l = 1;
                        break;
                    case 'a':
                        params->ls_a = 1;
                        break;
                    case 'r' : 
                        params->ls_r = 1;
                        break;
                    case 't' : 
                        params->ls_t = 1;
                        break;
                    case 'A' :
                        params->ls_A = 1;
                        break;
                    case 'd' : 
                        params->ls_d = 1;
                        break;
                    case 'L' : 
                        params->ls_L = 1;
                        break;
                    case 'R' : 
                        params->ls_R = 1;
                        break;
                    case 'h' : 
                        print_help();
                        exit(EXIT_SUCCESS);
                        break;
                    default : //default if not seen in other case report error
                        my_putstr("ls: option requires an argument -- ");
                        my_putchar(argv[i][1]);
                        my_putchar('\n');
                        my_putstr("Try 'ls --h' for more information. ");
                        my_putchar('\n');
                        exit(EXIT_SUCCESS);
                        break;
                }
            }        
    }
    return tab;
}
//function used to print informations in ./my_ls -h
void print_help()
{
    my_putstr("\n\n");
    my_putstr("Usage: ls [OPTION]... [FILE]... \nList information about the FILEs (the current directory by default).\nSort entries alphabetically if no sorting option specified.\n");
    my_putstr("\n Availables options list : \n\n");
    my_putstr("------------------------------ Bonus ------------------------------- \n \n");
    my_putstr("-1       list one file per line.\n");
    my_putchar('\n');
    my_putstr("-h       Show help manual.\n");
    my_putchar('\n');
    my_putstr("----------------------------- Subject ------------------------------ \n \n");
    my_putstr("-a       do not ignore entries starting with .\n");
    my_putchar('\n');
    my_putstr("-A       do not list implied . and ..\n");
    my_putchar('\n');
    my_putstr("-d       list directories themselves, not their contents\n");
    my_putchar('\n');
    my_putstr("-l       use a long listing format\n");
    my_putchar('\n');
    my_putstr("-L       when showing file information for a symbolic\n");
    my_putstr("         link, show information for the file the link\n");
    my_putstr("         references rather than for the link itself\n");
    my_putchar('\n');
    my_putstr("-r       reverse order while sorting\n");
    my_putchar('\n');
    my_putstr("-R       list subdirectories recursively\n");
    my_putchar('\n');
    my_putstr("-t       sort by modification time, newest first\n");
    my_putstr("\n\n");
}