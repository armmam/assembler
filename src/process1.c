#include "asm.h"
#include "libft.h"

/*
** Set nl_i and nl to refer to the new \n encountered
*/

void	new_newline(t_asm *a)
{
	a->nl_i = a->j;
	++a->nl;
}

void	input_head(t_asm *a)
{
	unsigned	head_token;

	(void)a;
	(void)head_token;
}

void	input_body(t_asm *a)
{
	(void)a;
}
