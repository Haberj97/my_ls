/*
** ETNA PROJECT, 28/09/2021 by habert_j
** my_strlen
** File description:
**      counts and returns the number of characters found in the string passed as parameter.
*/
void my_putchar(char c);
int my_strlen(const char *str)
{
    int counter=0;
    for(int i=0;str[i]!='\0';i++)
    {
        counter++;
    }
    return counter;
}
