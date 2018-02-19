/*
** EPITECH PROJECT, 2018
** nm
** File description:
** my_nm
*/

#include "my_nm.h"

static void show_nm(const t_symbol *symarr)
{
	for (int i = 0 ; symarr[i].name ; i++) {
		if (symarr[i].addr != 0)
			printf("%016x ", (unsigned int)symarr[i].addr);
		else
			printf("%16c ", ' ');
		printf("%c ", symarr[i].type);
		printf("%s\n", symarr[i].name);
	}
}

static int start_nm(const char *file_name, const int nb_files)
{
	Elf64_Ehdr *elf;
	t_symbol *symarr;

	elf = get_elf_header(file_name);
	if (elf == NULL)
		return (ERROR);
	symarr = get_symarr(elf, (Elf64_Shdr *)((void *)elf + elf->e_shoff));
	if (! symarr)
		return (ERROR);
	if (nb_files > 2)
		printf("\n%s:\n", file_name);
	show_nm(symarr);
	free(symarr);
	return (SUCCESS);
}

int main(const int ac, const char **av)
{
	int ret = SUCCESS;

	if (ac == 1)
		return (start_nm("a.out", ac));
	for (int i = 1 ; av[i] ; i++)
		ret = (start_nm(av[i], ac) == ERROR ? ERROR : ret);
	return (ret);
}
