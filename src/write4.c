#include <unistd.h>
#include <stdlib.h>
#include "asm.h"

int		antoi(char *nptr, int n)
{
	char	end;
	int		res;

	nptr += n;
	end = *nptr;
	*nptr = '\0';
	nptr -= n;
	res = atoi(nptr);
	nptr += n;
	*nptr = end;
	return (res);
}

int		bntoi(t_byte *byte, int n)
{
	int		mult;
	int		res;

	res = 0;
	mult = 1;
	while (n-- > 0)
	{
		res += *byte * mult;
		mult <<= 8;
		++byte;
	}
	return (res);
}

void	asm_write_dirsize_bytes(int fd, int dir, int dirsize)
{
	short	ind;

	ind = dir;
	byte_swap((t_byte*)&dir, DIR_SIZE);
	byte_swap((t_byte*)&ind, IND_SIZE);
	if (dirsize == DIR_SIZE)
		write(fd, (t_byte*)&dir, dirsize);
	else
		write(fd, (t_byte*)&ind, dirsize);
}

void	asm_write_typebyte(int fd, t_op op, int *byte_i, t_byte typebyte)
{
	if (op.typebyte)
	{
		lseek(fd, -(*byte_i - 1), SEEK_CUR);
		write(fd, &typebyte, sizeof(t_byte));
		lseek(fd, *byte_i - 2, SEEK_CUR);
	}
}
