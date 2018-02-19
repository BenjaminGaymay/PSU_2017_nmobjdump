##
## EPITECH PROJECT, 2018
## nmobjdump
## File description:
## Makefile
##

all	:	nm objdump

nm	:
		make -C nm/

objdump	:
		make -C objdump/

clean	:
		make clean -C nm/
		make clean -C objdump/

fclean	:
		make fclean -C nm/
		make fclean -C objdump/

re	:	fclean all

.PHONY	:	nm objdump all clean fclean
