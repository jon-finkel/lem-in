/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 20:56:08 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/07 16:12:58 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			main(int argc, const char *argv[])
{
	t_lemin		*lemin;

	if (!(lemin = (t_lemin *)ft_memalloc(sizeof(t_lemin))))
		ft_fatal("allocation failed");
	lemin->debug = usage(argc, argv);
	if (parse(lemin, false) == -1)
		ft_fatal("allocation failed");
	KTHXBYE;
}
