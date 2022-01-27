/*
** ETNA PROJECT, 01/2022 by habert_j && hamia_r
** my_ls_l
** File description:
**      this function is ls whit flag l that list complete informations of targeted folder/file
*/

#include "../headers/extlib.h"
#include "../headers/libmy.h"
#include "../headers/flags.h"
#include "../headers/my_colored_output.h"

// function used to print right of the targeted file/folder for 
void print_file_right(struct stat *st) 
{
    switch (st->st_mode & S_IFMT)  //switch case for find type of file exemple d for directory or l for symlink 
    {
        case S_IFBLK:  
            my_putstr("b"); 
            break;
        case S_IFCHR:  
            my_putstr("c"); 
            break;
        case S_IFDIR:
            my_putstr("d");
            break;
        case S_IFIFO:
            my_putstr("p");
            break;
        case S_IFLNK:
            my_putstr("l");
            break;
        case S_IFREG:
            my_putstr("-");
            break;
        case S_IFSOCK:
            my_putstr("s");
            break;
        default:
            my_putstr("?");
            break;
    }

  my_putstr(st->st_mode & S_IRUSR ? "r" : "-"); // read usr right
  my_putstr(st->st_mode & S_IWUSR ? "w" : "-"); // write usr right
  my_putstr(st->st_mode & S_IXUSR ? "x" : "-"); // exec usr right
  my_putstr(st->st_mode & S_IRGRP ? "r" : "-"); // read group right
  my_putstr(st->st_mode & S_IWGRP ? "w" : "-"); // write group right 
  my_putstr(st->st_mode & S_IXGRP ? "x" : "-"); // exec group right
  my_putstr(st->st_mode & S_IROTH ? "r" : "-"); // read oth right 
  my_putstr(st->st_mode & S_IWOTH ? "w" : "-"); // write oth right
  my_putstr(st->st_mode & S_IXOTH ? "x" : "-"); // oth exec right 
}
//count the total of blocks for be able to dislay this 
void count_total_of_block(int * total, char ** path , int n_files ,Flags * params)
{
    struct stat st;
    int counter = 0;
    for(int i = 0; i < n_files;i++)
    {
        //if -L use stat if not lstat
        if(params->ls_L == 0 ? lstat(path[i], &st) == 0 : stat(path[i],&st) == 0)
			counter += st.st_blocks;
    }
    *total = counter/2;
}

//count digit of a number exemple for 342 we can see 3 digit 
int * count_nbr_digit(int nbr , int * n_times)
{
    if (nbr>9) //if number is greater than 9 use recursivity
        {
            *n_times = *n_times +1 ;
            count_nbr_digit(nbr/10,n_times);
        }
    else
    {
        *n_times = *n_times +1 ;
    }
    return n_times;
}
// used to check the number with more digit foreach table and modify values in function of that
int check_max_digit(int n_files,char ** path,int * max_digit_sz,Flags * params)
{
    struct stat st;
    int max_digit_nlink = 0,nbr_max_nlink = 0,nbr_max_sz = 0;

    count_nbr_digit(nbr_max_nlink,&max_digit_nlink);
    count_nbr_digit(nbr_max_sz,max_digit_sz);
    
    for(int i = 0;i< n_files;i++)
    {
        //if -L == 0 use lstat else stat
        if (params->ls_L == 0 ? lstat(path[i], &st) == -1 : stat(path[i], &st) == -1)
        {   
            //catch error
            perror("stat");
            exit(EXIT_FAILURE);
        }
        else
        {
            //check for max_number between two values
            int n_times_actual = 0;
            count_nbr_digit(st.st_nlink,&n_times_actual);
            if(n_times_actual>max_digit_nlink)
            {
                max_digit_nlink=n_times_actual;
                nbr_max_nlink = st.st_nlink;
            }
        }
    }
    //similare to the first for but is another table 
    for(int i = 0;i< n_files;i++)
    {
        if (params->ls_L == 0 ? lstat(path[i], &st) == -1 : stat(path[i], &st) == -1)
        {   
            perror("stat");
            exit(EXIT_FAILURE);
        }
        else
        {
            int n_times_actual_sz = 0;
            count_nbr_digit(st.st_size,&n_times_actual_sz);
            if(n_times_actual_sz>*max_digit_sz)
            {
                *max_digit_sz =n_times_actual_sz;
                nbr_max_sz = st.st_size;
            }
        }
    }
    return max_digit_nlink;
}
//function for recover strlen of the longer word in a table 
void max_strlen(int n_files,char ** path,int * max_pw_name_strlen,int * max_gr_name_strlen,Flags * params)
{
    struct stat st;
    struct passwd *passwd;
    struct group  *group;
    
    for(int i = 0; i< n_files;i++)
    {
        //if -L use stat else lstat 
        if (params->ls_L == 0 ? lstat(path[i], &st) == -1 : stat(path[i], &st) == -1 )
        {   
            perror("stat"); // catch error 
            exit(EXIT_FAILURE);
        }
        else
        {
            passwd = getpwuid(st.st_uid); //recovering usrName
            group = getgrgid(st.st_gid); // recovering groupe name 
            
            int actual_pw_name_strlen = my_strlen(passwd->pw_name); // strlen usrName
            int actual_gr_name_strlen = my_strlen(group->gr_name); // strlen groupeName
            //comparate last greater strlen of usr name with actual
            if(actual_pw_name_strlen> *max_pw_name_strlen)
            {
                *max_pw_name_strlen = actual_pw_name_strlen;
            }
            //same for groupeName
            if(actual_gr_name_strlen>*max_gr_name_strlen)
            {
                *max_gr_name_strlen = actual_gr_name_strlen;
            }
        }
    }
}

void print_stat(char **filename , int n_files , char ** path,Flags * params)
{
    int total = 0, max_digit_sz = 0, i=0, max_pw_name_strlen=0, max_gr_name_strlen = 0;

    struct stat st; // create a stat to recover informations
    
    int max_digit_nlink = check_max_digit(n_files,path,&max_digit_sz,params);

    max_strlen(n_files,path,&max_pw_name_strlen,&max_gr_name_strlen,params);

    struct passwd *passwd; // create a pointer type passwd to access to pw_name
    struct group  *group; // create a pointer type grp to recover groupe name
    
    //print total block if more than 1 files 
    if(n_files>1)
    {
        count_total_of_block(&total,path,n_files,params);
        my_putstr("total ");
        my_putnbr(total);
        my_putchar('\n');
    }
    
    while(i< n_files)
    {
        //if -L use stat else lstat
        if (params->ls_L == 0 ? lstat(path[i], &st) == -1 : stat(path[i], &st)== -1)
        {   
            perror("stat"); //catch unexpected error
            exit(EXIT_FAILURE);
        }
        else
        {
            print_file_right(&st);
            
            int digit_actual_nlink = 0;
            //count nb digit to manage space in the second colomn 2 that display hard link
            count_nbr_digit(st.st_nlink,&digit_actual_nlink);   
            
            while(digit_actual_nlink<=max_digit_nlink)
            {
                my_putstr(" ");
                digit_actual_nlink ++;
            }

            my_putnbr(st.st_nlink); /* number of hard links */
            
            //containing the broken-out fields of the record in 
            //the password database that matches the user ID uid
            passwd = getpwuid(st.st_uid);
            group = getgrgid(st.st_gid);

            int actual_pw_name_strlen = my_strlen(passwd->pw_name);

            my_putchar(' ');
            my_putstr(passwd->pw_name); // recovering /* username */
            //managing space in function of strlen for username
            while(actual_pw_name_strlen<=max_pw_name_strlen)
            {
                my_putchar(' ');
                actual_pw_name_strlen ++;
            }
           
            my_putstr(group->gr_name); // recovering /* group name */

            int actual_gr_name_strlen = my_strlen(group->gr_name);
            //managing space in function of strlen for grp name 
            while(actual_gr_name_strlen<=max_gr_name_strlen)
            {
                my_putchar(' ');
                actual_gr_name_strlen ++;
            }

            int digit_actual_sz = 0;

            count_nbr_digit(st.st_size,&digit_actual_sz);
            //managing space in function of nb of git on field size
            while(digit_actual_sz<=max_digit_sz)
            {
                my_putstr(" ");
                digit_actual_sz ++;
            }
            
            my_putnbr(st.st_size); // recovering
            my_putstr("  ");
            //ctime to recover modification time 
            char * tab = ctime(&(st.st_mtime));
            
            for(int i=0;tab[i] != '\n';i++)
            {
                if(i>3 && i<16)
                {
                    my_putchar(tab[i]);
                }
            }
            
            my_putstr("  ");

            //file name
            my_colored_output(filename[i],path[i],params);
            //my_putstr(filename[i]);
            
            if(params->ls_L == 0)
                {
                    char *linkname = NULL;
                    size_t r;

                    linkname = malloc(st.st_size + 1);

                    if (linkname == NULL)//catch memory issues
                        {
                            fprintf(stderr, "mémoire insuffisante\n");
                            exit(EXIT_FAILURE);
                        }
                    
                    //use read link to read symlink location 
                    r = readlink(path[i], linkname, st.st_size + 1);
                    linkname[r] = '\0'; //adding end of string
                    
                    //checking if is a real symlink 
                    if(my_strlen(linkname)>6 && (my_strncmp(linkname,"root:x:0",8)!=0))
                        {
                            my_putstr(" -> ");
                            my_putstr(linkname);
                        }
                    //free memory used to stock the string 
                    free(linkname);
                }
                my_putstr("\n");
        }
        i++;
    }
}
