#include "asm.h"
#include "libft.h"

static unsigned	hash(char *s, int n)
{
	unsigned	hash_val;

	hash_val = 0;
	while (n-- > 0)
		hash_val = *s + 31 * hash_val;
	return (hash_val % HASH_SIZE);
}

/*
** Search for a token in the hash table. If the token is not present in the
** hash table, return NULL (the function that invoked this one should exit in
** this case).
*/

t_label			*ht_search(t_asm *a)
{
	t_label	*label;
	int		i;
	int		len;

	if (a->token == DIRECT_LABEL || a->token == INDIRECT_LABEL)
	{
		i = a->token == DIRECT_LABEL ? a->i + 2 : a->i + 1;
		len = a->j - i;
	}
	else
	{
		i = a->i;
		len = a->j - i - 1;
	}
	label = a->ht[hash(&a->buff[i], len)];
	while (label)
	{
		if (len == label->len &&
		strnequ(&a->buff[i], &a->buff[label->i], label->len))
			return (label);
		label = label->next;
	}
	return (NULL);
}

/*
** Insert a token into the hash table. If the token is already present in the
** hash table, do not replace the old one.
*/

void			ht_insert(t_asm *a)
{
	t_label		*label;

	if (!(label = (t_label*)memalloc(sizeof(t_label))))
		sys_error(NULL);
	if (!ht_search(a))
	{
		*label = (t_label){.i = a->i, .len = a->j - a->i - 1,
		.byte_i = a->byte_i};
		label->next = a->ht[hash(&a->buff[label->i], label->len)];
		a->ht[hash(&a->buff[label->i], label->len)] = label;
	}
}

/*
** Free dynamic memory allocated for the each element of the hash table.
*/

void			ht_delete(t_asm *a)
{
	int		i;
	t_label	*label;
	t_label	*label_prev;

	i = 0;
	while (i < HASH_SIZE)
	{
		if ((label = a->ht[i++]))
		{
			while (label->next)
			{
				label_prev = label;
				label = label->next;
				memdel((void**)&label_prev);
			}
			memdel((void**)&label);
		}
	}
}
