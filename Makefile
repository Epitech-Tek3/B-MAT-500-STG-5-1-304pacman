##
## EPITECH PROJECT, 2021
## B-MAT-500-STG-5-1-304pacman-clement.muth
## File description:
## Makefile
##

SRC		=	 main.cpp

CFLAGS	=	-std=gnu11 -Wall -Wextra -I include

OBJ		=	$(SRC:.cpp=.o)

INCLUDE	=	-o

LIB		=	-g -lm

NAME	=	304pacman

all:	$(NAME)

$(NAME):$(OBJ)
	g++ $(OBJ) $(CFLAGS) $(INCLUDE) $(NAME) $(LIB)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re