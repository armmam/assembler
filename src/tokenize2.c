/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brika <brika@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:37:58 by brika             #+#    #+#             */
/*   Updated: 2020/05/10 17:59:48 by brika            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

/*
** Try to process the token as COMMAND_NAME or COMMAND_COMMENT. Exit with error
** if failed.
*/

unsigned		header(t_asm *a)
{
	a->token = COMMAND_NAME;
	if (ft_strnequ(&a->buff[a->i], NAME_CMD_STRING,
	ft_strlen(NAME_CMD_STRING)))
	{
		a->j += ft_strlen(NAME_CMD_STRING);
		return (COMMAND_NAME);
	}
	else if (ft_strnequ(&a->buff[a->i], COMMENT_CMD_STRING,
	ft_strlen(COMMENT_CMD_STRING)))
	{
		a->j += ft_strlen(COMMENT_CMD_STRING);
		return (a->token = COMMAND_COMMENT);
	}
	else
	{
		error3("Invalid command name/comment keyword", a);
		return (0);
	}
}

/*
** Try to process the token as STRING. Exit with error if failed.
*/

unsigned		string(t_asm *a)
{
	int		nl;
	int		nl_i;

	nl = 0;
	nl_i = 0;
	a->token = STRING;
	++a->j;
	while (a->buff[a->j] != '\"' && a->buff[a->j] != '\0')
		if (a->buff[a->j++] == '\n')
		{
			++nl;
			nl_i = a->j;
		}
	if (a->buff[a->j] == '\"')
	{
		a->nl += nl;
		a->nl_i = nl_i > 0 ? nl_i : a->nl_i;
		++a->j;
		return (STRING);
	}
	else
	{
		error3("Invalid string", a);
		return (0);
	}
}

static int		ft_strnnum(const char *s, int num)
{
	if (!s)
		return (0);
	while (num && *s)
	{
		if (!ft_isdigit(*s))
			return (0);
		--num;
		++s;
	}
	return (1);
}

/*
** Try to process the token as INSTRUCTION. Exit with error if failed.
*/

static unsigned	instruction(t_asm *a)
{
	int					i;

	a->token = INSTRUCTION;
	i = 1;
	while (i <= INSTR_NUM)
	{
		if (ft_strnequ(&a->buff[a->i], g_tab[i].name,
		ft_strlen(g_tab[i].name)))
			return (INSTRUCTION);
		++i;
	}
	error3("Invalid instruction, indirect or register", a);
	return (0);
}

/*
** Try to process the token as INSTRUCTION, LABEL, REGISTER or INDIRECT. Exit
** with error if failed.
*/

unsigned		text(t_asm *a)
{
	while (a->buff[a->j] != '\0' && ft_strchr(LABEL_CHARS, a->buff[a->j]))
		++a->j;
	if (a->buff[a->j] == LABEL_CHAR && ++a->j)
		return (a->token = LABEL);
	while (ft_isalnum(a->buff[a->j]) &&
	ft_tolower(a->buff[a->j]) == a->buff[a->j])
		++a->j;
	if (a->buff[a->i] == 'r' && ((a->j - a->i == (int)ft_strlen("r1") &&
	!ft_strnequ(&a->buff[a->i], "r0", ft_strlen("r0")) &&
	ft_isdigit(a->buff[a->j - 1])) || (a->j - a->i == (int)ft_strlen("r01") &&
	ft_isdigit(a->buff[a->j - 1]) && ft_isdigit(a->buff[a->j - 2]) &&
	!ft_strnequ(&a->buff[a->i], "r00", ft_strlen("r00")))))
		return (a->token = REGISTER);
	else if (ft_strnnum(&a->buff[a->i], a->j - a->i))
		return (a->token = INDIRECT);
	else
		return (instruction(a));
}
