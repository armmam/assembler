#include "asm.h"
#include "libft.h"

unsigned	endline(t_asm *a)
{
	++a->j;
	return (ENDLINE);
}

unsigned	separator(t_asm *a)
{
	++a->j;
	return (SEPARATOR);
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
		return (INDIRECT_LABEL);
	else
		error3("Invalid indirect label", a);
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
			error3("Invalid direct", a);
	}
	else
	{
		if (a->j - a->i != 2)
			return (DIRECT_LABEL);
		else
			error3("Invalid direct label", a);
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
