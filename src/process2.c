#include "asm.h"
#include "libft.h"

static int	arg_size(const t_op *op, unsigned token)
{
	if (token == REGISTER)
		return (REG_SIZE);
	else if (token == INDIRECT)
		return (IND_SIZE);
	else
		return (op->dirsize);
}

/*
** Check that INSTRUCTION has valid number of arguments, valid argument syntax
** and no other instructions on the same line.
**
** a->i points to the beginning of INSTRUCTION token, a-j -- to its end.
*/

static void	input_instruction(t_asm *a)
{
	int			i;
	int			j;
	unsigned	token;

	i = 0;
	while (i < OP_NUM &&
	!ft_strnequ(&a->buff[a->i], g_tab[i].name, a->j - a->i + 1))
		++i;
	if (i == OP_NUM)
		error3("Invalid instruction", a);
	++a->byte_i;
	if (g_tab[i].typebyte)
		++a->byte_i;
	j = 0;
	while (j < g_tab[i].argnum)
	{
		if (j != 0 && tokenize(a) != SEPARATOR)
			error3("Expected separator", a);
		if ((token = tokenize(a)) & g_tab[i].args[j])
			a->byte_i += arg_size(&g_tab[i], token);
		else
			error3("Invalid argument", a);
	}
	token = tokenize(a);
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
	unsigned	token;

	while ((token = tokenize(a)) != END)
	{
		if (token == LABEL)
		{
			token = tokenize(a);
			ht_insert(a);
		}
		if (token == INSTRUCTION)
			input_instruction(a);
		if (token != ENDLINE)
			error3("Expected newline", a);
	}
}
