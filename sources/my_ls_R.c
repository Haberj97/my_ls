/*
** ETNA PROJECT, 01/2022 by habert_j && hamia_r
** my_ls_R
** File description:
**      this function list recursively a folder 
*/

#include "../headers/flags.h"
#include "../headers/libmy.h"
#include "../headers/extlib.h"
#include "../headers/dir_traitement.h"
#include "../headers/tab_sorting.h"
#include "../headers/tab_filling.h"
#include "../headers/tab_printing.h"
#include "../headers/my_ls_l.h"
#include "../headers/get_path.h"
#include "../headers/my_colored_output.h"

void recursive(char * actual_string_path, Flags *params)
{

    char **files = NULL;
    int nb_files = 0;
    char **path_of_dir = NULL;
    //checking content of the folder count n_files inside
    count_n_file(&nb_files,params,actual_string_path);
    
    files = malloc((sizeof(char *)*nb_files)); // allocated space in function of n_files inside folder

    fill_my_table(files,params,actual_string_path); // create table with all names of folder inside my dir

    sort_my_table_in_alpha_order(nb_files,files); // sort table by Alph
    
    path_of_dir = get_all_paths(actual_string_path,nb_files,files); // get path of all files 

    if(params->ls_t) // if -t sort by modification time
    {
        sort_my_tab_by_mod_time(files,nb_files,path_of_dir);
    } 
    
    if(params->ls_r) // if -r reverse the table 
    {
        reverse_my_table(nb_files,files,path_of_dir);
    }
    
    my_putchar('\n');
    my_putstr(actual_string_path);
    my_putchar(':');
    my_putchar('\n');

    if(params->ls_l) //if ls -l use this method for printing the files names 
    {
      print_stat(files,nb_files,path_of_dir,params);
      my_putchar('\n');
    }
    else //else use this method for printing the files names 
    { 
        for(int i = 0; i < nb_files;i++)
        {
            my_colored_output(files[i],path_of_dir[i],params);
            params->ls1 == 1 ? my_putchar('\n') : my_putchar(' ');
        }
        my_putchar('\n');
    }
    
    if (params->ls_l == 0)
    {
        my_putchar('\n');
    }
    for(int i = 0; i<nb_files ; i++) // check if any dir inside my actual dir use recursive call of my function
    {
            if (check_if_dir_exist_2(path_of_dir[i])==0)
            {
                recursive(path_of_dir[i],params);
            }
    }
    free_filled_by_my_table(files,params,actual_string_path);
    free(files);
    for(int i = 0;i<nb_files;i++)
    {
        free(path_of_dir[i]);
    }
    free(path_of_dir);
}
