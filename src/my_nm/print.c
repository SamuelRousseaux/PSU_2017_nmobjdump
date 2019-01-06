/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** print
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "nm.h"

Elf64_Sym **copy_symtab(Elf64_Sym *symtab, size_t size)
{
	Elf64_Sym **new = malloc(sizeof(Elf64_Sym *) * (size + 1));

	if (new == NULL)
		return (NULL);
	for (unsigned int i = 0 ; i < size ; i++)
		new[i] = &symtab[i];
	return (new);
}

void print_line(Elf64_Sym **symtab_cpy, char *strsymtab,
		Elf64_Shdr *sh, int i)
{
	char type;

	if (symtab_cpy[i]->st_info != 4) {
		type = get_flag(symtab_cpy[i], sh);
		if (type != 'U' && type != 'w')
			printf("%016x ", (uint32_t)(symtab_cpy[i]->st_value));
		else
			printf("%17c", ' ');
		printf("%c %s\n", type, &strsymtab[symtab_cpy[i]->st_name]);
	}
}

void print_nm(Elf64_Shdr *symsection, Elf64_Sym *symtab,
		char *strsymtab, Elf64_Shdr *sh)
{
	unsigned int size = symsection->sh_size / sizeof(*symtab);
	Elf64_Sym **symtab_cpy = copy_symtab(symtab, size);
	size_t stname;

	if (symtab_cpy == NULL) {
		fprintf(stderr, "error: malloc: failed.\n");
		return;
	}
	sort_ascii(symtab_cpy, size, strsymtab);
	for (unsigned int i = 0 ; i < size ; i++) {
		stname = symtab_cpy[i]->st_name;
		if (stname != 0 && stname != 1)
			print_line(symtab_cpy, strsymtab, sh, i);
	}
	free(symtab_cpy);
}
