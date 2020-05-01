#include "asm.h"
#include "libft.h"

/*
** Try to process the token as INDIRECT_LABEL. Exit with error if failed.
*/

unsigned	indirect_label(t_asm *a)
{
	++a->j;
	while (ft_strchr(LABEL_CHARS, a->buff[a->j]))
		++a->j;
	if (a->j - a->i != 1)
		return (INDIRECT_LABEL);
	else
	{
		error3("Invalid indirect label", a);
		return (0);
	}
}

/*
** Try to process the token as DIRECT or DIRECT_LABEL. Exit with error if
** failed.
*/

unsigned	direct(t_asm *a)
{
	if (a->buff[++a->j] == LABEL_CHAR)
		++a->j;
	while (ft_strchr(LABEL_CHARS, a->buff[a->j]))
		++a->j;
	if (a->buff[a->i + 1] != LABEL_CHAR)
	{
		if (a->j - a->i != 1)
			return (DIRECT);
		else
		{
			error3("Invalid direct", a);
			return (0);
		}
	}
	else
	{
		if (a->j - a->i != 2)
			return (DIRECT_LABEL);
		else
		{
			error3("Invalid direct label", a);
			return (0);
		}
	}
}

/*
** Try to process the token as INDIRECT. Exit with error if failed.
*/

unsigned	neg_indirect(t_asm *a)
{
	if (a->buff[a->i] == '-' && !ft_isdigit(a->buff[a->i] + 1))
		error3("Invalid indirect", a);
	while (ft_isdigit(a->buff[a->j]))
		++a->j;
	return (INDIRECT);
}

/*
** Try to process the token as COMMAND_NAME or COMMENT_NAME. Exit with error if
** failed.
*/

unsigned	name(t_asm *a)
{
	if (ft_strnequ(&a->buff[a->i], NAME_CMD_STRING,
	ft_strlen(NAME_CMD_STRING)))
	{
		a->j = ft_strlen(NAME_CMD_STRING);
		return (COMMAND_NAME);
	}
	else if (ft_strnequ(&a->buff[a->i], COMMENT_CMD_STRING,
	ft_strlen(COMMENT_CMD_STRING)))
	{
		a->j = ft_strlen(COMMENT_CMD_STRING);
		return (COMMENT_NAME);
	}
	else
	{
		error3("Invalid command/comment name", a);
		return (0);
	}
}

/*
** Try to process the token as STRING. Exit with error if failed.
*/

unsigned	string(t_asm *a)
{
	while (a->buff[a->j] != '\"' && a->buff[a->j++] != '\0')
		if (a->buff[a->j] == '\n')
			new_newline(a);
	if (a->buff[a->j] == '\"')
		return (STRING);
	else
	{
		error3("Invalid string", a);
		return (0);
	}
}
