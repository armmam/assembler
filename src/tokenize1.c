/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brika <brika@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:37:52 by brika             #+#    #+#             */
/*   Updated: 2020/05/10 17:59:13 by brika            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

/*
** Set nl_i and nl to refer to the new encountered \n.
*/

unsigned		endl(t_asm *a)
{
	a->nl_i = a->j;
	++a->nl;
	return (ENDLINE);
}

static void		skip_spaces(t_asm *a)
{
	while (a->buff[a->j] == ' ' || a->buff[a->j] == '\t')
		++a->j;
	a->i = a->j;
}

/*
** Recognize the next token, set buffer indices a->i and a->j to the
** beginning and the end of the token and return the token flag. If the token
** has unallowed chars in it, output the corresponding error message and
** terminate the program.
*/

unsigned		tokenize(t_asm *a)
{
	skip_spaces(a);
	if (a->buff[a->i] == '\0')
		return (a->token = END);
	else if (a->buff[a->i] == NAME_CMD_STRING[0])
		return (header(a));
	else if (a->buff[a->i] == '"')
		return (string(a));
	else if (ft_strchr(LABEL_CHARS, a->buff[a->i]) ||
	(ft_isalnum(a->buff[a->i]) && ft_tolower(a->buff[a->i]) == a->buff[a->i]))
		return (text(a));
	else if (a->buff[a->i] == '-')
		return (neg_indirect(a));
	else if (a->buff[a->i] == DIRECT_CHAR)
		return (direct(a));
	else if (a->buff[a->i] == LABEL_CHAR)
		return (indirect_label(a));
	else if (a->buff[a->i] == SEPARATOR_CHAR ||
	a->buff[a->i] == COMMENT_CHAR || a->buff[a->i] == '\n')
		return (char_token(a));
	else
	{
		a->token = 0;
		error3("Syntax error", a);
		return (0);
	}
}
