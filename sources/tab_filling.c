/*
** ETNA PROJECT, 01/2022 by habert_j && hamia_r
** tab_filling
** File description:
**      functions used to fill a table with strings and free memory  
*/

#include "../headers/flags.h"
#include "../headers/libmy.h"
#include "../headers/extlib.h"

//function that fill a table 
void fill_my_table(char ** tab_file_name,Flags *params,char * actual_string_path)
{
        struct dirent *directory_entry;  // Pointer for directory entry     
        DIR *targeted_directory = opendir(actual_string_path); // opendir() returns a pointer of DIR type. 
        int i = 0;
        //while i read an entry in my table
        while ((directory_entry = readdir(targeted_directory)) != NULL)
        {
            if(params->ls_a == 0 && directory_entry->d_name[0]!='.' && params->ls_A == 0) // for a simple ls i recover all exepte hide files
            {
                tab_file_name[i] = my_strdup(directory_entry->d_name); //used dynamyc allocation et cpy str inside
                
                i++;
            }
            else if (params->ls_a == 1 && params->ls_A ==0) // if -a recover all files 
            {
                tab_file_name[i] = my_strdup(directory_entry->d_name);
                i++;
            }else if((directory_entry->d_name[1] && directory_entry->d_name[1] != '.' && params->ls_A == 1))//if -A ignore only . and ..
            {
                tab_file_name[i] = my_strdup(directory_entry->d_name);
                i++;
            }
        }
  closedir(targeted_directory);
}

// is the oposite of previous function to free memory
void free_filled_by_my_table(char ** tab_file_name,Flags *params,char * actual_string_path)
{
        struct dirent *directory_entry;  // Pointer for directory entry     
        DIR *targeted_directory = opendir(actual_string_path); // opendir() returns a pointer of DIR type. 
        int i = 0;

        while ((directory_entry = readdir(targeted_directory)) != NULL)
        {
            if(params->ls_a == 0 && directory_entry->d_name[0]!='.' && params->ls_A == 0)
            {
                free(tab_file_name[i]);
                
                i++;
            }else if (params->ls_a == 1 && params->ls_A ==0)
            {
                free(tab_file_name[i]);
                i++;
            }else if((directory_entry->d_name[1] && directory_entry->d_name[1] != '.' && params->ls_A == 1))
            {
                free(tab_file_name[i]);
                i++;
            }
        }
  closedir(targeted_directory);
}
