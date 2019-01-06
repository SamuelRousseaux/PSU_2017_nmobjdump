/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** get_flag
*/

#include "nm.h"

static t_flags gflags[] = {
	{ STT_NOTYPE, SHT_PROGBITS, 3, 'D' },
	{ STT_OBJECT, SHT_PROGBITS, 3, 'D' },
	{ STT_NOTYPE, SHT_PROGBITS, 2, 'R' },
	{ STT_OBJECT, SHT_PROGBITS, 2, 'R' },
	{ STT_OBJECT, SHT_PROGBITS, 18, 'R' },
	{ STT_NOTYPE, SHT_NOBITS, 3, 'B' },
	{ STT_OBJECT, SHT_NOBITS, 3, 'B' },
	{ STT_FUNC, SHT_NULL, 0, 'U' },
	{ STT_FUNC, SHT_PROGBITS, 6, 'T' },
	{ STT_LOOS, SHT_PROGBITS, 6, 'i' }
};

static t_flags lflags[] = {
	{ STT_NOTYPE, SHT_PROGBITS, 0, 'n' },
	{ STT_NOTYPE, SHT_PROGBITS, 2, 'r' },
	{ STT_NOTYPE, SHT_PROGBITS, 50, 'r' },
	{ STT_NOTYPE, SHT_PROGBITS, 3, 'd' },
	{ STT_NOTYPE, SHT_PROGBITS, 6, 't' },
	{ STT_NOTYPE, SHT_NOBITS, 3, 'b' },
	{ STT_OBJECT, SHT_DYNAMIC, 3, 'd' },
	{ STT_OBJECT, SHT_NOTE, 2, 'r' },
	{ STT_NOTYPE, SHT_INIT_ARRAY, 3, 't' },
	{ STT_OBJECT, SHT_FINI_ARRAY, 3, 't' },
	{ STT_OBJECT, SHT_INIT_ARRAY, 3, 't' },
	{ STT_OBJECT, SHT_PROGBITS, 0, 'n' },
	{ STT_OBJECT, SHT_PROGBITS, 2, 'r' },
	{ STT_OBJECT, SHT_PROGBITS, 50, 'r' },
	{ STT_OBJECT, SHT_PROGBITS, 3, 'd' },
	{ STT_OBJECT, SHT_NOBITS, 3, 'b' },
	{ STT_FUNC, SHT_PROGBITS, 6, 't' },
	{ STT_TLS, SHT_PROGBITS, 1027, 'd' },
	{ STT_TLS, SHT_NOBITS, 1027, 'b' },
	{ STT_LOOS, SHT_PROGBITS, 6, 'i' }
};

char global_sym(Elf64_Sym *symtab, Elf64_Shdr *sh, char bind, char type)
{
	int gflags_len = 10;
	Elf64_Shdr sh_symtab = sh[symtab->st_shndx];

	if (bind == STB_GLOBAL) {
		for (int i = 0 ; i < gflags_len ; i++) {
			if (type == gflags[i].st_type &&
			sh_symtab.sh_type == gflags[i].sh_type &&
			sh_symtab.sh_flags == gflags[i].sh_flags)
				return (gflags[i].flag);
		}
		return ('U');
	}
	return ('?');
}

char local_sym(Elf64_Sym *symtab, Elf64_Shdr *sh, char bind, char type)
{
	int lflags_len = 20;
	Elf64_Shdr sh_symtab = sh[symtab->st_shndx];

	if (bind == STB_LOCAL) {
		for (int i = 0 ; i < lflags_len ; i++) {
			if (type == lflags[i].st_type &&
			sh_symtab.sh_type == lflags[i].sh_type &&
			sh_symtab.sh_flags == lflags[i].sh_flags)
				return (lflags[i].flag);
		}
		return ('U');
	}
	return ('?');
}

char weak_sym(Elf64_Sym *symtab, char bind, char type)
{
	if (bind == STB_WEAK) {
		if (type == STT_OBJECT)
			return (symtab->st_shndx == SHN_UNDEF ? 'v' : 'V');
		else
			return (symtab->st_shndx == SHN_UNDEF ? 'w' : 'W');
	}
	return ('?');
}

char other_flags(Elf64_Sym *symtab, char bind, char type)
{
	if (bind == STB_GLOBAL && type == STT_OBJECT &&
	symtab->st_shndx == SHN_COMMON)
		return ('C');
	if (bind == STB_GNU_UNIQUE)
		return ('U');
	return ('?');
}

char get_flag(Elf64_Sym *symtab, Elf64_Shdr *sh)
{
	char bind = ELF64_ST_BIND(symtab->st_info);
	char type = ELF64_ST_TYPE(symtab->st_info);
	char flag = other_flags(symtab, bind, type);

	if (flag != '?')
		return (flag);
	if (symtab->st_shndx != SHN_ABS && symtab->st_shndx != SHN_COMMON) {
		flag = global_sym(symtab, sh, bind, type);
		if (flag != '?')
			return (flag);
		flag = local_sym(symtab, sh, bind, type);
		if (flag != '?')
			return (flag);
	}
	flag = weak_sym(symtab, bind, type);
	if (flag != '?')
		return (flag);
	if (flag != '?' && symtab->st_shndx == SHN_ABS)
		return (bind == STB_LOCAL ? 'a' : 'A');
	return ('?');
}
