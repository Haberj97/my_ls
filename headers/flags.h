#ifndef _FLAGS_
#define _FLAGS_

//struct definition
void print_help();

typedef struct Flags Flags;
struct Flags 
{
    int ls1;
    int ls_l;
    int ls_a;
    int ls_r;
    int ls_t;
    int ls_A;  
    int ls_d;
    int ls_L;
    int ls_R;
    int n_dir;  
};

void clear_flags_struct_params(Flags * params);
char ** checkFlagsParameters(int argc , char **argv , Flags * params);

#endif