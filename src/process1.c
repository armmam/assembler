#include "asm.h"
#include "libft.h"

static void	next_line(t_asm *a)
{
	while (a->buff[a->j] != '\n' && a->buff[a->j] != '\0')
		++a->j;
	if (a->buff[a->j] != '\0')
		error("no newline at end of file.");
	++a->nl;
}

static void	skip(t_asm *a)
{
	while (a->buff[a->j] == COMMENT_CHAR || ft_isspace(a->buff[a->j++]))
		a->buff[a->j] == COMMENT_CHAR ? next_line(a) : ++a->j;
	a->i = a->j;
}

unsigned	tokenize(t_asm *a)
{
	skip(a);
	if (a->buff[a->i] == NAME_CMD_STRING[0]) // COMMAND_NAME or COMMENT_NAME
	else if (a->buff[a->i] == '"') // STRING
	else if (ft_strchr(LABEL_CHARS, a->buff[a->i]) ||
	(ft_isalnum(a->buff[a->i]) && ft_tolower(a->buff[a->i]) == a->buff[a->i])) // INSTRUCTION / LABEL / REGISTER / INDIRECT
	else if (a->buff[a->i] == DIRECT_CHAR) // DIRECT / DIRECT_LABEL
	else if (a->buff[a->i] == LABEL_CHAR) // INDIRECT_LABEL
	else if (a->buff[a->i] == SEPARATOR_CHAR) // SEPARATOR
	else if (a->buff[a->i] == '\n') // ENDLINE
	else if (a->buff[a->i] == '\0') // END
}
