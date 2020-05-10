/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brika <brika@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:36:15 by brika             #+#    #+#             */
/*   Updated: 2020/05/10 17:44:20 by brika            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

int		main(int ac, char **av)
{
	t_asm	a;

	ft_bzero(&a, sizeof(t_asm));
	check_invariants();
	input(&a, ac, av);
	output(&a, ac, av);
	return (0);
}
