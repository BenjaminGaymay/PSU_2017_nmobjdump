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
# define GOOD_SECTION(type) ((type) != SHT_SYMTAB && \
                             (type) != SHT_STRTAB && \
                             (type) != SHT_NOBITS)

typedef struct s_machine {
        uint16_t id;
        const char *name;
} t_machine;

bool is_elf_file(const Elf64_Ehdr *);
Elf64_Ehdr *get_elf_header(const char *);
int show_sections(const Elf64_Ehdr *, const Elf64_Shdr *);
void show_header(const Elf64_Ehdr *, const Elf64_Shdr *, const char *);
