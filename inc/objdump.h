/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** objd header
*/

#ifndef OBJDUMP_H_
# define OBJDUMP_H_

typedef struct	arch_s
{
	size_t	type;
	char	*name;
}		t_arch;

int *get_ftypes();
char **get_flags();
void objdump_64bits(void *, char *);
void objdump_32bits(void *, char *);

#endif
