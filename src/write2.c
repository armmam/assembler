#include "asm.h"
#include "libft.h"
#include <unistd.h>

int			antoi(char *nptr, int n)
{
	char	end;
	int		res;

	nptr += n;
	end = *nptr;
	*nptr = '\0';
	nptr -= n;
	res = ft_atoi(nptr);
	nptr += n;
	*nptr = end;
	return (res);
}

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

static void	write_args(t_asm *a, t_op op)
{
	int			j;
	t_byte		args;

	j = 0;
	args = 0;
	while (j < op.argnum)
	{
		if (j != 0)
			tokenize(a);
		if (tokenize(a) == REGISTER && (args |= REG_CODE))
			write_reg(a);
		else if (a->token == DIRECT && (args |= DIR_CODE))
			write_dir(a, op.dirsize);
		else if (a->token == INDIRECT && (args |= IND_CODE))
			write_ind(a);
		else if (a->token == DIRECT_LABEL && (args |= DIR_CODE))
			write_dir_label(a, op.dirsize);
		else if (a->token == INDIRECT_LABEL && (args |= IND_CODE))
			write_ind_label(a);
		if (tokenize(a) & op.args[j] || (a->token == DIRECT_LABEL && 
		DIRECT & op.args[j]) || (a->token == INDIRECT_LABEL &&
		INDIRECT & op.args[j]))
			a->byte_i += arg_size(a, &op);
		++j;
	}
}

/*
** IS write(a->fd, (t_byte)i, sizeof(t_byte)); READ CORRECTLY?
*/

static void	write_instr(t_asm *a)
{
	int			i;

	i = 0;
	while (i < INSTR_NUM &&
	!ft_strnequ(&a->buff[a->i], g_tab[i].name, a->j - a->i))
		++i;
	write(a->fd, (t_byte*)&i, sizeof(t_byte));
	++a->byte_i;
	if (g_tab[i].typebyte)
	{
		write(a->fd, "\0", sizeof(t_byte));
		++a->byte_i;
	}
	write_args(a, g_tab[i]);
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
