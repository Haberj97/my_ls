/*
** ETNA PROJECT, 01/2022 by habert_j && hamia_r
** tab_sorting
** File description:
**      this folder contained all sorting tab algo  
*/

#include "../headers/extlib.h"
#include "../headers/libmy.h"
//function that converte a string to lowercase
char * my_str_to_lowercase(char * s1)
{
    char * str_lower_case = NULL;
    str_lower_case = malloc(sizeof(char)*my_strlen(s1));
    int i = 0;
    while (s1[i] != '\0')
    {
            if(s1[i] >= 'A' && s1[i] <= 'Z')
            {
                str_lower_case[i] = s1[i] + 32;
            }
            else
            {
                str_lower_case[i] = s1[i];
            }
        i++;
    }
    
    return str_lower_case;
}


//sort my table in alpha order
void sort_my_table_in_alpha_order(int n_files,char ** tab_file_name)
{
    int i =0,j = 0;
    char *temp = NULL;
    
    while (i < n_files)
        {
            j = 0;
            while (j < n_files)
            {
                int breaker = 0;
                int first_strlen = my_strlen(tab_file_name[i]);
                int second_strlen = my_strlen(tab_file_name[j]);
                // compare strlen to see how many letters i need to compare and create breacker
                //in function of return 
                if(first_strlen<second_strlen)
                {
                    breaker = my_strlen(tab_file_name[j]);
                }
                else if (first_strlen>second_strlen)
                {
                    breaker = my_strlen(tab_file_name[i]);
                }
                //comp string and swap them in alph order
                if(my_strncmp(my_str_to_lowercase(tab_file_name[i]), my_str_to_lowercase(tab_file_name[j]),breaker) <= 0)
                {
                    temp = tab_file_name[i];
                    tab_file_name[i] = tab_file_name[j];
                    tab_file_name[j] = temp;
                }
                j++;
            }
            i++;
        }
}

//function used to reverse a table 
void reverse_my_table(int n_files,char ** tab_file_name,char ** tab_directory)
{
    char * temp = NULL; 
    int i = 0;
    while(i<(n_files/2)) // loop when table and swap tab[last-i] and tab[i] until middle of table 
    {
        temp = tab_file_name[i];
        tab_file_name[i] = tab_file_name[n_files-(i+1)];
        tab_file_name[n_files-(i+1)] = temp;

        temp = tab_directory[i];
        tab_directory[i] = tab_directory[n_files-(i+1)];
        tab_directory[n_files-(i+1)] = temp;

        i++;
    }

}
//get last modification time on a file 
size_t get_mtime(char filename[])
{
  struct stat  status;
  stat(filename, &status);
  return (status.st_mtime);
}

//sort a table by modification time
void sort_my_tab_by_mod_time(char **tab_file_name, int n_files,char ** tab_directory)
{
  int i = 0,j=0;
  char *temp = NULL;
  
  while (i < n_files)
    {
      j = 0;
      while (j < n_files)
        { 
            if (get_mtime(tab_directory[i]) > get_mtime(tab_directory[j])) // we compare last modification time and swap in conseq
            {
              temp = tab_file_name[i];
              tab_file_name[i] = tab_file_name[j];
              tab_file_name[j] = temp;
              temp = tab_directory[i];
              tab_directory[i] = tab_directory[j];
              tab_directory[j] = temp;
            }
            else if(get_mtime(tab_directory[i]) == get_mtime(tab_directory[j]))
                //if last modifications time are the same sort by alpha name
                {
                
                int breaker = 0;
                int first_strlen = my_strlen(tab_file_name[i]);
                int second_strlen = my_strlen(tab_file_name[j]);
                
                if(first_strlen<second_strlen)
                {
                    breaker = my_strlen(tab_file_name[j]);
                }
                else if (first_strlen>second_strlen)
                 {
                    breaker = my_strlen(tab_file_name[i]);
                 }
                if(my_strncmp(my_str_to_lowercase(tab_file_name[i]), my_str_to_lowercase(tab_file_name[j]),breaker) <= 0)
                {
                    temp = tab_file_name[i];
                     tab_file_name[i] = tab_file_name[j];
                     tab_file_name[j] = temp;
                     temp = tab_directory[i];
                        tab_directory[i] = tab_directory[j];
                        tab_directory[j] = temp;
                }

            }
          j++;
    }
      i++;
    }
}
