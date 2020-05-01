#include "asm.h"
#include "libft.h"

static int		ft_strnnum(const char *s, size_t num)
{
	if (!s)
		return (0);
	while (num && *s)
	{
		if (!ft_isdigit(*s))
			return (0);
		--num;
		++s;
	}
	return (1);
}

static unsigned	instruction(t_asm *a)
{
	static const char	*tab[] = {"live", "ld", "st", "add", "sub",
	"and", "or", "xor", "zjmp", "ldi", "sti", "sfork", "lld", "lldi", "lfork",
	"aff"};
	int					i;

	i = -1;
	while (++i < OP_NUM)
		if (ft_strnequ(&a->buff[a->i], tab[i], ft_strlen(tab[i])))
			return (INSTRUCTION);
	error3("Invalid instruction", a);
	return (0);
}

/*
** Try to process the token as INSTRUCTION, LABEL, REGISTER or INDIRECT. Exit
** with error if failed.
**
** ends with : => LABEL
** between 2 and 3 chars, the 1st one r, the rest nums, not r0/r00 => REGISTER
** all valid numbers (the first char may be -) => INDIRECT
** else (combination of chars and numbers, no '-' allowed) => INSTRUCTION
*/

unsigned		text(t_asm *a)
{
	while (ft_strchr(LABEL_CHARS, a->buff[a->j]) ||
	(ft_isalnum(a->buff[a->j]) && ft_tolower(a->buff[a->j]) == a->buff[a->j]))
		++a->j;
	if (a->buff[a->j] == LABEL_CHAR)
		return (LABEL);
	else if (a->buff[a->i] == 'r' && ((a->j - a->i == ft_strlen("r1") &&
	!ft_strnequ(&a->buff[a->i], "r0", ft_strlen("r0")) &&
	ft_isdigit(a->buff[a->j - 1])) || (a->j - a->i == ft_strlen("r01") &&
	ft_isdigit(a->buff[a->j - 1]) && ft_isdigit(a->buff[a->j - 2]) &&
	!ft_strnequ(&a->buff[a->i], "r00", ft_strlen("r00")))))
		return (REGISTER);
	else if (ft_strnnum(&a->buff[a->i], a->j - a->i))
		return (INDIRECT);
	else
		return (instruction(a));
}

static void		skip(t_asm *a)
{
	if (a->buff[a->j] == COMMENT_CHAR)
	{
		while (a->buff[a->j] != '\n' && a->buff[a->j] != '\0')
			++a->j;
		if (a->buff[a->j] == '\0')
			error("No newline at end of file.");
		++a->j;
		new_newline(a);
	}
	else
		while (ft_isspace(a->buff[a->j]) || a->buff[a->j] == '\n')
		{
			if (a->buff[a->j] == '\n')
				new_newline(a);
			++a->j;
		}
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
	skip(a);
	if (a->buff[a->i] == NAME_CMD_STRING[0])
		return (name(a)); // COMMAND_NAME or COMMENT_NAME
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
	else if (a->buff[a->i] == SEPARATOR_CHAR || a->buff[a->i] == '\n') // SEPARATOR / ENDLINE
		return (a->buff[a->i++] == SEPARATOR_CHAR ? SEPARATOR_CHAR : ENDLINE);
	else if (a->buff[a->i] == '\0')
		return (END); // END
	error("Unknown token.");
	return (0);
}
