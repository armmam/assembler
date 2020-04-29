#ifndef ASM_H
# define ASM_H
# include "op.h"

# define BUFF_SIZE 32767

typedef struct		s_asm {
	int				i;
	int				j;
	int				nl;
	char			buff[BUFF_SIZE];
}					t_asm;

void				sys_error(char *s);
void				error(char *s);
void				error2(char *s, char *t);
void				usage(void);

void				input(t_asm *a, int ac, char **av);
void				check_invariants(void);

#endif
