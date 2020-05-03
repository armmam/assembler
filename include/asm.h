#ifndef ASM_H
# define ASM_H
# include "op.h"

# define BUFF_SIZE 			32767

# define OP_NUM				16

# define REGISTER			1
# define DIRECT				2
# define INDIRECT			4
# define DIRECT_LABEL		8
# define INDIRECT_LABEL		16
# define COMMAND_NAME		32
# define COMMAND_COMMENT	64
# define STRING				128
# define LABEL				256
# define INSTRUCTION		512
# define SEPARATOR			1024
# define ENDLINE			2048
# define END				4096

# define HASH_SIZE			67

typedef unsigned char		t_byte;

/*
** Struct to store label info (an element in a hash table)
** i -- index of the first char in a label
** len -- number of chars in a label
** number of the byte of a label in the output file
*/

typedef struct			s_label {
	int					i;
	int					len;
	int					byte_i;
	struct s_label		*next;
}						t_label;

/*
** i - index of the first char in current token
** j - index of the last char in current token
** nl -- number of the last \n in buff encountered
** nl_i -- index of the last \n in buff encountered
** byte_i -- number of the byte of the token pointed to by i in the output file
** (excluding file head info -- magic header, command name, command exec code
** size, command comment and nulls)
*/

typedef struct			s_asm {
	char				buff[BUFF_SIZE];
	int					i;
	int					j;
	int					nl;
	int					nl_i;
	int					byte_i;
	t_header			header;
	t_label				*ht[HASH_SIZE];

}						t_asm;

typedef struct			s_op
{
	char				name[5];
	int					typebyte;
	int					argnum;
	char				args[3];
	int					dirsize;
	int					lag;
}						t_op;

extern const t_op		g_tab[];

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
unsigned				char_token(t_asm *a);

t_label					*ht_search(t_asm *a);
void					ht_insert(t_asm *a);

#endif
