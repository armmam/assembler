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
#include <limits.h>
#include "asm.h"
#include "libft.h"

void	error(char *s)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

/*
** COMMENT_CHAR, LABEL_CHAR, DIRECT_CHAR, SEPARATOR_CHAR, first element of
** NAME_CMD_STRING, COMMENT_CMD_STRING and any elements of LABEL_CHARS should
** all be different, printable and non-space.
*/

static void	check_labels(void)
{
	char	c;

	if (ft_strchr(LABEL_CHARS, COMMENT_CHAR) ||
	ft_strchr(LABEL_CHARS, LABEL_CHAR) ||
	ft_strchr(LABEL_CHARS, DIRECT_CHAR) ||
	ft_strchr(LABEL_CHARS, SEPARATOR_CHAR) ||
	ft_strchr(LABEL_CHARS, NAME_CMD_STRING[0]))
		error("op.h constants are invalid.");
	c = 0;
	while (c != '\0' && (!ft_isprint(c) || ft_isspace(c)))
	{
		if (ft_strchr(LABEL_CHARS, c) || ft_strchr(NAME_CMD_STRING, c) ||
		ft_strchr(COMMENT_CMD_STRING, c++))
			error("op.h constants are invalid.");
	}
}

void	check_invariants(void)
{
	if (BUFF_SIZE != SHRT_MAX && BUFF_SIZE != USHRT_MAX)
		error("asm.h constants are invalid.");
	if (NAME_CMD_STRING[0] != COMMENT_CMD_STRING[0] ||
	!ft_isprint(COMMENT_CHAR) || ft_isspace(COMMENT_CHAR) ||
	!ft_isprint(LABEL_CHAR) || ft_isspace(LABEL_CHAR) ||
	!ft_isprint(DIRECT_CHAR) || ft_isspace(DIRECT_CHAR) ||
	!ft_isprint(SEPARATOR_CHAR) || ft_isspace(SEPARATOR_CHAR) ||
	!ft_isprint(NAME_CMD_STRING[0]) || ft_isspace(NAME_CMD_STRING[0]) ||
	COMMENT_CHAR == LABEL_CHAR || COMMENT_CHAR == DIRECT_CHAR ||
	COMMENT_CHAR == SEPARATOR_CHAR || COMMENT_CHAR == NAME_CMD_STRING[0] ||
	LABEL_CHAR == DIRECT_CHAR || LABEL_CHAR == SEPARATOR_CHAR ||
	LABEL_CHAR == NAME_CMD_STRING[0] || DIRECT_CHAR == SEPARATOR_CHAR ||
	DIRECT_CHAR == NAME_CMD_STRING[0] ||
	SEPARATOR_CHAR == NAME_CMD_STRING[0] ||
	IND_SIZE != sizeof(short) || REG_SIZE != sizeof(int) ||
	DIR_SIZE > REG_SIZE || REG_CODE == DIR_CODE || REG_CODE == IND_CODE ||
	DIR_CODE == IND_CODE || MEM_SIZE <= 0 || MAX_ARGS_NUMBER <= 0 ||
	MAX_ARGS_NUMBER > 4 || MAX_PLAYERS <= 0 || MEM_SIZE <= 0 ||
	CHAMP_MAX_SIZE * MAX_PLAYERS > MEM_SIZE || REG_NUMBER <= 0 ||
	T_REG == T_DIR || T_REG == T_IND || T_IND == T_DIR ||
	PROG_NAME_LENGTH < 0 || COMMENT_LENGTH < 0)
		error("op.h constants are invalid.");
	check_labels();
}
