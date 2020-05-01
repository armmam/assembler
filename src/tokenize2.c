#include "asm.h"
#include "libft.h"

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
		return (COMMAND_COMMENT);
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




