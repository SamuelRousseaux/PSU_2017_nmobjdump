/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <elf.h>

int *get_ftypes(void)
{
	static int ftypes[ET_NUM];

	ftypes[ET_NONE] = 0x0;
	ftypes[ET_REL] = 0x11;
	ftypes[ET_EXEC] = 0x112;
	ftypes[ET_DYN] = 0x150;
	ftypes[ET_CORE] = 0x0;
	return (ftypes);
}

char **get_flags(void)
{
	static char *flags[ET_NUM];

	flags[ET_NONE] = "";
	flags[ET_REL] = "HAS_RELOC, HAS_SYMS";
	flags[ET_EXEC] = "EXEC_P, HAS_SYMS, D_PAGED";
	flags[ET_DYN] = "HAS_SYMS, DYNAMIC, D_PAGED";
	flags[ET_CORE] = "";
	return (flags);
}
