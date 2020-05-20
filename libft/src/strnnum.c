#include <ctype.h>

int		strnnum(const char *s, int num)
{
	if (!s)
		return (0);
	while (num && *s)
	{
		if (!isdigit(*s))
			return (0);
		--num;
		++s;
	}
	return (1);
}