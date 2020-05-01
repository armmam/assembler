#ifndef ASM_H
# define ASM_H
# include "op.h"

# define BUFF_SIZE 			32767

# define OP_NUM				16

# define COMMAND_NAME		1
# define COMMAND_COMMENT	2
# define STRING				4
# define LABEL				8
# define INSTRUCTION		16
# define REGISTER			32
# define DIRECT				64
# define DIRECT_LABEL		128
# define INDIRECT			256
# define INDIRECT_LABEL		512
# define SEPARATOR			1024
# define ENDLINE			2048
# define END				4096

typedef unsigned char		t_byte;

/*
** i - index of the first char in current token
** j - index of the last char in current token
** nl -- number of the last \n in buff encountered
** nl_i -- index of the last \n in buff encountered
*/

typedef struct			s_asm {
	unsigned			i;
	unsigned			j;
	unsigned			nl;
	unsigned			nl_i;
	t_header			header;
	char				buff[BUFF_SIZE];
}						t_asm;

void					sys_error(char *s);
void					error(char *s);
void					error2(char *s, char *t);
void					error3(char *s, t_asm *a);
void					usage(void);
void					check_invariants(void);

void					input(t_asm *a, int ac, char **av);
void					input_head(t_asm *a);
void					input_body(t_asm *a);

unsigned				tokenize(t_asm *a);
unsigned				name(t_asm *a);
unsigned				string(t_asm *a);
unsigned				text(t_asm *a);
unsigned				neg_indirect(t_asm *a);
unsigned				direct(t_asm *a);
unsigned				indirect_label(t_asm *a);
unsigned				endl(t_asm *a);

#endif
