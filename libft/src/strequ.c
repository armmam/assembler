#include <string.h>

int		strequ(char const *s1, char const *s2)
{
	if (!s1 || !s2)
		return (0);
	if (!strcmp(s1, s2))
		return (1);
	return (0);
}
