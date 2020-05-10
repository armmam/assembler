/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brika <brika@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:30:45 by sscarecr          #+#    #+#             */
/*   Updated: 2020/05/10 18:01:20 by brika            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "asm.h"

/*
** Corewar operations reference table.
*/

const t_op	g_tab[INSTR_NUM + 1] =
{
	{"", 0, 0, {0, 0, 0}, 0, 0},
	{"live", 0, 1, {T_DIR, 0, 0}, DIR_SIZE, 10},
	{"ld", 1, 2, {T_DIR | T_IND, T_REG, 0}, DIR_SIZE, 5},
	{"st", 1, 2, {T_REG, T_REG | T_IND, 0}, DIR_SIZE, 5},
	{"add", 1, 3, {T_REG, T_REG, T_REG}, DIR_SIZE, 10},
	{"sub", 1, 3, {T_REG, T_REG, T_REG}, DIR_SIZE, 10},
	{"and", 1, 3, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		DIR_SIZE, 6},
	{"or", 1, 3, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		DIR_SIZE, 6},
	{"xor", 1, 3, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		DIR_SIZE, 6},
	{"zjmp", 0, 1, {T_DIR, 0, 0}, IND_SIZE, 20},
	{"ldi", 1, 3, {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG}, IND_SIZE, 25},
	{"sti", 1, 3, {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR}, IND_SIZE, 25},
	{"fork", 0, 1, {T_DIR, 0, 0}, IND_SIZE, 800},
	{"lld", 1, 2, {T_DIR | T_IND, T_REG, 0}, DIR_SIZE, 10},
	{"lldi", 1, 3, {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG}, IND_SIZE,
		50},
	{"lfork", 0, 1, {T_DIR, 0, 0}, IND_SIZE, 1000},
	{"aff", 1, 1, {T_REG, 0, 0}, DIR_SIZE, 2}
};
