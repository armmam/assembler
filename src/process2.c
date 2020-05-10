/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brika <brika@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:37:35 by brika             #+#    #+#             */
/*   Updated: 2020/05/10 17:55:38 by brika            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

int			arg_size(t_asm *a, const t_op *op)
{
	if (a->token == REGISTER)
		return (REG_NUM_SIZE);
	else if (a->token == INDIRECT || a->token == INDIRECT_LABEL)
		return (IND_SIZE);
	else
		return (op->dirsize);
}

/*
** Check that INSTRUCTION has a valid number of arguments, valid argument syntax
** and no other instructions on the same line.
*/

static void	input_instruction(t_asm *a)
{
	int			i;
	int			j;

	i = 1;
	while (i <= INSTR_NUM &&
	!ft_strnequ(&a->buff[a->i], g_tab[i].name, a->j - a->i))
		++i;
	if (i > INSTR_NUM)
		error3("Invalid instruction", a);
	++a->byte_i;
	if (g_tab[i].typebyte)
		++a->byte_i;
	j = 0;
	while (j < g_tab[i].argnum)
	{
		if (j != 0 && tokenize(a) != SEPARATOR)
			error3("Expected separator", a);
		if (tokenize(a) & g_tab[i].args[j] || (a->token == DIRECT_LABEL &&
		DIRECT & g_tab[i].args[j]) || (a->token == INDIRECT_LABEL &&
		INDIRECT & g_tab[i].args[j]))
			a->byte_i += arg_size(a, &g_tab[i]);
		else
			error3("Invalid argument", a);
		++j;
	}
}

/*
** Check that every LABEL is at the beginning of a line, there is at most one
** INSTRUCTION per line (each of which is also whether at the beginning of a
** line or right after LABEL), each one is followed with a valid number and
** types of arguments, all separated from each other with SEPARATOR_CHAR.
** Record each LABEL name and the number of a byte it points to into a hash
** table.
*/

void		input_asm_body(t_asm *a)
{
	while (tokenize(a) != END)
	{
		if (a->token != LABEL && a->token != INSTRUCTION &&
		a->token != ENDLINE)
			error3("Expected another line start", a);
		if (a->token == LABEL)
		{
			ht_insert(a);
			tokenize(a);
		}
		if (a->token == INSTRUCTION)
		{
			input_instruction(a);
			tokenize(a);
		}
		if (a->token != ENDLINE)
			error3("Expected newline", a);
	}
	a->header.prog_size = a->byte_i;
}

void		reset_indices(t_asm *a)
{
	a->i = 0;
	a->j = 0;
	a->nl = 0;
	a->nl_i = 0;
	a->byte_i = 0;
	a->token = 0;
}

/*
** Check that each label in DIRECT_LABEL and INDIRECT_LABEL has a corresponding
** LABEL somewhere in the file.
*/

void		input_labels(t_asm *a)
{
	reset_indices(a);
	while (tokenize(a) != END)
	{
		if (a->token == DIRECT_LABEL || a->token == INDIRECT_LABEL)
		{
			if (!ht_search(a))
				error3("Tried to dereference non-existing label", a);
		}
	}
}
