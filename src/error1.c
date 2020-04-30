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
** Non-system error messages.
*/

#include <stdio.h>
#include <unistd.h>
#include "asm.h"
#include "libft.h"

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

/*
** Replace the next \n after the last one encountered with \0.
*/

static void	next_newline(t_asm *a)
{
	unsigned i;

	i = a->nl_i;
	while (a->buff[i] != '\0' && a->buff[i] != '\n')
		++i;
	a->buff[i] = '\0';
}

/*
** Include line number where the error occured with its contents into error
** message.
*/

void	error3(char *s, t_asm *a)
{
	next_newline(a);
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, " at line ", 9);
	ft_putnbr_fd(a->nl + 1, STDERR_FILENO);
	write(STDERR_FILENO, "\n\t\"", 3);
	write(STDERR_FILENO, &a->buff[a->nl_i], ft_strlen(&a->buff[a->nl_i]));
	write(STDERR_FILENO, "\"\n", 2);
	exit(EXIT_FAILURE);
}
