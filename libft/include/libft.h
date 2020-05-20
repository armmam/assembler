#ifndef LIBFT_H
# define LIBFT_H
#include <stdlib.h>

void			*memalloc(size_t size);
void			memdel(void **ap);
int				strequ(char const *s1, char const *s2);
int				strnequ(char const *s1, char const *s2, size_t n);
char			*strjoin(char const *s1, char const *s2);
int				strnnum(const char *s, int num);

#endif
