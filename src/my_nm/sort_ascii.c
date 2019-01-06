/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** sort_ascii
*/

#include <ctype.h>
#include <stdio.h>
#include "nm.h"

int is_alphanum(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
	(c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int my_strcmp(char *str1, char *str2)
{
	int i = 0;
	int j = 0;

	while (str1[i] && str2[j]) {
		while (str1[i] && !is_alphanum(str1[i]))
			i++;
		while (str2[j] && !is_alphanum(str2[j]))
			j++;
		if (tolower(str1[i]) != tolower(str2[j]))
			break;
		i++;
		j++;
	}
	return (tolower(str1[i]) - tolower(str2[j]));
}

void swap_ptr(Elf64_Sym **symtab, int left, int right)
{
	Elf64_Sym *tmp = symtab[left];

	symtab[left] = symtab[right];
	symtab[right] = tmp;
}

void sort_ascii(Elf64_Sym **symtab, int size, char *strsymtab)
{
	char *str1;
	char *str2;
	int j;

	for (int i = 1 ; i < size ; i++) {
		j = i;
		str1 = &strsymtab[symtab[j]->st_name];
		str2 = &strsymtab[symtab[j - 1]->st_name];
		while (my_strcmp(str1, str2) < 0) {
			swap_ptr(symtab, j, j - 1);
			j--;
			if (j == 0)
				break;
			str1 = &strsymtab[symtab[j]->st_name];
			str2 = &strsymtab[symtab[j - 1]->st_name];
		}
	}
}
