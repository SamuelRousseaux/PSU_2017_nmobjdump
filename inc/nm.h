/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** nm header
*/

#ifndef NM_H_
# define NM_H_

#include <elf.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct	s_flags
{
	int		st_type;
	Elf64_Word	sh_type;
	Elf64_Word	sh_flags;
	char		flag;
}		t_flags;

Elf64_Ehdr	*check_file(char *, int *, struct stat *, Elf64_Ehdr *);
Elf64_Sym	**copy_symtab(Elf64_Sym *, size_t);
char	get_flag(Elf64_Sym *, Elf64_Shdr *);
void	get_print_nm(void *, Elf64_Sym *, char *, char *);
int	my_nm(int, char **);
void	print_line(Elf64_Sym **, char *, Elf64_Shdr *, int);
void	print_nm(Elf64_Shdr *, Elf64_Sym *, char *, Elf64_Shdr *);
void	sort_ascii(Elf64_Sym **, int, char *);

#endif
