/*
** ETNA PROJECT, 30/09/2021 by habert_j
** my_strcmp.c
** File description:
**     ---------------------------SYNOPSIS-----------------------                          int strcmp(const char *s1, const char *s2);                           -------------------------DESCRIPTION----------------------                   The  strcmp()  function compares the two strings s1 and s2.
       It returns an integer less than, equal to, or greater  than
       zero  if  s1  is  found,  respectively, to be less than, to
       match, or be greater than s2.

       The strncmp() function is similar, except it compares  only
       the first (at most) n bytes of s1 and s2.                                    -----------------------RETURN VALUE-----------------------
       The strcmp() and strncmp() functions return an integer less
       than, equal to, or greater than zero if s1 (or the first  n
       bytes  thereof) is found, respectively, to be less than, to
       match, or be greater than s2.
*/
#include <string.h>
int my_strcmp(const char *s1, const char *s2)
{
   
    int i = 0;
    while(s1[i]!='\0' && s2[i]!='\0')
        {
            if (s1[i]!=s2[i])
                {
                    int test= s1[i]-s2[i];
                    if (test>0)
                        {return 1;}
                    else{return -1;}
                } 
            i++;  
        }

        return 0;
    
}
