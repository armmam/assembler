/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brika <brika@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:38:19 by brika             #+#    #+#             */
/*   Updated: 2020/05/10 17:43:37 by brika            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "op.h"

# define ASM_BUFF_SIZE 		32767
# define DISASM_BUFF_SIZE 	8191

# define INSTR_NUM			16
# define REG_NUM_SIZE		1

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
# define CODE_BITMASK		3

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

typedef struct			s_op
{
	char				name[5];
	int					typebyte;
	int					argnum;
	char				args[3];
	int					dirsize;
	int					lag;
}						t_op;

/*
** i - index of the first char in current token
** j - index of the last char in current token
** nl -- number of the last \n in buff encountered
** nl_i -- index of the last \n in buff encountered
** byte_i -- number of the byte of the token pointed to by i in the output file
** (excluding file head info -- magic header, command name, command exec code
** size, command comment and nulls)
** token -- the latest (last) recognized token: used in error3 functon
** header_flag -- flag for making sure that name/comment are only read once
** ht -- hash table for storing all encountered labels
** code -- buffer for storing all bytes of bytecode file (disasm)
** op -- info of the instruction currently being outputed to .s file (disasm)
*/

typedef struct			s_asm {
	char				buff[ASM_BUFF_SIZE + 1];
	int					i;
	int					j;
	int					nl;
	int					nl_i;
	int					byte_i;
	unsigned			token;
	t_header			header;
	unsigned			header_flag;
	t_label				*ht[HASH_SIZE];
	t_byte				code[DISASM_BUFF_SIZE + 1];
	t_op				op;
	int					fd;

}						t_asm;

extern const t_op		g_tab[];

void					sys_error(char *s);
void					error(char *s);
void					error2(char *s, char *t);
void					error3(char *s, t_asm *a);
void					usage(void);
void					check_invariants(void);

void					input(t_asm *a, int ac, char **av);
void					input_asm_header(t_asm *a);
void					input_asm_body(t_asm *a);
void					input_labels(t_asm *a);
int						arg_size(t_asm *a, const t_op *op);

unsigned				tokenize(t_asm *a);
unsigned				header(t_asm *a);
unsigned				string(t_asm *a);
unsigned				text(t_asm *a);
unsigned				neg_indirect(t_asm *a);
unsigned				direct(t_asm *a);
unsigned				indirect_label(t_asm *a);
unsigned				endl(t_asm *a);
unsigned				char_token(t_asm *a);

void					reset_indices(t_asm *a);
void					output(t_asm *a, int ac, char **av);
void					byte_swap(t_byte *bytes, int size);
int						antoi(char *nptr, int n);
int						bntoi(t_byte *byte, int n);
void					asm_write_header(t_asm *a);
void					asm_write_body(t_asm *a);
void					asm_write_reg(t_asm *a);
void					asm_write_dir(t_asm *a, int dirsize);
void					asm_write_ind(t_asm *a);
void					asm_write_dir_label(t_asm *a, int dirsize);
void					asm_write_ind_label(t_asm *a);
void					asm_write_dirsize_bytes(int fd, int dir, int dirsize);
void					asm_write_typebyte(int fd, t_op op, int *byte_i,
						t_byte typebyte);

void					disasm_write_header(t_asm *a);
void					disasm_write_body(t_asm *a);
void					disasm_write_reg(t_asm *a);
void					disasm_write_dir(t_asm *a);
void					disasm_write_ind(t_asm *a);
void					disasm_check_eof(t_asm *a);

t_label					*ht_search(t_asm *a);
void					ht_insert(t_asm *a);
void					ht_delete(t_asm *a);

#endif
