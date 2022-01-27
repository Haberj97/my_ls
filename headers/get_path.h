#ifndef _GET_PATH_
#define _GET_PATH_
#include "flags.h"
char *get_path(char dir_name[], char * path);
char ** get_all_paths(char * actual_string_path,int n_files,char ** tab_file_name);
#endif