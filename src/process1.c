#include "asm.h"
#include "libft.h"

static void	input_name(t_asm *a)
{
	if (!a->header.prog_name[0])
	{
		if (tokenize(a) == STRING)
		{
			if (a->j - a->i - 1 <= PROG_NAME_LENGTH)
				ft_strncpy(a->header.prog_name, &a->buff[a->i + 1],
				a->j - a->i - 1);
			else
				error3("Invalid program name length", a);
		}
		else
			error3("Invalid program name syntax", a);
	}
	else
		error3("Trying to specify program name multiple times", a);
}

static void	input_comment(t_asm *a)
{
	if (!a->header.comment[0])
	{
		if (tokenize(a) == STRING)
		{
			if (a->j - a->i - 1 <= COMMENT_LENGTH)
				ft_strncpy(a->header.comment, &a->buff[a->i + 1],
				a->j - a->i - 1);
			else
				error3("Invalid comment length", a);
		}
	}
	else
		error3("Trying to specify comment multiple times", a);
}

void		input_head(t_asm *a)
{
	unsigned	head_token;

	while (!a->header.prog_name[0] || !a->header.comment[0])
	{
		head_token = tokenize(a);
		if (head_token == COMMAND_NAME)
			input_name(a);
		else if (head_token == COMMAND_COMMENT)
			input_comment(a);
		else
			error3("Expected program name/comment", a);
	}
}

void		input_body(t_asm *a)
{
	(void)a;
}
