#include <fcntl.h>
#include <unistd.h>
#include "asm.h"
#include "libft.h"

static void	input_disasm(t_asm *a, int ac, char **av)
{
	(void)a;
	(void)ac;
	(void)av;
	ft_printf("nothing here yet!\n");
	exit(EXIT_SUCCESS);
}

static void	input_asm(t_asm *a)
{
	input_asm_header(a);
	input_asm_body(a);
	input_labels(a);
}

/*
** Perform basic input validation:
** - number of arguments and -d option are valid,
** - file name passed as an argument is valid,
** - file size is valid.
** If successful, invoke functions that deal with further asm/disasm input
** validation.
*/

void		input(t_asm *a, int ac, char **av)
{
	int	fd;
	int	r;

	r = 0;
	fd = 0;
	if ((ac == 2 && (fd = open(av[1], O_RDONLY)) >= 0) || (ac == 3 &&
	ft_strequ(av[1], "-d") && (fd = open(av[2], O_RDONLY)) >= 0))
	{
		if ((r = read(fd, a->buff, BUFF_SIZE)) > 0 &&
		(r = read(fd, a->buff, 1)) == 0)
			ac == 3 ? input_disasm(a, ac, av) : input_asm(a);
		else if (r == 0)
			error2(ac == 3 ? av[2] : av[1], " is empty.");
		else if (r > 0)
			error2(ac == 3 ? av[2] : av[1], " is too large.");
		else
			sys_error(ac == 3 ? av[2] : av[1]);
		close(fd);
	}
	else if (fd < 0)
		sys_error(ac == 3 ? av[2] : av[1]);
	else
		usage();
}
