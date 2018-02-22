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
	char *sec;
	unsigned int size;
	unsigned int offset;

	for (int i = 0 ; i < elf->e_shnum ; i++) {
		sec = &strtab[shdr[i].sh_name];
		if (strlen(sec) > 0 && (strcmp(sec, ".dynstr") == 0 ||
                    GOOD_SECTION(shdr[i].sh_type))) {
			offset = shdr[i].sh_offset;
			size = offset + shdr[i].sh_size;
			printf("Contents of section %s:\n", sec);
			for (unsigned int j = offset ; j < size ; j += 16)
				print_line_datas(elf, shdr, i, j - offset);
		}
	}
	return (SUCCESS);
}
