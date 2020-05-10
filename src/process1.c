/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brika <brika@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:37:31 by brika             #+#    #+#             */
/*   Updated: 2020/05/10 17:43:27 by brika            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

static void	input_name(t_asm *a)
{
	if (a->header_flag & COMMAND_NAME)
		error3("Another command name keyword", a);
	if (tokenize(a) == STRING)
	{
		if (a->j - a->i - 2 <= PROG_NAME_LENGTH)
		{
			ft_strncpy(a->header.prog_name, &a->buff[a->i + 1],
			a->j - a->i - 2);
			a->header_flag |= COMMAND_NAME;
		}
		else
			error3("Invalid command name string length", a);
	}
	else
		error3("Expected string after command name keyword", a);
}

static void	input_comment(t_asm *a)
{
	if (a->header_flag & COMMAND_COMMENT)
		error3("Another command comment keyword", a);
	if (tokenize(a) == STRING)
	{
		if (a->j - a->i - 2 <= COMMENT_LENGTH)
		{
			ft_strncpy(a->header.comment, &a->buff[a->i + 1],
			a->j - a->i - 2);
			a->header_flag |= COMMAND_COMMENT;
		}
		else
			error3("Invalid command comment string length", a);
	}
	else
		error3("Expected string after command comment keyword", a);
}

/*
** Check that the file starts with exactly one COMMAND_NAME and COMMAND_COMMENT
** tokens, each followed with one STRING token, one pair per line (STRING may
** be multiline).
*/

void		input_asm_header(t_asm *a)
{
	a->header.magic = COREWAR_EXEC_MAGIC;
	while (!(a->header_flag & COMMAND_COMMENT) ||
	!(a->header_flag & COMMAND_NAME))
	{
		while (tokenize(a) == ENDLINE)
		{
		}
		if (a->token == COMMAND_NAME)
			input_name(a);
		else if (a->token == COMMAND_COMMENT)
			input_comment(a);
		else
			error3("Expected command name or comment keyword", a);
		if (tokenize(a) != ENDLINE)
			error3("Expected newline after command name or comment string", a);
	}
}
