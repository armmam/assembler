#include "asm.h"
#include "libft.h"

static void	input_name(t_asm *a)
{
	if (tokenize(a) == STRING)
	{
		if (a->j - a->i - 2 <= PROG_NAME_LENGTH)
			ft_strncpy(a->header.prog_name, &a->buff[a->i + 1],
			a->j - a->i - 2);
		else
			error3("Invalid program name length", a);
	}
	else
		error3("Invalid program name syntax", a);
}

static void	input_comment(t_asm *a)
{
	if (tokenize(a) == STRING)
	{
		if (a->j - a->i - 2 <= COMMENT_LENGTH)
			ft_strncpy(a->header.comment, &a->buff[a->i + 1],
			a->j - a->i - 2);
		else
			error3("Invalid comment length", a);
	}
	else
		error3("Invalid comment syntax", a);
}

/*
** Check that the file starts with exactly one COMMAND_NAME and COMMAND_COMMENT
** tokens, each followed with one STRING token, one pair per line (STRING may
** be multiline).
*/

void		input_head(t_asm *a)
{
	unsigned	token;
	int			prog_name;
	int			comment;

	prog_name = 0;
	comment = 0;
	while (!prog_name || !comment)
	{
		while ((token = tokenize(a)) == ENDLINE)
		{
		}
		if (token == COMMAND_NAME && (prog_name = 1))
			input_name(a);
		else if (token == COMMAND_COMMENT && (comment = 1))
			input_comment(a);
		else
			error3("Expected program name/comment", a);
		if (tokenize(a) != ENDLINE)
			error3("Expected newline after name/comment", a);
	}
}
