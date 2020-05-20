#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "asm.h"

/*
** System error and usage messages.
*/

void	sys_error(char *s)
{
	if (!s)
		write(STDERR_FILENO, "Error: ", 7);
	perror(s);
	exit(EXIT_FAILURE);
}

void	usage(void)
{
	printf("Usage: ./asm [-d] <file>\n"
	"\t-d\t: Disassembler mode\n");
	exit(EXIT_SUCCESS);
}
