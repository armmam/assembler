#include "asm.h"
#include "libft.h"

void	reset_indices(t_asm *a)
{
	a->i = 0;
	a->j = 0;
	a->byte_i = 0;
	a->nl = 0;
	a->nl_i = 0;
	a->token = 0;
}

void		input_labels(t_asm *a)
{
	reset_indices(a);
	while(tokenize(a) != END)
	{
		if (a->token == DIRECT_LABEL || a->token == INDIRECT_LABEL)
		{
			if (!ht_search(a))
				error3("Tried to dereference non-existing label", a);
		}
	}
}
