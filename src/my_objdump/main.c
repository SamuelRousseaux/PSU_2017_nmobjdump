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
#include "objdump.h"

void *check_file(char *file, int *fd, struct stat *fs, Elf64_Ehdr *eh)
{
	*fd = open(file, O_RDONLY);
	if (*fd == -1) {
		fprintf(stderr, "objdump: \'%s\': No such file\n", file);
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

void *check_elf(void *eh, char *name)
{
	Elf64_Ehdr *eh64 = (Elf64_Ehdr *)eh;
	Elf32_Ehdr *eh32 = (Elf32_Ehdr *)eh;

	if (!eh32 || !eh64)
		return (NULL);
	else if ((eh32->e_ident[EI_MAG0] != ELFMAG0 ||
		eh32->e_ident[EI_MAG1] != ELFMAG1 ||
		eh32->e_ident[EI_MAG2] != ELFMAG2 ||
		eh32->e_ident[EI_MAG3] != ELFMAG3) &&
		(eh64->e_ident[EI_MAG0] != ELFMAG0 ||
		eh64->e_ident[EI_MAG1] != ELFMAG1 ||
		eh64->e_ident[EI_MAG2] != ELFMAG2 ||
		eh64->e_ident[EI_MAG3] != ELFMAG3))
		fprintf(stderr, "nm: %s: File format not recognized\n", name);
	return (eh);
}

int my_objdump(char **argv)
{
	void *eh = NULL;
	int fd;
	struct stat fs;

	for (int i = 1 ; argv[i] != NULL ; i++) {
		eh = check_file(argv[i], &fd, &fs, eh);
		if (check_elf(eh, argv[i]) == NULL)
			continue;
		if (((Elf32_Ehdr *)eh)->e_ident[EI_CLASS] == ELFCLASS32)
			objdump_32bits(eh, argv[i]);
		else if (((Elf64_Ehdr *)eh)->e_ident[EI_CLASS] == ELFCLASS64)
			objdump_64bits(eh, argv[i]);
	}
	return (0);
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		argv[1] = "a.out";
		argv[2] = NULL;
	}
	return (my_objdump(argv));
}
