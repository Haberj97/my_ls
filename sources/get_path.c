/*
**
** ETNA PROJECT, 01/2022 by habert_j && hamia_r
** get_path
** File description: functions used to recovering path from a string or a table of strings
** entered in the command line by the user.
**
*/
#include "../headers/extlib.h"
#include "../headers/libmy.h"

//recovering path from a string 
char *get_path(char dir_name[], char * path)
{
  char *dir_path = NULL;
  int size = 0,i=0;
  i = my_strlen(path);
  size = i + my_strlen(dir_name);
  dir_path = malloc(size* sizeof(char*));
  dir_path = path;
  if (dir_path[i-1] != '/')
      dir_path = my_strcat(dir_path,"/");
  i++;  
  return my_strcat(dir_path, dir_name);
}
//recovering paths[] from a tables of strings 
char ** get_all_paths(char * actual_string_path,int n_files,char ** tab_file_name)
{
  char ** path = NULL;
  int i = 0;
  path = malloc(sizeof(char *)*n_files);
  while (i< n_files)
    {
        path[i] = get_path(tab_file_name[i], actual_string_path);
        i++;
    }
  return path;
}