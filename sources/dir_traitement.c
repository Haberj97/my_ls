/*
**
** ETNA PROJECT, 01/2022 by habert_j && hamia_r
** dir_traitement
** File description: is file reportory all function that need to do analysis under directory
** entered in the command line by the user.
**
*/
#include "../headers/flags.h"
#include "../headers/libmy.h"
#include "../headers/extlib.h"

//function used for count number of files inside a targeted directory
int count_n_file(int *n_files,Flags *params,char * actual_string_path)
{
    struct dirent *directory_entry;  // Pointer for directory entry     
    DIR *targeted_directory = opendir(actual_string_path); // opendir() returns a pointer of DIR type. 

    if(targeted_directory == NULL)  // opendir returns NULL if couldn't open directory
    {
        my_putstr("Could not open current directory");
        return 0;
        
    }
    
    while((directory_entry = readdir(targeted_directory)) != NULL)
    {
        if(params->ls_a == 0 && directory_entry->d_name[0]!='.' && params->ls_A == 0)
        {
            *n_files +=1;
            
        }
        else if (params->ls_a == 1 && params->ls_A ==0)
        {
            *n_files +=1;
        }else if((directory_entry->d_name[1] && directory_entry->d_name[1] != '.' && params->ls_A == 1))
        {
            *n_files +=1;
        }
    }
    closedir(targeted_directory);
    return 0;
}

// this function check a path return 0 for a dir 1 for error 2 for file
int check_if_dir_exist(char * path)
{
    int status = 0;
    DIR *targeted_directory = opendir(path); // opendir() returns a pointer of DIR type.                                                                      
            if(!targeted_directory)
            {
                if(errno == ENOENT)
                {
                    status = 1;
                    perror("invalid dir");
                }
                else
                {
                    status = 2;
                    return status;

                }
                return EXIT_FAILURE;
            }
            closedir(targeted_directory);
            return status;
}
// this function check a path return 0 for a dir 1 for error 2 for file is used into recursive 
int check_if_dir_exist_2(char * path)
{
    int status = 0;
    
    DIR *targeted_directory = opendir(path); // opendir() returns a pointer of DIR type. 
            if(!targeted_directory)
            {
                if(errno == ENOENT)
                {
                    status = 1;
                    return status;
                    
                }
                else
                {
                    status = 2;
                    return status;
                    
                }   
            }
            closedir(targeted_directory);
            return status;
}