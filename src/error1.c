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

void		error(char *s)
{
	ft_dprintf(STDERR_FILENO, "Error: %s\n", s);
	exit(EXIT_FAILURE);
}

void		error2(char *s, char *t)
{
	ft_dprintf(STDERR_FILENO, "Error: %s%s\n", s, t);
	exit(EXIT_FAILURE);
}

/*
** Replace the next \n after the last one encountered with \0.
*/

static void	next_newline(t_asm *a)
{
	int		i;

	if (a->token == ENDLINE)
	{
		--a->nl;
		a->buff[--a->nl_i] = '\0';
		if (a->nl_i)
		{
			--a->nl_i;
			while (a->nl_i && a->buff[a->nl_i] != '\n')
				--a->nl_i;
			if (a->buff[a->nl_i] == '\n')
				++a->nl_i;
		}
	}
	else
	{
		i = a->nl_i;
		while (a->buff[i] != '\0' && a->buff[i] != '\n')
			++i;
		a->buff[i] = '\0';
	}
}

/*
** Include line number where the error occured with its contents into error
** message.
**
** Fix: print a single line instead of the rest of the file (replace the next
** \n with \0)
*/

void		error3(char *s, t_asm *a)
{
	next_newline(a);
	ft_dprintf(STDERR_FILENO, "Error: %s at line %i\n\t\"%s\"\n",
	s, a->nl + 1, &a->buff[a->nl_i]);
	exit(EXIT_FAILURE);
}
