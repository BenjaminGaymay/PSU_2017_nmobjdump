NAME	= my_nm

CC	= gcc

RM	= rm -f

SRCS	= ./sources/my_nm.c \
	  ./sources/sort.c \
	  ./sources/types.c \
	  ./sources/get_elf.c \

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
