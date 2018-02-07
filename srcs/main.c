/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 20:56:08 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/07 22:12:46 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			main(int argc, const char *argv[])
{
	t_lemin		*lemin;

	if (!(lemin = (t_lemin *)ft_memalloc(sizeof(t_lemin))))
		ft_fatal("allocation failed");
	_DEBUG = usage(argc, argv);
	if (parse(lemin, false, E_VOID) == -1)
		ft_fatal("allocation failed");
	debug_output(lemin);
	KTHXBYE;
}
