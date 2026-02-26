##
## EPITECH PROJECT, 2026
## FTP
## File description:
## Makefile
##


NAME	=	myftp

CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror

SRC	=	main.c \
		src/server.c \
		src/client.c \
		src/helpers.c \
		src/server_helpers.c


OBJ	=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
