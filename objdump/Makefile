NAME	= my_objdump

CC	= gcc

RM	= rm -f

SRCS	= ./sources/my_objdump.c \
	  ./sources/get_elf.c \
	  ./sources/header.c \


OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./includes/
CFLAGS += -W -Wall -Wextra

all: $(NAME)
	cp $(NAME) ../

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
