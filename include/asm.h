#ifndef ASM_H
# define ASM_H
# include "op.h"

# define BUFF_SIZE 32767

typedef struct		s_asm {
	int				i;
	int				j;
	int				nl;
	char			buff[BUFF_SIZE];
	int				r;
	int				fd;
}					t_asm;

void				error(char *s);
void				check_invariants(void);

#endif
