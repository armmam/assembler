#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "asm.h"
#include "libft.h"

static void	check_labels(void)
{
	char	c;

	if (!strlen(LABEL_CHARS) || strchr(LABEL_CHARS, '"') ||
	strchr(LABEL_CHARS, '-') || strchr(LABEL_CHARS, COMMENT_CHAR) ||
	strchr(LABEL_CHARS, LABEL_CHAR) ||
	strchr(LABEL_CHARS, DIRECT_CHAR) ||
	strchr(LABEL_CHARS, SEPARATOR_CHAR) ||
	strchr(LABEL_CHARS, NAME_CMD_STRING[0]))
		error("op.h constants are invalid.");
	c = 0;
	while (!isprint(c) || isspace(c))
	{
		if (c == '\0')
			++c;
		if (strchr(LABEL_CHARS, c) || strchr(NAME_CMD_STRING, c) ||
		strchr(COMMENT_CMD_STRING, c++))
			error("op.h constants are invalid.");
	}
}

static void	check_char(void)
{
	if (isalnum(COMMENT_CHAR) || isalnum(LABEL_CHAR) ||
	isalnum(DIRECT_CHAR) || isalnum(SEPARATOR_CHAR) ||
	COMMENT_CHAR == '"' || LABEL_CHAR == '"' || DIRECT_CHAR == '"' ||
	SEPARATOR_CHAR == '"' || COMMENT_CHAR == '-' || LABEL_CHAR == '-' ||
	DIRECT_CHAR == '-' || SEPARATOR_CHAR == '-' || !isprint(COMMENT_CHAR) ||
	isspace(COMMENT_CHAR) || !isprint(LABEL_CHAR) ||
	isspace(LABEL_CHAR) || !isprint(DIRECT_CHAR) ||
	isspace(DIRECT_CHAR) || !isprint(SEPARATOR_CHAR) ||
	isspace(SEPARATOR_CHAR) || COMMENT_CHAR == LABEL_CHAR ||
	COMMENT_CHAR == DIRECT_CHAR || COMMENT_CHAR == SEPARATOR_CHAR ||
	COMMENT_CHAR == NAME_CMD_STRING[0] || LABEL_CHAR == DIRECT_CHAR ||
	LABEL_CHAR == SEPARATOR_CHAR || LABEL_CHAR == NAME_CMD_STRING[0] ||
	DIRECT_CHAR == SEPARATOR_CHAR || DIRECT_CHAR == NAME_CMD_STRING[0] ||
	SEPARATOR_CHAR == NAME_CMD_STRING[0])
		error("op.h constants are invalid.");
}

/*
** LABELS_CHARS, NAME_CMD_STRING and COMMENT_CMD_STRING should be non-empty.
** NAME_CMD_STRING and COMMENT_CMD_STRING should be different and one cannot be
** a substring of the other. COMMENT_CHAR, LABEL_CHAR, DIRECT_CHAR,
** SEPARATOR_CHAR, first element of NAME_CMD_STRING and COMMENT_CMD_STRING and
** any elements of LABEL_CHARS should all be different, printable non-space,
** not '"' and not '-'. In addition, none of the above (except for chars from
** NAME_CMD_STRING, COMMENT_CMD_STRING (starting with the second one) and
** LABEL_CHARS) can be alphabetical or numeric. Also, T_REG should be equal to
** REGISTER, T_DIR should be equal to DIRECT, T_IND should be equal to
** INDIRECT.
*/

void		check_invariants(void)
{
	if (ASM_BUFF_SIZE != SHRT_MAX && ASM_BUFF_SIZE != USHRT_MAX)
		error("asm.h constants are invalid.");
	if (NAME_CMD_STRING[0] != COMMENT_CMD_STRING[0] ||
	!strlen(NAME_CMD_STRING) ||
	strequ(NAME_CMD_STRING, COMMENT_CMD_STRING) ||
	strstr(NAME_CMD_STRING, COMMENT_CMD_STRING) ||
	strstr(COMMENT_CMD_STRING, NAME_CMD_STRING) ||
	strchr(NAME_CMD_STRING, '"') || strchr(COMMENT_CMD_STRING, '"') ||
	strchr(NAME_CMD_STRING, '-') || strchr(COMMENT_CMD_STRING, '-') ||
	isalnum(NAME_CMD_STRING[0]) || !isprint(NAME_CMD_STRING[0]) ||
	isspace(NAME_CMD_STRING[0]) ||
	IND_SIZE != sizeof(short) || REG_SIZE != sizeof(int) ||
	DIR_SIZE > REG_SIZE || REG_CODE == DIR_CODE || REG_CODE == IND_CODE ||
	DIR_CODE == IND_CODE || MEM_SIZE <= 0 || MAX_ARGS_NUMBER <= 0 ||
	MAX_ARGS_NUMBER > 4 || MAX_PLAYERS <= 0 || MEM_SIZE <= 0 ||
	CHAMP_MAX_SIZE * MAX_PLAYERS > MEM_SIZE || REG_NUMBER <= 0 ||
	T_REG == T_DIR || T_REG == T_IND || T_IND == T_DIR ||
	T_REG != REGISTER || T_DIR != DIRECT || T_IND != INDIRECT ||
	PROG_NAME_LENGTH < 0 || COMMENT_LENGTH < 0)
		error("op.h constants are invalid.");
	check_char();
	check_labels();
}
