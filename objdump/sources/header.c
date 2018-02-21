/*
** EPITECH PROJECT, 2018
** objdump
** File description:
** header
*/

#include <stdio.h>
#include "my_objdump.h"
#include "flags.h"

static int get_flags(const Elf64_Ehdr *elf, const Elf64_Shdr *shdr, char **str)
{
	int flags = 0;

	for (int i = 0 ; i < elf->e_shnum ; i++) {
		if (shdr[i].sh_type == SHT_REL || shdr[i].sh_type == SHT_RELA)
			flags |= HAS_RELOC;
	}
	if (elf->e_type == ET_EXEC) {
		flags = (flags & ~HAS_RELOC) | (EXEC_P | D_PAGED);
		*str =  "HAS_RELOC, EXEC_P, D_PAGED";
	}
	if (elf->e_type == ET_DYN) {
		flags = (flags & ~HAS_RELOC) | (DYNAMIC | D_PAGED);
		*str =  "HAS_SYMS, DYNAMIC, D_PAGED";
	}
	return (flags | HAS_SYMS);
}

static const char *find_machine(uint16_t id)
{
	for (int i = 0 ; machine[i].name ; i++) {
		if (machine[i].id == id)
			return (machine[i].name);
	}
	return ("unknown");
}

void show_header(const Elf64_Ehdr *elf, const Elf64_Shdr *shdr,
		 const char *file)
{
	char *str = NULL;

	printf("\n%s:     file format elf64-x86-64\n", file);
	printf("architecture: %s, ", find_machine(elf->e_machine));
	printf("flags 0x%08x:\n", get_flags(elf, shdr, &str));
	printf("%s\nstart address 0x%016lx\n\n", str, elf->e_entry);
}
