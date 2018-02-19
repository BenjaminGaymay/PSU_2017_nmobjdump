/*
** EPITECH PROJECT, 2018
** nm
** File description:
** types
*/

#include "my_nm.h"

static char checktype_shdr(const Elf64_Sym *sym, const Elf64_Shdr *shdr)
{
	static t_type_info arr[] = {
		{'B', SHT_NOBITS, (SHF_ALLOC | SHF_WRITE)},
		{'R', SHT_PROGBITS, SHF_ALLOC},
		{'D', SHT_PROGBITS, (SHF_ALLOC | SHF_WRITE)},
		{'T', SHT_PROGBITS, (SHF_ALLOC | SHF_EXECINSTR)},
		{'D', SHT_DYNAMIC, (SHF_ALLOC | SHF_EXECINSTR)},
		{'\0'}
	};

	for (int i = 0 ; arr[i].type ; i++) {
		if (shdr[sym->st_shndx].sh_type == (unsigned int)arr[i].fst &&
		    shdr[sym->st_shndx].sh_flags == (unsigned int)arr[i].sec)
			return (arr[i].type);
	}
	return (shdr[sym->st_shndx].sh_type == SHT_DYNAMIC ? 'D' : 't');
}


static char checktype_shndx(const Elf64_Sym *sym, const Elf64_Shdr *shdr)
{
	static t_type_info arr[] = {
		{'U', SHN_UNDEF, SHN_UNDEF},
		{'A', SHN_ABS, SHN_ABS},
		{'C', SHN_COMMON, SHN_COMMON},
		{'\0'}
	};

	for (int i = 0 ; arr[i].type ; i++) {
		if (sym->st_shndx == arr[i].fst)
			return (arr[i].type);
	}
	return (checktype_shdr(sym, shdr));
}

static char checktype_info(const Elf64_Sym *sym, const Elf64_Shdr *shdr)
{
	static t_type_info arr[] = {
		{'u', STB_GNU_UNIQUE, STB_GNU_UNIQUE},
		{'W', STB_WEAK, STB_WEAK},
		{'V', STB_WEAK, STT_OBJECT},
		{'\0'}
	};

	for (int i = 0 ; arr[i].type ; i++) {
		if (ELF64_ST_BIND(sym->st_info) == arr[i].fst &&
		    ELF64_ST_BIND(sym->st_info) == arr[i].sec)
			return (arr[i].type);
	}
	return (checktype_shndx(sym, shdr));
}


char get_symtype(const Elf64_Sym *sym, const Elf64_Shdr *shdr)
{
	char type = checktype_info(sym, shdr);

	if (((type == 'V' || type == 'W') &&
	     sym->st_shndx == SHN_UNDEF) ||
	    (type != 't' &&
	     ELF64_ST_BIND(sym->st_info) == STB_LOCAL))
		type += 32;
	return (type);
}
