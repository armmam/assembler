#ifndef ASM_H
# define ASM_H

# define BUFF_SIZE 32767

typedef struct		s_asm {
	int				i;
	int				j;
	int				nl;
	char			buff[BUFF_SIZE];
	int				r;
	int				fd;
}					t_asm;

#endif
