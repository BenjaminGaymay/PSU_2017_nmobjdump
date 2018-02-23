/*
** EPITECH PROJECT, 2018
** objdump
** File description:
** my_objdump
*/

#pragma once

#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

# define SUCCESS 0
# define FAILURE 1
# define ERROR 84
# define OPEN_ERROR -1
# define IS_ELF64(e_ident) (e_ident[0] == ELFMAG0 &&		\
				e_ident[1] == ELFMAG1 &&	\
				e_ident[2] == ELFMAG2 &&	\
				e_ident[3] == ELFMAG3 &&	\
				e_ident[4] == ELFCLASS64)
# define GOOD_SECTION(type) ((type) != SHT_SYMTAB &&	\
				(type) != SHT_STRTAB &&	\
				(type) != SHT_NOBITS)

typedef struct s_arch {
	uint16_t id;
	const char *name;
} t_arch;

static const t_arch g_arch[] =
{
	{EM_M32, "AT&T WE 32100"},
	{EM_SPARC, "Sun Microsystems SPARC"},
	{EM_386, "Intel 80386"},
	{EM_68K, "Motorola 68000"},
	{EM_88K, "Motorola 88000"},
	{EM_860, "Intel 80860"},
	{EM_MIPS, "MIPS RS3000"},
	{EM_PARISC, "HP/PA"},
	{EM_SPARC32PLUS, "SPARC"},
	{EM_PPC, "PowerPC"},
	{EM_PPC64, "PowerPC 64-bit"},
	{EM_S390, "IBM S/390"},
	{EM_ARM, "Advanced RISC Machines"},
	{EM_SH, "Renesas SuperH"},
	{EM_SPARCV9, "SPARC v9 64-bit"},
	{EM_IA_64, "Intel Itanium"},
	{EM_X86_64, "i386:x86-64"},
	{EM_VAX, "DEC Vax"},
	{EM_NONE, "unknown"}
};

Elf64_Ehdr *get_elf_header(const char *);
int show_sections(const Elf64_Ehdr *, const Elf64_Shdr *);
void show_header(const Elf64_Ehdr *, const Elf64_Shdr *, const char *);
