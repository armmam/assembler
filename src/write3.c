/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brika <brika@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:37:00 by brika             #+#    #+#             */
/*   Updated: 2020/05/10 17:43:20 by brika            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <unistd.h>

void		asm_write_reg(t_asm *a)
{
	t_byte	reg;

	reg = antoi(&a->buff[a->i + 1], a->j - a->i - 1);
	write(a->fd, &reg, REG_NUM_SIZE);
}

void		asm_write_dir(t_asm *a, int dirsize)
{
	int		dir;

	dir = antoi(&a->buff[a->i + 1], a->j - a->i - 1);
	asm_write_dirsize_bytes(a->fd, dir, dirsize);
}

void		asm_write_ind(t_asm *a)
{
	short	ind;

	ind = antoi(&a->buff[a->i], a->j - a->i);
	byte_swap((t_byte*)&ind, IND_SIZE);
	write(a->fd, (t_byte*)&ind, IND_SIZE);
}

void		asm_write_dir_label(t_asm *a, int dirsize)
{
	int		dir;
	t_label	*label;

	label = ht_search(a);
	dir = label->byte_i - a->byte_i;
	asm_write_dirsize_bytes(a->fd, dir, dirsize);
}

void		asm_write_ind_label(t_asm *a)
{
	short	ind;
	t_label	*label;

	label = ht_search(a);
	ind = label->byte_i - a->byte_i;
	byte_swap((t_byte*)&ind, IND_SIZE);
	write(a->fd, (t_byte*)&ind, IND_SIZE);
}
