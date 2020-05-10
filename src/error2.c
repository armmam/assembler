/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brika <brika@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 23:32:18 by sscarecr          #+#    #+#             */
/*   Updated: 2020/05/10 17:43:36 by brika            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** System error and usage messages.
*/

#include <stdio.h>
#include <unistd.h>
#include "asm.h"
#include "libft.h"

void	sys_error(char *s)
{
	if (!s)
		write(STDERR_FILENO, "Error: ", 7);
	perror(s);
	exit(EXIT_FAILURE);
}

void	usage(void)
{
	ft_printf("Usage: ./asm [-d] <file>\n"
	"\t-d\t: Disassembler mode\n");
	exit(EXIT_SUCCESS);
}
