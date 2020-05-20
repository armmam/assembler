#include <strings.h>
#include "asm.h"

int		main(int ac, char **av)
{
	t_asm	a;

	bzero(&a, sizeof(t_asm));
	check_invariants();
	input(&a, ac, av);
	output(&a, ac, av);
	return (0);
}
