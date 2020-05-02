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
		else
			error3("Invalid comment syntax", a);
	}
	else
		error3("Trying to specify comment multiple times", a);
}

/*
** Check that the file starts with exactly one COMMAND_NAME and COMMAND_COMMENT
** tokens, each followed with one STRING token, one pair per line (STRING may
** be multiline).
*/

void		input_head(t_asm *a)
{
	unsigned	head_token;

	while (!a->header.prog_name[0] || !a->header.comment[0])
	{
		while ((head_token = tokenize(a)) == ENDLINE)
		{
		}
		if (head_token == COMMAND_NAME)
			input_name(a);
		else if (head_token == COMMAND_COMMENT)
			input_comment(a);
		else
			error3("Expected program name/comment", a);
		if (tokenize(a) != ENDLINE)
			error3("Expected newline", a);
	}
}

/*
** Check that INSTRUCTION has valid number of arguments, valid argument syntax
** and no other instructions on the same line.
**
** a->i points to the beginning of INSTRUCTION token, a-j -- to its end.
*/

static void	input_instruction(t_asm *a)
{
	(void)a;
}

/*
** Check that every LABEL is at the beginning of a line, there is at most one
** INSTRUCTION per line (each of which is also whether at the beginning of a
** line or right after LABEL), each one is followed with a valid number and
** types of arguments, all separated from each other with SEPARATOR_CHAR.
** Record each LABEL name and the number of a byte it points to in a hash
** table.
**
** If LABEL then record it in hash table, set label_flag to true (to take the
** next instruction and save its place in memory into the same entry in hash
** table -- or is it actually "the current" place in memory?), and whether
** nothing else on the same line is allowed or exactly one INSTRUCTION (check
that the next token is ENDLINE, if END then EXIT_FAILURE).
**
** If INSTRUCTION then, if label_flag is set to true then save the INSTRUCTION
** place in memory into that hash table entry, make sure that it has proper
** number and types of arguments, each separated by SEPARATOR_CHAR,
** blahblahblah.
*/

void		input_body(t_asm *a)
{
	input_instruction(a);
}
