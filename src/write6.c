/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brika <brika@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:37:15 by brika             #+#    #+#             */
/*   Updated: 2020/05/10 17:43:23 by brika            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <unistd.h>

void		disasm_write_reg(t_asm *a)
{
	short	reg;

	disasm_check_eof(a);
	reg = a->code[a->i++];
	ft_dprintf(a->fd, "r%hd", reg);
}

void		disasm_write_dir(t_asm *a)
{
	int		dir;
	short	ind;

	disasm_check_eof(a);
	dir = 0;
	ind = 0;
	if (a->op.dirsize == DIR_SIZE &&
	a->i + DIR_SIZE <= (int)a->header.prog_size)
	{
		byte_swap((t_byte*)&a->code[a->i], DIR_SIZE);
		dir = bntoi((t_byte*)&a->code[a->i], DIR_SIZE);
		ft_dprintf(a->fd, "%%%d", dir);
		a->i += DIR_SIZE;
	}
	else if (a->op.dirsize == IND_SIZE &&
	a->i + IND_SIZE <= (int)a->header.prog_size)
	{
		byte_swap((t_byte*)&a->code[a->i], IND_SIZE);
		ind = bntoi((t_byte*)&a->code[a->i], IND_SIZE);
		ft_dprintf(a->fd, "%%%hd", ind);
		a->i += IND_SIZE;
	}
	else
		error("File ended unexpectedly.");
}

void		disasm_write_ind(t_asm *a)
{
	short	ind;

	disasm_check_eof(a);
	if (a->i + IND_SIZE <= (int)a->header.prog_size)
	{
		byte_swap((t_byte*)&a->code[a->i], IND_SIZE);
		ind = bntoi((t_byte*)&a->code[a->i], IND_SIZE);
		ft_dprintf(a->fd, "%hd", ind);
		a->i += IND_SIZE;
	}
	else
		error("File ended unexpectedly.");
}
