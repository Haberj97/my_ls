/*
** ETNA PROJECT, 22/12/2021 by habert_j
** my_putstr
** File description:
**      function that displays, one-by-one, the characters of a string.
The address of the string's first character will be found in the pointer passed as a parameter to the function.
*/
#include "../lmy_headers/my_putchar.h"
void my_putstr(char *str)
{
    int i = 0;
    
    while(str[i] !='\0')
        {
            my_putchar(str[i]);
            i++;
        }
}