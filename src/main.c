#include "asm.h"
#include "libft.h"

int		main(int ac, char **av)
{
	t_asm	a;

	ft_bzero(&a, sizeof(t_asm));
	check_invariants();
	input(&a, ac, av);
	output(&a, ac, av);
	return (0);
}
