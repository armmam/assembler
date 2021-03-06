#include <unistd.h>
#include <stdio.h>
#include "asm.h"

void		disasm_write_reg(t_asm *a)
{
	short	reg;

	disasm_check_eof(a);
	reg = a->code[a->i++];
	dprintf(a->fd, "r%hd", reg);
}

void		disasm_write_dir(t_asm *a)
{
	int		dir;
	short	ind;

	disasm_check_eof(a);
	dir = 0;
	ind = 0;
	if (a->op.dirsize == DIR_SIZE &&
	a->i + DIR_SIZE <= (int)a->header.prog_size)
	{
		byte_swap((t_byte*)&a->code[a->i], DIR_SIZE);
		dir = bntoi((t_byte*)&a->code[a->i], DIR_SIZE);
		dprintf(a->fd, "%%%d", dir);
		a->i += DIR_SIZE;
	}
	else if (a->op.dirsize == IND_SIZE &&
	a->i + IND_SIZE <= (int)a->header.prog_size)
	{
		byte_swap((t_byte*)&a->code[a->i], IND_SIZE);
		ind = bntoi((t_byte*)&a->code[a->i], IND_SIZE);
		dprintf(a->fd, "%%%hd", ind);
		a->i += IND_SIZE;
	}
	else
		error("File ended unexpectedly.");
}

void		disasm_write_ind(t_asm *a)
{
	short	ind;

	disasm_check_eof(a);
	if (a->i + IND_SIZE <= (int)a->header.prog_size)
	{
		byte_swap((t_byte*)&a->code[a->i], IND_SIZE);
		ind = bntoi((t_byte*)&a->code[a->i], IND_SIZE);
		dprintf(a->fd, "%hd", ind);
		a->i += IND_SIZE;
	}
	else
		error("File ended unexpectedly.");
}
