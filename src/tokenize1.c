#include "asm.h"
#include "libft.h"

/*
** Set nl_i and nl to refer to the new \n encountered
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
** has unallowed chars in it, output corresponding error message and terminate
** the program.
**
** indices are handled carelessly: does a->j point to the last char in the
** token or the first char after the token?
*/

unsigned		tokenize(t_asm *a)
{
	skip_spaces(a);
	if (a->buff[a->i] == NAME_CMD_STRING[0])
		return (name(a)); // COMMAND_NAME or COMMAND_COMMENT
	else if (a->buff[a->i] == '"')
		return (string(a)); // STRING
	else if (ft_strchr(LABEL_CHARS, a->buff[a->i]) || a->buff[a->i] == '-' ||
	(ft_isalnum(a->buff[a->i]) && ft_tolower(a->buff[a->i]) == a->buff[a->i]))
		return (text(a)); // INSTRUCTION / LABEL / REGISTER / INDIRECT
	else if (a->buff[a->i] == '-')
		return (neg_indirect(a)); // INDIRECT
	else if (a->buff[a->i] == DIRECT_CHAR)
		return (direct(a)); // DIRECT / DIRECT_LABEL
	else if (a->buff[a->i] == LABEL_CHAR)
		return (indirect_label(a)); // INDIRECT_LABEL
	else if (a->buff[a->i] == SEPARATOR_CHAR ||
	a->buff[a->i] == COMMENT_CHAR || a->buff[a->i] == '\n') // SEPARATOR / comment / ENDLINE
		return (char_token(a));
	else if (a->buff[a->i] == '\0')
		return (END); // END
	else
	{
		error("Unknown token.");
		return (0);
	}
}
