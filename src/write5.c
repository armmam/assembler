#include "asm.h"
#include "libft.h"
#include <unistd.h>

void		disasm_check_eof(t_asm *a)
{
	if (a->i < (int)a->header.prog_size)
		error("File ended unexpectedly.");
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
			ft_dprintf(a->fd, ", ");
		arg_code = typebyte >> (6 - i) * 2 & CODE_BITMASK;
		if (arg_code == REG_CODE && g_tab[a->token].args[i] & T_REG)
			disasm_write_reg(a);
		else if (arg_code == DIR_CODE && g_tab[a->token].args[i] & T_DIR)
			disasm_write_dir(a);
		else if (arg_code == IND_CODE && g_tab[a->token].args[i] & T_IND)
			disasm_write_ind(a);
		else
			error("Invalid argument type.");
		i++;
	}
}

/*
** Try to write bytecode instructions to .s file, exit with error if failed or
** if the file ended while reading instruction info.
**
** token member of t_asm struct is used for instr storage
*/

void		disasm_write_body(t_asm *a)
{
	const char	*instr;

	while (a->i < (int)a->header.prog_size)
	{
		if (a->code[a->i] > 0 && a->code[a->i] <= INSTR_NUM)
		{
			a->token = a->code[a->i];
			instr = g_tab[(int)a->code[a->i++]].name;
			ft_dprintf(a->fd, "%s ", instr);
			disasm_check_eof(a);
			disasm_write_args(a);
			ft_dprintf(a->fd, "\n");
		}
		else
			error("Invalid instruction.");
	}
}

/*
** Write program name and comment to .s file.
*/

void	disasm_write_header(t_asm *a)
{
	ft_dprintf(a->fd, "%s \"%s\"\n%s \"%s\"\n",
	NAME_CMD_STRING, a->header.prog_name,
	COMMENT_CMD_STRING, a->header.comment);
}
