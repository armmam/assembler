/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brika <brika@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:37:10 by brika             #+#    #+#             */
/*   Updated: 2020/05/10 17:52:29 by brika            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <unistd.h>

void		disasm_check_eof(t_asm *a)
{
	if (a->i >= (int)a->header.prog_size)
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

	typebyte = a->op.typebyte ? a->code[a->i++] : 0;
	disasm_check_eof(a);
	i = 0;
	while (i < a->op.argnum)
	{
		if (i > 0)
			ft_dprintf(a->fd, ", ");
		arg_code = typebyte >> (3 - i) * 2 & CODE_BITMASK;
		if (arg_code == REG_CODE && a->op.args[i] & T_REG)
			disasm_write_reg(a);
		else if (!typebyte || (arg_code == DIR_CODE && a->op.args[i] & T_DIR))
			disasm_write_dir(a);
		else if (arg_code == IND_CODE && a->op.args[i] & T_IND)
			disasm_write_ind(a);
		else
			error("Invalid argument type.");
		i++;
	}
}

/*
** Try to write bytecode instructions to .s file, exit with error if failed or
** if the file ended while reading instruction info.
*/

void		disasm_write_body(t_asm *a)
{
	while (a->i < (int)a->header.prog_size)
	{
		if (a->code[a->i] > 0 && a->code[a->i] <= INSTR_NUM)
		{
			a->op = g_tab[(int)a->code[a->i++]];
			ft_dprintf(a->fd, "%s ", a->op.name);
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

void		disasm_write_header(t_asm *a)
{
	ft_dprintf(a->fd, "%s \"%s\"\n%s \"%s\"\n",
	NAME_CMD_STRING, a->header.prog_name,
	COMMENT_CMD_STRING, a->header.comment);
}
