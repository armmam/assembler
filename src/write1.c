#include "asm.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

/*
** Write multibyte data into a file using big-endian ordering
*/

void	write_bytes(int fd, t_byte *bytes, int size)
{
	int		i;

	i = 0;
	bytes += size - 1;
	while (i++ < size)
	{
		write(fd, bytes, 1);
		if (i != size)
			--bytes;
	}
}

static void	write_asm(t_asm *a)
{
	(void)a;
}

/*
** Write contents of .s file as bytes into .cor file
*/

static void	write_bytecode(t_asm *a)
{
	reset_indices(a);
	write_bytecode_header(a);
	write_bytecode_body(a);
}

/*
** Try to create a file with the same filename as the old one but with .cor
** instead of .s or, if failed, with .cor appended to the old filename. If
** there already is a file with the new filename, overwrite it. Return file
** descriptor of the new file.
*/

static void	create_file(t_asm *a, int ac, char **av)
{
	int		i;
	char	*filename;
	char	*new_filename;

	filename = ac == 3 ? av[2] : av[1];
	i = ft_strlen(filename);
	while (--i >= 0 && filename[i] != '/')
		if (filename[i] == '.')
		{
			filename[i] = '\0';
			break ;
		}
	if (!(new_filename = ac == 3 ?
	ft_strjoin(filename, ".s") : ft_strjoin(filename, ".corr")))
		sys_error(NULL);
	if ((a->fd = open(new_filename, O_WRONLY | O_CREAT, 0644)) < 0)
		sys_error(new_filename);
	ft_memdel((void**)&new_filename);
}

/*
** Output bytecode or assembly code (if -d option is present) into a file
** created by create_file function.
*/

void		output(t_asm *a, int ac, char **av)
{
	create_file(a, ac, av);
	if (ac == 3)
		write_asm(a);
	else
		write_bytecode(a);
	close(a->fd);
}
