/*
** ETNA PROJECT, 03/01/2022 by habert_j && hamia_r
** my_ls_base
** File description:
**      this file is our rooter for options entered by users
*/
#include "../headers/extlib.h"
#include "../headers/libmy.h"
#include "../headers/flags.h"
#include "../headers/tab_sorting.h"
#include "../headers/tab_filling.h"
#include "../headers/tab_printing.h"
#include "../headers/my_ls_l.h"
#include "../headers/my_ls_R.h"
#include "../headers/dir_traitement.h"
#include "../headers/get_path.h"
#include "../headers/my_colored_output.h"

//this is the options router
int my_ls_base(Flags *params,char * actual_string_path )
{
    //checking if case .. because this case was a error case before and transform to ../
    //if is found 

    if(actual_string_path[2] == '\0' && actual_string_path[1] == '.')
        {
            char tempo[4] = "../";
            actual_string_path = tempo;
        }

    //checking if case . because this case was a error case before and transform to ./
    //if is found 

    if(actual_string_path[0] == '.' && actual_string_path[1] == '\0')
        {
            char tempo[3] = "./";
            actual_string_path = tempo;
        }

    /*
    * *
    * * case of path is unknowned 
    * *
    */ 
    if(check_if_dir_exist(actual_string_path)==1) // case path unknow cut the program and return 1 to main
    {
        return 1;
    }
    /*
    * *
    * * case or path is a file 
    * *
    */ 
    else if(check_if_dir_exist(actual_string_path)==2)
    {
        //create a table for store actual path 
        char ** tab_file_name = malloc(sizeof(char *));
        tab_file_name[0] = my_strdup(actual_string_path);

        //case flag ls 
        if(params->ls_l == 1)
        {
            print_stat(tab_file_name,1,&actual_string_path,params);
        }
        else // else for all other case report name of file
        {
            //my_putstr(actual_string_path);
            my_colored_output(actual_string_path,actual_string_path,params);
            my_putchar('\n');
        }
        //free allocated memory used
        free(tab_file_name[0]);
        free(tab_file_name);
        return 0;
    }
    
    /*
    * *
    * * rooter section if path is a directory and sort in function 
    * *
    */
    if(params->ls_R == 1) // if recusive is activated call function recursive()
    {
        recursive(actual_string_path, params);
    }
    else if (params->ls_d == 0) // if -d is unactivated 
    { 
        //Variables initialization
        int n_files = 0;
        char ** tab_file_name = NULL;
        char ** paths = NULL;
        //preparation of my table of file 
        count_n_file(&n_files,params,actual_string_path);
        tab_file_name = malloc((sizeof(char *)*n_files));

        //fill an sort my_table in alpha order 
        fill_my_table(tab_file_name,params,actual_string_path);
        sort_my_table_in_alpha_order(n_files,tab_file_name);

        paths = get_all_paths(actual_string_path,n_files,tab_file_name);
        if(params->ls_t) // case -t sorting my tab by mod time
        {
            sort_my_tab_by_mod_time(tab_file_name,n_files,paths);
        }
        if(params->ls_r) // case -r i reverse my table 
        {
            reverse_my_table(n_files,tab_file_name,paths);
        }
        
        //in case of -l root to print_stat to render detailed infos for print result else print_my_table
        params->ls_l == 1 ? print_stat(tab_file_name,n_files,paths,params) : print_my_table(n_files,tab_file_name,paths,params);
        free_filled_by_my_table(tab_file_name,params,actual_string_path);
        free(tab_file_name);
    }
    else if(params->ls_d) // traitement for -d 
    {
        char ** tab_file_name = malloc(sizeof(char *));
        tab_file_name[0] = my_strdup(actual_string_path);

        if(params->ls_l == 1)
        {
            print_stat(tab_file_name,1,&actual_string_path,params);
        }
        else
        {
            my_colored_output(actual_string_path,actual_string_path,params);
            my_putchar('\n');
        }

        free(tab_file_name[0]);
        free(tab_file_name);
    }
    return 0;
}









