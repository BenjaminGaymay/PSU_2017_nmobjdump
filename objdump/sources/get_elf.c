/*
** EPITECH PROJECT, 2018
** nm
** File description:
** get_elf
*/

#include "my_objdump.h"
#include <sys/mman.h>

static int filesize(int fd)
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
		return (dprintf(2, "objdump: '%s': No such file\n", file),
			NULL);
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

bool is_elf_file(const Elf64_Ehdr *elf)
{
	return (elf->e_ident[0] == ELFMAG0 &&
		elf->e_ident[1] == ELFMAG1 &&
		elf->e_ident[2] == ELFMAG2 &&
		elf->e_ident[3] == ELFMAG3 &&
                elf->e_ident[4] == ELFCLASS64);
}

static void print_line_datas(const Elf64_Ehdr *elf, const Elf64_Shdr *shdr,
		      int i, int index)
{
	unsigned char *data = (unsigned char *)elf + shdr[i].sh_offset + index;
	int size = shdr[i].sh_size - index;

	printf(" %04x ", (int)(shdr[i].sh_addr + index));
	for (int i = 0 ; i < 16 ; i++) {
		printf((i < size ? "%02x" : "  "), data[i]);
		if ((i + 1) % 4 == 0)
			printf(" ");
	}
	printf(" ");
	for (int i = 0 ; i < 16 ; i++) {
		if (i < size)
			printf((data[i] >= ' ' &&
				data[i] <= '~' ? "%c" : "."), data[i]);
		else
			printf(" ");
	}
	printf("\n");
}

int show_sections(const Elf64_Ehdr *elf, const Elf64_Shdr *shdr)
{
	char *strtab = (char *)((void *)elf + shdr[elf->e_shstrndx].sh_offset);
	char *section;
	unsigned int size;
	unsigned int offset;

	for (int i = 0 ; i < elf->e_shnum ; i++) {
		section = &strtab[shdr[i].sh_name];
		if (strlen(section) > 0 && (strcmp(section, ".dynstr") == 0 ||
                    GOOD_SECTION(shdr[i].sh_type))) {
			offset = shdr[i].sh_offset;
			size = offset + shdr[i].sh_size;
			printf("Contents of section %s:\n", section);
			for (unsigned int j = offset ; j < size ; j += 16)
				print_line_datas(elf, shdr, i, j - offset);
		}
	}
	return (SUCCESS);
}
