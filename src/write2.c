#include "asm.h"
#include "libft.h"
#include <unistd.h>

/*
** Write magic header, program name, program exec code size and program comment
** of .s file as bytes into .cor file.
*/

void		write_bytecode_header(t_asm *a)
{
	write_bytes(a->fd, (t_byte*)&a->header.magic, sizeof(unsigned));
	write(a->fd, &a->header.prog_name, PROG_NAME_LENGTH);
	write(a->fd, "\0\0\0\0", 4);
	write_bytes(a->fd, (t_byte*)&a->header.prog_size, sizeof(unsigned));
	write(a->fd, &a->header.comment, COMMENT_LENGTH);
	write(a->fd, "\0\0\0\0", 4);
}

static void	write_args(t_asm *a, t_op op, int *byte_i)
{
	int			j;
	t_byte		typebyte;

	j = 0;
	typebyte = 0;
	while (j < op.argnum)
	{
		if (j != 0)
			tokenize(a);
		if (tokenize(a) == REGISTER && (typebyte |= REG_CODE << (6 - 2 * j)))
			write_reg(a);
		else if (a->token == DIRECT && (typebyte |= DIR_CODE << (6 - 2 * j)))
			write_dir(a, op.dirsize);
		else if (a->token == INDIRECT && (typebyte |= IND_CODE << (6 - 2 * j)))
			write_ind(a);
		else if (a->token == DIRECT_LABEL &&
		(typebyte |= DIR_CODE << (6 - 2 * j)))
			write_dir_label(a, op.dirsize);
		else if (a->token == INDIRECT_LABEL &&
		(typebyte |= IND_CODE << (6 - 2 * j)))
			write_ind_label(a);
		byte_i += arg_size(a, &op);
		++j;
	}
	write_typebyte(a->fd, op, byte_i, typebyte);
}

/*
** IS write(a->fd, (t_byte)i, sizeof(t_byte)); READ CORRECTLY?
*/

static void	write_instr(t_asm *a)
{
	int			i;
	int			byte_i;

	i = 0;
	byte_i = 0;
	while (i < INSTR_NUM &&
	!ft_strnequ(&a->buff[a->i], g_tab[i].name, a->j - a->i))
		++i;
	write(a->fd, (t_byte*)&i, sizeof(t_byte));
	++byte_i;
	if (g_tab[i].typebyte)
	{
		write(a->fd, "\0", sizeof(t_byte));
		++byte_i;
	}
	write_args(a, g_tab[i], &byte_i);
	a->byte_i += byte_i;
}

/*
** Write instructions and their arguments as bytes into .cor file.
*/

void		write_bytecode_body(t_asm *a)
{
	while (tokenize(a) == COMMAND_NAME || a->token == COMMAND_COMMENT)
	{
	}
	while (tokenize(a) != END)
	{
		if (a->token == LABEL)
			tokenize(a);
		if (a->token == INSTRUCTION)
		{
			write_instr(a);
			tokenize(a);
		}
	}
}
