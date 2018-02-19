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

Elf64_Ehdr *get_elf_header(const char *file)
{
	int fd;
	void *datas;
	Elf64_Ehdr *elf;

	fd = open(file, O_RDONLY);
	if (fd == OPEN_ERROR)
		return (dprintf(2, "objdump: '%s': No such file\n", file), NULL);
	datas = mmap(NULL, filesize(fd), PROT_READ, MAP_SHARED, fd, 0);
	if (datas == MAP_FAILED)
		return (perror("mmap"), NULL);
	elf = (Elf64_Ehdr *)datas;
	close(fd);
	if (is_elf_file(elf) == false) {
		dprintf(2, "objdump: %s: File format not recognized\n", file);
		return (NULL);
	}
	return (elf);
}

bool is_elf_file(const Elf64_Ehdr *ehdr)
{
	return (ehdr->e_ident[0] == ELFMAG0 &&
                ehdr->e_ident[1] == ELFMAG1 &&
                ehdr->e_ident[2] == ELFMAG2 &&
                ehdr->e_ident[3] == ELFMAG3);
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
			if (! symarr)
				return (NULL);
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
			symend = (Elf64_Sym *)((void *)sym +
					       shdr[i].sh_size);
			break;
		}
	}
	return (symstr ? fill_symarr(shdr, sym, symend, symstr) : NULL);
}
