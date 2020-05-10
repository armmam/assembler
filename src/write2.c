/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brika <brika@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:36:54 by brika             #+#    #+#             */
/*   Updated: 2020/05/10 17:51:12 by brika            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <unistd.h>

/*
** Write magic header, program name, program exec code size and program comment
** of .s file as bytes into .cor file.
*/

void		asm_write_header(t_asm *a)
{
	byte_swap((t_byte*)&a->header.magic, sizeof(unsigned));
	byte_swap((t_byte*)&a->header.prog_size, sizeof(unsigned));
	write(a->fd, (t_byte*)&a->header.magic, sizeof(unsigned));
	write(a->fd, &a->header.prog_name, PROG_NAME_LENGTH);
	write(a->fd, "\0\0\0\0", 4);
	write(a->fd, (t_byte*)&a->header.prog_size, sizeof(unsigned));
	write(a->fd, &a->header.comment, COMMENT_LENGTH);
	write(a->fd, "\0\0\0\0", 4);
}

static void	asm_write_args(t_asm *a, t_op op, int *byte_i)
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
			asm_write_reg(a);
		else if (a->token == DIRECT && (typebyte |= DIR_CODE << (6 - 2 * j)))
			asm_write_dir(a, op.dirsize);
		else if (a->token == INDIRECT && (typebyte |= IND_CODE << (6 - 2 * j)))
			asm_write_ind(a);
		else if (a->token == DIRECT_LABEL &&
		(typebyte |= DIR_CODE << (6 - 2 * j)))
			asm_write_dir_label(a, op.dirsize);
		else if (a->token == INDIRECT_LABEL &&
		(typebyte |= IND_CODE << (6 - 2 * j)))
			asm_write_ind_label(a);
		*byte_i += arg_size(a, &op);
		++j;
	}
	asm_write_typebyte(a->fd, op, byte_i, typebyte);
}

static void	asm_write_instr(t_asm *a)
{
	t_byte		i;
	int			byte_i;

	i = 1;
	byte_i = 0;
	while (i <= INSTR_NUM &&
	!ft_strnequ(&a->buff[a->i], g_tab[i].name, a->j - a->i))
		++i;
	write(a->fd, (t_byte*)&i, sizeof(t_byte));
	++byte_i;
	if (g_tab[i].typebyte)
	{
		write(a->fd, "\0", sizeof(t_byte));
		++byte_i;
	}
	asm_write_args(a, g_tab[i], &byte_i);
	a->byte_i += byte_i;
}

/*
** Write instructions and their arguments as bytes into .cor file.
*/

void		asm_write_body(t_asm *a)
{
	while (tokenize(a) != END)
	{
		if (a->token == LABEL)
			tokenize(a);
		if (a->token == INSTRUCTION)
		{
			asm_write_instr(a);
			tokenize(a);
		}
	}
}
