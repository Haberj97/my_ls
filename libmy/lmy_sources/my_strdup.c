#include "../lmy_headers/my_strlen.h"
#include "../lmy_headers/my_strcpy.h"
#include <stdlib.h>
char *my_strdup(char *src)
{
	char *dest;
	dest = malloc(sizeof(char) * (my_strlen(src) + 1));
	dest = my_strcpy(dest, src);
	return (dest);
}