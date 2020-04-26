#include "asm.h"
#include "libft.h"

int		main(int ac, char **av)
{
	(void)ac;
	(void)av;
	if (ac == 2)
	{
		ft_printf("hello, world!\n");
	}
	else
		ft_printf("usage: ./asm file\n");
	return (0);
}
