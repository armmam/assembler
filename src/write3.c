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

	dir = antoi(&a->buff[a->i + 1], a->j - a->i - 1);
	write_dirsize_bytes(a->fd, dir, dirsize);
}

void		write_ind(t_asm *a)
{
	short	ind;

	ind = antoi(&a->buff[a->i], a->j - a->i);
	write_bytes(a->fd, (t_byte*)&ind, IND_SIZE);
}

void		write_dir_label(t_asm *a, int dirsize)
{
	int		dir;
	t_label	*label;

	label = ht_search(a);
	dir = label->byte_i - a->byte_i;
	write_dirsize_bytes(a->fd, dir, dirsize);
}

void		write_ind_label(t_asm *a)
{
	short	ind;
	t_label	*label;

	label = ht_search(a);
	ind = label->byte_i - a->byte_i;
	write_bytes(a->fd, (t_byte*)&ind, IND_SIZE);
}