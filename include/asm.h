#ifndef ASM_H
# define ASM_H
# include "op.h"

# define BUFF_SIZE 32767

# define COMMAND_NAME	1
# define COMMENT_NAME	2
# define STRING			4
# define LABEL			8
# define INSTRUCTION	16
# define REGISTER		32
# define DIRECT			64
# define DIRECT_LABEL	128
# define INDIRECT		256
# define INDIRECT_LABEL	512
# define SEPARATOR		1024
# define ENDLINE		2048
# define END			4096

typedef struct		s_asm {
	unsigned		i;
	unsigned		j;
	unsigned		nl;
	t_header		header;
	char			buff[BUFF_SIZE];
}					t_asm;

void				sys_error(char *s);
void				error(char *s);
void				error2(char *s, char *t);
void				usage(void);
void				check_invariants(void);

void				input(t_asm *a, int ac, char **av);

unsigned			tokenize(t_asm *a);

#endif
