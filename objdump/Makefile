##
## EPITECH PROJECT, 2018
## nmobjdump
## File description:
## objdump Makefile
##

NAME	= my_objdump

CC	= gcc

RM	= rm -f

SRCS	=

OBJS	= $(SRCS:=.o)

CFLAGS = -I
CFLAGS += -W -Wall -Wextra

all: $(NAME)
	cp ../$(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
