/*
** EPITECH PROJECT, 2018
** nm
** File description:
** my_nm
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
# define IS_ELF64(e_ident) (e_ident[0] == ELFMAG0 &&	\
			    e_ident[1] == ELFMAG1 &&	\
			    e_ident[2] == ELFMAG2 &&	\
			    e_ident[3] == ELFMAG3 &&	\
			    e_ident[4] == ELFCLASS64)

typedef struct s_symbol {
	long unsigned int addr;
	char *name;
	char type;
} t_symbol;

typedef struct s_type_info {
	char type;
	int fst;
	int sec;
} t_type_info;

t_symbol *alphanum_sort(t_symbol *);
Elf64_Ehdr *get_elf_header(const char *);
char get_symtype(const Elf64_Sym *, const Elf64_Shdr *);
t_symbol *get_symarr(const Elf64_Ehdr *, const Elf64_Shdr *);
