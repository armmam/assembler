#include <string.h>
#include <stdlib.h>

char			*strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*t;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = strlen(s1);
	len2 = strlen(s2);
	if (len1 + len2 < len1 || !(len1 + len2 + 1) ||
	!(str = (char*)malloc(len1 + len2 + 1)))
		return (NULL);
	t = str;
	while (*s1)
		*t++ = *s1++;
	while ((*t++ = *s2++))
		;
	return (str);
}
