#include "asm.h"
#include "libft.h"

static unsigned	hash(char *s, unsigned n)
{
	unsigned	hash_val;

	hash_val = 0;
	while (n--)
		hash_val = *s + 31 * hash_val;
	return (hash_val);
}

/*
** Search for a token in the hash table. If the token is not present in the
** hast table, return NULL (the function that invoked this one should exit in
** this case).
*/

t_label			*ht_search(t_asm *a)
{
	t_label	*label;

	label = a->ht[hash(&a->buff[a->i], a->j - a->i)];
	while (label)
	{
		if (a->j - a->i == label->len &&
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
	static t_label	label;
	unsigned		hash_val;

	if (ht_search(a) == NULL)
	{
		label = (t_label){.i = a->i, .len = a->j - a->i, .byte_i = a->byte_i};
		hash_val = hash(&a->buff[label.i], label.len);
		label.next = a->ht[hash_val];
		a->ht[hash(&a->buff[label.i], label.len)] = &label;
	}
}
