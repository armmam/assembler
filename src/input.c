#include <fcntl.h>
#include <unistd.h>
#include "asm.h"
#include "libft.h"

/*
** Perform basic disasm input validation:
** - file type is valid,
** - file size is valid.
*/

static void	input_disasm(t_asm *a, int fd, char *filename)
{
	int		r;

	if ((r = read(fd, &(a->header), sizeof(t_header))) < 0)
		sys_error(filename);
	byte_swap((t_byte*)&a->header.magic, sizeof(a->header.magic));
	byte_swap((t_byte*)&a->header.prog_size, sizeof(a->header.prog_size));
	if (r < (int)sizeof(t_header) || a->header.magic != COREWAR_EXEC_MAGIC)
		error2(filename, " has an invalid header.");
	if (a->header.prog_size > DISASM_BUFF_SIZE)
		error2(filename, " is too large.");
	if ((r = read(fd, a->code, a->header.prog_size + 1)) !=
	(int)a->header.prog_size)
		r < 0 ? sys_error(filename) :
		error2(filename, " has a wrong code size.");
}

/*
** Check that asm input file size is valid. If successful, invoke functions
** that deal with further asm input validation.
*/

static void	input_asm(t_asm *a, int fd, char *filename)
{
	int		r;

	if ((r = read(fd, a->buff, ASM_BUFF_SIZE)) > 0 &&
	(r = read(fd, a->buff, 1)) == 0)
	{
		input_asm_header(a);
		input_asm_body(a);
		input_labels(a);
	}
	else if (r == 0)
		error2(filename, " is empty.");
	else if (r > 0)
		error2(filename, " is too large.");
	else
		sys_error(filename);
}

/*
** Perform basic input validation:
** - number of arguments and -d option are valid,
** - file name passed as an argument is valid,
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
	strequ(av[1], "-d") && (fd = open(av[2], O_RDONLY)) >= 0))
	{
		if (ac == 2)
			input_asm(a, fd, av[1]);
		else
			input_disasm(a, fd, av[2]);
		close(fd);
	}
	else if (fd < 0)
		sys_error(ac == 3 ? av[2] : av[1]);
	else
		usage();
}
