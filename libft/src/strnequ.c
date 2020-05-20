#include <stdlib.h>

int		strnequ(char const *s1, char const *s2, size_t n)
{
	if (s1 == s2)
		return (1);
	if (!s1 || !s2)
		return (0);
	while (n && *s1 == *s2)
	{
		if (!*s1)
			return (1);
		--n;
		++s1;
		++s2;
	}
	return (!n);
}
