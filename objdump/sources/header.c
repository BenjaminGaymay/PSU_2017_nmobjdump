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
        flags &= ~HAS_RELOC;
        flags |= EXEC_P | D_PAGED;
        *str =  "HAS_RELOC, EXEC_P, D_PAGED";
    }
    if (elf->e_type == ET_DYN) {
        flags &= ~HAS_RELOC;
        flags |= DYNAMIC | D_PAGED;
        *str =  "HAS_SYMS, DYNAMIC, D_PAGED";
    }
    flags |= HAS_SYMS;
    return (flags);
}

static const char *find_machine(uint16_t id)
{
    static t_machine machine[] =
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

    for (int i = 0 ; machine[i].name ; i++) {
        if (machine[i].id == id)
            return (machine[i].name);
        i++;
    }
    return (NULL);
}

void show_header(const Elf64_Ehdr *elf, const Elf64_Shdr *shdr, const char *file)
{
    char *str = NULL;
    int flags = 0;

    printf("\n");
    printf("%s:     file format elf64-x86-64\n", file);
    printf("architecture: %s, ", find_machine(elf->e_machine));
    flags = get_flags(elf, shdr, &str);
    printf("flags 0x%08x:\n%s\n", flags, str);
    printf("start address 0x%016lx\n", elf->e_entry);
    printf("\n");
}
