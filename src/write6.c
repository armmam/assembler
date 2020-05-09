#include "asm.h"
#include "libft.h"
#include <unistd.h>

void		disasm_write_reg(t_asm *a)
{
	short	reg;

	reg = a->code[a->i++];
	ft_dprintf(a->fd, "r%hd", reg);
	disasm_check_eof(a);
}

void		disasm_write_dir(t_asm *a)
{
	int		dir;

	dir = 0;
	if (g_tab[a->token].dirsize == DIR_SIZE &&
	a->i + DIR_SIZE <= (int)a->header.prog_size)
	{
		byte_swap((t_byte*)&a->code[a->i], DIR_SIZE);
		dir = bntoi((t_byte*)&a->code[a->i], DIR_SIZE);
	}
	else if (g_tab[a->token].dirsize == IND_SIZE &&
	a->i + IND_SIZE <= (int)a->header.prog_size)
	{
		byte_swap((t_byte*)&a->code[a->i], IND_SIZE);
		dir = bntoi((t_byte*)&a->code[a->i], IND_SIZE);
	}
	else
		error("File ended unexpectedly.");
	ft_dprintf(a->fd, "%d", dir);
}

void		disasm_write_ind(t_asm *a)
{
	short	ind;

	if (a->i + IND_SIZE <= (int)a->header.prog_size)
	{
		byte_swap((t_byte*)&a->code[a->i], IND_SIZE);
		ind = bntoi((t_byte*)&a->code[a->i], IND_SIZE);
		ft_dprintf(a->fd, "%hd", ind);
	}
	else
		error("File ended unexpectedly.");
}
