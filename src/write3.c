#include "asm.h"
#include "libft.h"
#include <unistd.h>

void		write_reg(t_asm *a)
{
	t_byte	reg;

	reg = antoi(&a->buff[a->i + 1], a->j - a->i - 1);
	write(a->fd, &reg, REG_NUM_SIZE);
}

void		write_dir(t_asm *a, int dirsize)
{
	int		dir;
	short	ind;

	dir = antoi(&a->buff[a->i + 1],  a->j - a->i - 1);
	ind = dir;
	if (dirsize == DIR_SIZE)
		write_bytes(a->fd, (t_byte*)&dir, dirsize);
	else
		write_bytes(a->fd, (t_byte*)&ind, dirsize);
}

void		write_ind(t_asm *a)
{
	short	ind;

	ind = antoi(&a->buff[a->i + 1],  a->j - a->i - 1);
	write_bytes(a->fd, (t_byte*)&ind, IND_SIZE);
}

void		write_dir_label(t_asm *a, int dirsize)
{
	(void)a;
	(void)dirsize;
	// ht_search(a)
}

void		write_ind_label(t_asm *a)
{
	(void)a;
}
