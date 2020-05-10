/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brika <brika@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:38:03 by brika             #+#    #+#             */
/*   Updated: 2020/05/10 18:00:17 by brika            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

/*
** Try to process the token as INDIRECT. Exit with error if failed.
*/

unsigned	neg_indirect(t_asm *a)
{
	if (a->buff[a->j] == '-' && !ft_isdigit(a->buff[++a->j]))
		error3("Invalid indirect", a);
	while (ft_isdigit(a->buff[a->j]))
		++a->j;
	return (a->token = INDIRECT);
}

/*
** Try to process the token as DIRECT or DIRECT_LABEL. Exit with error if
** failed.
*/

unsigned	direct(t_asm *a)
{
	if (a->buff[++a->j] == LABEL_CHAR)
	{
		++a->j;
		while (a->buff[a->j] != '\0' && ft_strchr(LABEL_CHARS, a->buff[a->j]))
			++a->j;
		if (a->j - a->i == 2)
			error3("Invalid direct label", a);
		return (a->token = DIRECT_LABEL);
	}
	else
	{
		if ((a->buff[a->j] == '-' && !ft_isdigit(a->buff[a->j + 1])) ||
		(a->buff[a->j] != '-' && !ft_isdigit(a->buff[a->j])))
			error3("Invalid direct", a);
		else if (a->buff[a->j] == '-')
			++a->j;
		while (ft_isdigit(a->buff[a->j]))
			++a->j;
		return (a->token = DIRECT);
	}
}

/*
** Try to process the token as INDIRECT_LABEL. Exit with error if failed.
*/

unsigned	indirect_label(t_asm *a)
{
	++a->j;
	while (a->buff[a->j] != '\0' && ft_strchr(LABEL_CHARS, a->buff[a->j]))
		++a->j;
	if (a->j - a->i != 1)
		return (a->token = INDIRECT_LABEL);
	else
	{
		error3("Invalid indirect label", a);
		return (0);
	}
}

/*
** Try to process the token as SEPARATOR, ENDLINE or a comment. Exit with error
** if failed.
*/

unsigned	char_token(t_asm *a)
{
	if (a->buff[a->i] == COMMENT_CHAR)
	{
		while (a->buff[a->j] != '\n' && a->buff[a->j] != '\0')
			++a->j;
		if (a->buff[a->j] == '\0')
			error("No newline at end of file.");
		a->i = ++a->j;
		return (a->token = endl(a));
	}
	a->i = ++a->j;
	return (a->buff[a->i - 1] == SEPARATOR_CHAR ?
	(a->token = SEPARATOR) :
	(a->token = endl(a)));
}
