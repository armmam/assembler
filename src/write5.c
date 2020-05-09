#include "asm.h"
#include "libft.h"
#include <unistd.h>

static void	disasm_check_eof(t_asm *a)
{
	if (a->i < (int)a->header.prog_size)
		error("File ended unexpectedly");
}

/*
** Write bytecode instruction arguments to .s file, exit with error if
** the file ended while reading arguments.
*/

static void	disasm_write_args(t_asm *a)
{
	t_byte	typebyte;
	t_byte	arg_code;
	int		i;

	typebyte = g_tab[(int)a->code[a->i]].typebyte && a->i++ ?
	a->code[a->i - 1] : 0;
	disasm_check_eof(a);
	i = 0;
	while (i < g_tab[(int)a->code[a->i]].argnum)
	{
		if (i < g_tab[(int)a->code[a->i]].argnum - 1)
			write(a->fd, ", ", 2);
		arg_code = typebyte >> (6 - i) * 2 & CODE_BITMASK;
		if (arg_code == REG_CODE)
			disasm_write_reg(a);
		else if (arg_code == DIR_CODE)
			disasm_write_dir(a);
		else
			disasm_write_ind(a);
		i++;
	}
}

/*
** Try to write bytecode instruction to .s file, exit with error if failed or
** if the file ended while reading instruction info.
*/

static void	disasm_write_instr(t_asm *a)
{
	const char	*instr;

	if (a->code[a->i] > 0 && a->code[a->i] <= INSTR_NUM)
	{
		instr = g_tab[(int)a->code[a->i++]].name;
		write(a->fd, instr, ft_strlen(instr));
		write(a->fd, " ", 1);
		disasm_check_eof(a);
		disasm_write_args(a);
		write(1, "\n", 1);
	}
	else
		error("Invalid instruction.");
}

/*
** Write bytecode instructions to .s file.
*/

void		disasm_write_body(t_asm *a)
{
	while (a->i < (int)a->header.prog_size)
		disasm_write_instr(a);
}

/*
** Write program name and comment to .s file.
*/

void	disasm_write_header(t_asm *a)
{
	write(a->fd, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING));
	write(a->fd, " \"", 2);
	write(a->fd, a->header.prog_name, ft_strlen(a->header.prog_name));
	write(a->fd, "\"\n", 2);
	write(a->fd, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING));
	write(a->fd, " \"", 2);
	write(a->fd, a->header.comment, ft_strlen(a->header.comment));
	write(a->fd, "\"\n", 2);
}
