#include "asm.h"
#include "libft.h"

/*
** Try to process the token as INDIRECT. Exit with error if failed.
*/

unsigned	neg_indirect(t_asm *a)
{
	if (a->buff[a->i] == '-' && !ft_isdigit(a->buff[a->i] + 1))
		error3("Invalid indirect", a);
	while (ft_isdigit(a->buff[a->j]))
		++a->j;
	return ((a->last_token = INDIRECT));
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
			return ((a->last_token = DIRECT));
		else
		{
			error3("Invalid direct", a);
			return (0);
		}
	}
	else
	{
		if (a->j - a->i != 2)
			return ((a->last_token = DIRECT_LABEL));
		else
		{
			error3("Invalid direct label", a);
			return (0);
		}
	}
}

/*
** Try to process the token as INDIRECT_LABEL. Exit with error if failed.
*/

unsigned	indirect_label(t_asm *a)
{
	++a->j;
	while (ft_strchr(LABEL_CHARS, a->buff[a->j]))
		++a->j;
	if (a->j - a->i != 1)
		return ((a->last_token = INDIRECT_LABEL));
	else
	{
		error3("Invalid indirect label", a);
		return (0);
	}
}

/*
** Try to process SEPARATOR, ENDLINE or comment. Exit with error if failed.
*/

unsigned	char_token(t_asm *a)
{
	if (a->buff[a->i] == COMMENT_CHAR)
	{
		while (a->buff[a->j] != '\n' && a->buff[a->j] != '\0')
			++a->j;
		if (a->buff[a->j] == '\0')
			error("No newline at end of file.");
		return (endl(a));
	}
	a->i = ++a->j;
	return (a->buff[a->i] == SEPARATOR_CHAR ?
	(a->last_token = SEPARATOR) : endl(a));
}
