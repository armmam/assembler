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
** hast table, return NULL (the function that invoked this one should exit in
** this case).
*/

t_label			*ht_search(t_asm *a)
{
	t_label	*label;

	label = a->ht[hash(&a->buff[a->i], a->j - a->i - 1)];
	while (label)
	{
		if (a->j - a->i - 1 == label->len &&
		ft_strnequ(&a->buff[a->i], &a->buff[label->i], label->len))
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

	if (!(label = (t_label*)ft_memalloc(sizeof(t_label))))
		sys_error(NULL);
	if (!ht_search(a))
	{
		*label = (t_label){.i = a->i, .len = a->j - a->i - 1,
		.byte_i = a->byte_i};
		label->next = a->ht[hash(&a->buff[label->i], label->len)];
		a->ht[hash(&a->buff[label->i], label->len)] = label;
	}
}
