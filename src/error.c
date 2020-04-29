/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 23:32:18 by sscarecr          #+#    #+#             */
/*   Updated: 2020/04/15 02:08:59 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** All error and usage messages and invariant check.
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

void	error(char *s)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	error2(char *s, char *t)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, t, ft_strlen(t));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	usage(void)
{
	ft_printf("Usage: ./asm [-d] <champion.s>\n"
	"\t-d\t: Disassembler mode\n");
	exit(EXIT_SUCCESS);
}
