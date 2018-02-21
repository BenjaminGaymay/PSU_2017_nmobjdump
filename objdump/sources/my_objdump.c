/*
** EPITECH PROJECT, 2018
** objdump
** File description:
** my_objdump
*/

#include "my_objdump.h"

static int start_objdump(const char *file)
{
	Elf64_Ehdr *elf;

	elf = get_elf_header(file);
	if (elf == NULL)
		return (ERROR);
	show_header(elf, (void *)elf + elf->e_shoff, file);
	show_sections(elf, (void *)elf + elf->e_shoff);
	return (SUCCESS);
}

int main(const int ac, const char **av)
{
	int ret = SUCCESS;

	if (ac == 1)
		return (start_objdump("a.out"));
	for (int i = 1 ; av[i] ; i++)
		ret = (start_objdump(av[i]) == ERROR ? ERROR : ret);
	return (ret);
}
