/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brika <brika@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:36:23 by brika             #+#    #+#             */
/*   Updated: 2020/05/10 18:07:23 by brika            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

/*
** Swap bytes in multibyte data so that it changes its endianness
*/

void		byte_swap(t_byte *bytes, int size)
{
	int		i;
	t_byte	c;

	i = 0;
	while (i < (int)size / 2)
	{
		c = bytes[i];
		bytes[i] = bytes[size - 1 - i];
		bytes[size - 1 - i] = c;
		++i;
	}
}

/*
** Write contents of a file containing bytecode as asm instructions into .s file
*/

static void	disasm_write(t_asm *a)
{
	disasm_write_header(a);
	disasm_write_body(a);
}

/*
** Write contents of .s file as bytes into .cor file
*/

static void	asm_write(t_asm *a)
{
	reset_indices(a);
	asm_write_header(a);
	asm_write_body(a);
}

/*
** Try to create a file with the same filename as the old one but with .cor
** (.s for disasm) instead of .s (.cor for disasm) or, if failed, with .cor
** (.s for disasm) appended to the old filename. If there already is a file
** with the new filename, overwrite it.
*/

static void	create_file(t_asm *a, int ac, char **av)
{
	int		i;
	char	*filename;
	char	*new_filename;

	filename = ac == 3 ? av[2] : av[1];
	i = ft_strlen(filename);
	while (--i >= 0 && filename[i] != '/')
		if (filename[i] == '.')
		{
			filename[i] = '\0';
			break ;
		}
	if (!(new_filename = ac == 3 ?
	ft_strjoin(filename, ".s") : ft_strjoin(filename, ".cor")))
		sys_error(NULL);
	if ((a->fd = open(new_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		sys_error(new_filename);
	ft_printf("Writing output program to %s\n", new_filename);
	ft_memdel((void**)&new_filename);
}

/*
** Output bytecode or assembly code (if -d option is present) into a file
** created by create_file function.
*/

void		output(t_asm *a, int ac, char **av)
{
	create_file(a, ac, av);
	if (ac == 2)
		asm_write(a);
	else
		disasm_write(a);
	close(a->fd);
	ht_delete(a);
}
