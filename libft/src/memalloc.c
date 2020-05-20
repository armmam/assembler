#include <string.h>
#include "libft.h"

void	*memalloc(size_t size)
{
	void	*p;

	p = NULL;
	if (size && (p = malloc(size)))
		memset(p, 0, size);
	return (p);
}
