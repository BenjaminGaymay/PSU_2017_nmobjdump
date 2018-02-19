#include <stdio.h>
#include "my_objdump.h"
#include "flags.h"

typedef struct s_arch {
        uint16_t id;
        const char *str;
} t_arch;

static const t_arch arch[] =
{
        {EM_M32, "WE32100"},
        {EM_SPARC, "Sparc"},
        {EM_386, "Intel 80386"},
        {EM_68K, "MC68000"},
        {EM_88K, "MC88000"},
        {EM_860, "Intel 80860"},
        {EM_MIPS, "MIPS R3000"},
        {EM_PARISC, "HPPA"},
        {EM_SPARC32PLUS, "Sparc v8+"},
        {EM_PPC, "PowerPC"},
        {EM_PPC64, "PowerPC64"},
        {EM_S390, "IBM S/390"},
        {EM_ARM, "ARM"},
        {EM_SH, "Renesas / SuperH SH"},
        {EM_SPARCV9, "Sparc v9"},
        {EM_IA_64, "Intel IA-64"},
        {EM_X86_64, "i386:x86-64"}
};


int display_flags(const Elf64_Ehdr *elf, const Elf64_Shdr *shdr, char **str)
{
    int flags = 0;

    for (int i = 0; i < elf->e_shnum; i++) {
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

const char *array_asso(uint16_t id)
{
    int i = 0;

    while (arch[i].str != NULL) {
        if (arch[i].id == id)
            return (arch[i].str);
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
    printf("architecture: %s, ", array_asso(elf->e_machine));
    flags = display_flags(elf, shdr, &str);
    printf("flags 0x%08x:\n%s\n", flags, str);
    printf("start address 0x%016lx\n", elf->e_entry);
    printf("\n");
}
