#include "asm.h"
#include "libft.h"
#include <unistd.h>

int		antoi(char *nptr, int n)
{
	char	end;
	int		res;

	nptr += n;
	end = *nptr;
	*nptr = '\0';
	nptr -= n;
	res = ft_atoi(nptr);
	nptr += n;
	*nptr = end;
	return (res);
}

void	write_dirsize_bytes(int fd, int dir, int dirsize)
{
	short	ind;

	ind = dir;
	if (dirsize == DIR_SIZE)
		write_bytes(fd, (t_byte*)&dir, dirsize);
	else
		write_bytes(fd, (t_byte*)&ind, dirsize);
}

void	write_typebyte(int fd, t_op op, int *byte_i, t_byte typebyte)
{
	if (op.typebyte)
	{
		lseek(fd, -(*byte_i - 1), SEEK_CUR);
		write(fd, &typebyte, sizeof(t_byte));
		lseek(fd, *byte_i - 2, SEEK_CUR);
	}
}
