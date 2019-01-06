/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** main
*/

#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "nm.h"

Elf64_Ehdr *check_file(char *file, int *fd, struct stat *fs, Elf64_Ehdr *eh)
{
	*fd = open(file, O_RDONLY);
	if (*fd == -1) {
		fprintf(stderr, "nm: \'%s\': No such file\n", file);
		return (NULL);
	}
	else if (fstat(*fd, fs) == -1) {
		fprintf(stderr, "Error: fstat failed\n");
		return (NULL);
	}
	eh = mmap(NULL, fs->st_size, PROT_READ, MAP_PRIVATE, *fd, 0);
	if (eh == MAP_FAILED) {
		fprintf(stderr, "Error: mmap failed\n");
		return (NULL);
	}
	return (eh);
}

Elf64_Ehdr *check_elf(Elf64_Ehdr *eh, char *name)
{
	if (!eh)
		return (NULL);
	else if (eh->e_ident[EI_MAG0] != ELFMAG0 ||
		eh->e_ident[EI_MAG1] != ELFMAG1 ||
		eh->e_ident[EI_MAG2] != ELFMAG2 ||
		eh->e_ident[EI_MAG3] != ELFMAG3) {
		fprintf(stderr, "nm: %s: File format not recognized\n", name);
		return (NULL);
	}
	return (eh);
}

void get_print_nm(void *data, Elf64_Sym *symtab, char *strsymtab, char *name)
{
	Elf64_Ehdr *eh = (Elf64_Ehdr *)data;
	Elf64_Shdr *sh = (Elf64_Shdr *)(data + eh->e_shoff);
	Elf64_Shdr *symsec = NULL;
	Elf64_Shdr *strsymsec = NULL;
	char *strtab = (char *)(data + sh[eh->e_shstrndx].sh_offset);

	for (int i = 0 ; i < eh->e_shnum ; i++) {
		if (!strcmp(&strtab[sh[i].sh_name], ".symtab"))
			symsec = (Elf64_Shdr *)&sh[i];
		else if (!strcmp(&strtab[sh[i].sh_name], ".strtab"))
			strsymsec = (Elf64_Shdr *)&sh[i];
	}
	if (symsec || strsymsec) {
		symtab = (Elf64_Sym *)(data + symsec->sh_offset);
		strsymtab = (char *)(data + strsymsec->sh_offset);
		print_nm(symsec, symtab, strsymtab, sh);
	}
	else
		fprintf(stderr, "nm: %s: no symbols\n", name);
}

int my_nm(int argc, char **argv)
{
	Elf64_Ehdr *eh = NULL;
	Elf64_Sym *sym_sec = NULL;
	char *strsym_sec = NULL;
	int fd;
	struct stat fs;

	for (int i = 1 ; argv[i] != NULL ; i++) {
		eh = check_file(argv[i], &fd, &fs, eh);
		if (check_elf(eh, argv[i]) == NULL)
			continue;
		if (argc > 2)
			printf("\n%s:\n", argv[i]);
		get_print_nm(eh, sym_sec, strsym_sec, argv[i]);
	}
	return (0);
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		argv[1] = "a.out";
		argv[2] = NULL;
	}
	return (my_nm(argc, argv));
}
