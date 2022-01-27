/*
** ETNA PROJECT, 01/2022 by habert_j && hamia_r
** tab_printing 
** File description:
**      function that print with a simple loop content of my tab and return line if -1 is enter as option  
**      else use escape
*/
#include "../headers/flags.h"
#include "../headers/my_colored_output.h"
#include "../headers/libmy.h"

void print_my_table(int n_files,char ** tab_file_name,char ** path,Flags * params)
{
    for( int i = 0;i<n_files;i++)
    {
        //my_putstr(tab_file_name[i]);
        my_colored_output(tab_file_name[i],path[i],params);
        if(i<(n_files-1))
        {
            if(params->ls1 == 0)
            {
                my_putchar(' ');
                my_putchar(' ');  
            }
            else
            {
                my_putchar('\n');
            }
        }
        else
        {
            my_putchar('\n');
        }
    }
}
