CC = gcc
NAME = my_ls
SRC = sources/main.c \
		sources/my_ls_base.c \
		sources/flags_management.c \
		sources/tab_sorting.c \
		sources/tab_filling.c \
		sources/tab_printing.c \
		sources/get_path.c \
		sources/my_ls_l.c \
		sources/my_ls_R.c \
		sources/dir_traitement.c \
		sources/my_colored_output.c
OBJ = $(SRC:%.c=%.o)
RM = rm -f
TMP = rm -f *.c~ Makefile~ *.h~ *.o
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L. -lmy
$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
all:		$(NAME)
tclean:
			$(TMP)
clean:
			$(RM) $(OBJ)
			$(TMP)
fclean:	clean
			$(RM) $(NAME)
re:		fclean all


