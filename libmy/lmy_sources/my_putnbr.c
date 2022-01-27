/*
** ETNA PROJECT, 27/09/2021 by habert_j
** my_putnbr
** File description:
**      Write a function that displays the number given as a parameter. It must be able to display all the possible values of an int.
*/
#include "../lmy_headers/my_putchar.h"
void my_putnbr (int number)
{
    unsigned int n = 0;
    int modulo = 0;
        	if (number<0)
        {
            my_putchar('-');
            n=number*-1;
	}
            else {
                n=number;
            }
    if (n>9)
        {
            modulo=n%10;
            my_putnbr(n/10);
            my_putchar(modulo+'0');
        }
        else
        {
            my_putchar(n+'0');
        }
}
