/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** 64bits
*/

#include <ctype.h>
#include <elf.h>
#include <stdio.h>
#include <string.h>
#include "objdump.h"

static t_arch architectures[] = {
	{ EM_NONE, "none" },
	{ EM_386, "Intel 80836" },
	{ EM_860, "Intel 80860" },
	{ EM_PPC, "PowerPC" },
	{ EM_PPC64, "PowerPC64" },
	{ EM_ARM, "ARM" },
	{ EM_IA_64, "Intel IA-64" },
	{ EM_X86_64, "i386:x86-64" }
};

static char *sec[] = { ".strtab", ".symtab", ".shstrtab", ".bss" };

char *return_arch32(Elf32_Ehdr *eh)
{
	int arch_len = 8;

	for (int i = 0 ; i < arch_len ; i++) {
		if (architectures[i].type == eh->e_machine)
			return (architectures[i].name);
	}
	return ("unknown");
}

void print_dump_bis_32(unsigned int i, unsigned int *j, unsigned char *stru,
			char *str)
{
	char tmp;

	for (int x = i ; x % 16 ; ++x) {
		if (!(x % 4) && x % 16)
			printf(" ");
		printf("  ");
	}
	printf("  ");
	for (*j = *j ; *j < i ; (*j)++) {
		tmp = isprint(stru[*j]) ? str[*j] : '.';
		printf("%c", tmp);
	}
	while ((*j)++ % 16)
		printf(" ");
	*j = i;
	printf("\n");
}

void print_dump_32(Elf32_Ehdr *eh, Elf32_Shdr sh)
{
	int add = sh.sh_addr;
	unsigned char *str = (unsigned char *)((char *)eh + sh.sh_offset);
	unsigned int j = 0;

	for (unsigned int i = 0 ; i < sh.sh_size ; (void)i) {
		if (!(i % 16))
			printf(" %04x ", add);
		printf("%02x", str[i++]);
		if (!(i % 4) && i % 16 && i < sh.sh_size)
			printf(" ");
		else if (i >= sh.sh_size)
			print_dump_bis_32(i, &j, str, (char *)str);
		else {
			if (!(i % 16)) {
				add += 16;
				print_dump_bis_32(i, &j, str, (char *)str);
			}
		}
	}
}

void print_objd_32(Elf32_Ehdr *eh, Elf32_Shdr *sh, char *strtab)
{
	int is_ok = 0;
	char *sec_name;

	for (int i = 0 ; i < eh->e_shnum ; i++) {
		is_ok = 1;
		for (int j = 0 ; j < 4 ; j++)
			if (!strcmp(&strtab[sh[i].sh_name], sec[j]) ||
			!sh[i].sh_size)
				is_ok = 0;
		if (is_ok) {
			sec_name = &strtab[sh[i].sh_name];
			printf("Contents of section %s:\n", sec_name);
			print_dump_32(eh, sh[i]);
		}
	}
}

void objdump_32bits(void *data, char *name)
{
	Elf32_Ehdr *eh = (Elf32_Ehdr *)data;
	Elf32_Shdr *sh = (Elf32_Shdr *)(data + eh->e_shoff);
	char *strtab = (char *)(data + sh[eh->e_shstrndx].sh_offset);
	int *ftypes = get_ftypes();
	char **flags = get_flags();

	printf("\n%s:%5cfile format elf32-x86-64\n", name, ' ');
	printf("architecture: %s, ", return_arch32(eh));
	if (eh->e_type < ET_NUM) {
		printf("flags 0x%08x:\n", ftypes[eh->e_type]);
		printf("%s\n", flags[eh->e_type]);
	}
	printf("start address 0x%016x\n\n", eh->e_entry);
	print_objd_32(eh, sh, strtab);
}
