##
## EPITECH PROJECT, 2018
## *
## File description:
## *
##

NAME_NM	=	my_nm

NAME_OB	=	my_objdump

CC	=	gcc

CFLAGS	=	-W -Wall -Wextra -I./inc

SRC_NM	=	src/my_nm/get_flag.c	\
		src/my_nm/main.c	\
		src/my_nm/print.c	\
		src/my_nm/sort_ascii.c

SRC_OB	=	src/my_objdump/get_flags.c	\
		src/my_objdump/main.c		\
		src/my_objdump/objdump64.c	\
		src/my_objdump/objdump32.c

OBJ_NM	=	$(SRC_NM:.c=.o)

OBJ_OB	=	$(SRC_OB:.c=.o)

all:	nm objdump

nm:	$(NAME_NM)

objdump:	$(NAME_OB)

$(NAME_NM):	$(OBJ_NM)
	$(CC) -o $(NAME_NM) $(OBJ_NM)

$(NAME_OB):	$(OBJ_OB)
	$(CC) -o $(NAME_OB) $(OBJ_OB)

clean:
	$(RM) $(OBJ_NM) $(OBJ_OB)

fclean:	clean
	$(RM) $(NAME_NM) $(NAME_OB)

re:	fclean all

.PHONY:	all clean fclean re nm objdump
