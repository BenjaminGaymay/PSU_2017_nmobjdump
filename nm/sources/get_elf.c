/*
** EPITECH PROJECT, 2018
** nm
** File description:
** get_elf
*/

#include "my_nm.h"
#include <sys/mman.h>

int filesize(int fd)
{
	return (lseek(fd, 0, SEEK_END));
}

bool is_elf_file(void *datas, const char *file, unsigned int size)
{
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)datas;
	Elf64_Shdr *shdr = (Elf64_Shdr *)(datas + ehdr->e_shoff);

	if (!(IS_ELF64(ehdr->e_ident)))
		return (fprintf(stderr,
				"my_nm: %s: File format not recognized\n",
				file), false);
	if ((void *)&(shdr[0]) > (void *)datas + size)
		return (fprintf(stderr, "my_nm: %s: File truncated\n",
				file), false);
	return (true);
}

Elf64_Ehdr *get_elf_header(const char *file)
{
	int fd;
	void *datas;
	unsigned int size;

	fd = open(file, O_RDONLY);
	if (fd == OPEN_ERROR)
		return (fprintf(stderr, "my_nm: '%s': No such file\n",
				file), NULL);
	size = filesize(fd);
	datas = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
	if (datas == MAP_FAILED)
		return (perror("mmap"), NULL);
	close(fd);
	if (is_elf_file(datas, file, size) == false)
		return (NULL);
	return ((Elf64_Ehdr *)datas);
}

static t_symbol *fill_symarr(const Elf64_Shdr *shdr, const Elf64_Sym *sym,
				const Elf64_Sym *symend, char *symstr)
{
	int index = 0;
	t_symbol *symarr;

	symarr = calloc(symend - sym + 1, sizeof(*symarr));
	if (! symarr)
		return (perror("calloc"), NULL);
	while (sym && symend && sym < symend) {
		if (sym->st_info != STT_FILE &&
			sym->st_info != STT_SECTION &&
			strlen(&symstr[sym->st_name]) > 0) {
				symarr[index] = (t_symbol){sym->st_value,
					&symstr[sym->st_name],
					get_symtype(sym, shdr)};
			index++;
		}
		sym++;
	}
	return (alphanum_sort(symarr));
}

t_symbol *get_symarr(const Elf64_Ehdr *elf, const Elf64_Shdr *shdr)
{
	Elf64_Sym *sym;
	Elf64_Sym *symend;
	char *symstr = NULL;

	for (int i = 0 ; i < elf->e_shnum ; i++) {
		if (shdr[i].sh_type == SHT_SYMTAB) {
			symstr = (char *)((void *)elf +
				shdr[shdr[i].sh_link].sh_offset);
			sym = (Elf64_Sym *)((void *)elf + shdr[i].sh_offset);
			symend = (Elf64_Sym *)((void *)sym + shdr[i].sh_size);
			break;
		}
	}
	return (symstr ? fill_symarr(shdr, sym, symend, symstr) : NULL);
}
