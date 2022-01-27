/*
**
** ETNA PROJECT, 03/01/2022 by habert_j && hamia_r
** flags_management
** File description: in this file we find functions relating to the verification of all args  
** entered in the command line by the user.
**
*/

#include "../headers/libmy.h"
#include "../headers/my_ls_base.h"
#include "../headers/flags.h"
#include "../headers/extlib.h"

int main(int argc , char** argv)
{
    //calling my Flags structure that used to run process for flags
        Flags params;
        clear_flags_struct_params(&params);
        char default_path[3] = "./";
    //call functions that check flags can be founded in flags_management.c
    char ** tab = checkFlagsParameters(argc , argv ,&params);
    //send value to base_ls in function of num of options and paths
    if(argc == 1)
    {
        my_ls_base(&params,default_path);
    }
    else if(argc == 2)
    {
        if(params.n_dir == 0)
        {
                my_ls_base(&params,default_path);
        }else
        {
            my_ls_base(&params,tab[0]);    
        }
    }
    else if(argc>2)
    {
        if(params.n_dir > 0){for(int k = params.n_dir-1;k>=0;k--)
        {
            if(params.n_dir != 1)
            {
                my_putstr(tab[k]);
                my_putstr(" : ");
                my_putchar('\n');
            }
            my_ls_base(&params,tab[k]);
            if(k>0){my_putchar('\n');}
        }
        }
        else
        {
            my_ls_base(&params,default_path);
        }
        //if parameters have been entered
    }
    for(int i=0;i<params.n_dir;i++)
    {
      free(tab[i]);
    }
    free(tab);
    //in case of unexpected error return 1
    return 0;
}
