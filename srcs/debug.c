/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 22:12:52 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/08 21:32:52 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static const char		*g_debug[5] =
{
	"---------- DEBUG MODE ENABLED ----------",
	"- Data:",
	"- Rooms ID:",
	"- Adjacency matrix:",
	"0 1 2 3 4 5 6 7 8 9 "
};

static void			display_matrix(const t_lemin *lemin, size_t len, int k,
					int p)
{
	uint16_t	nb;

	ft_printf("\n{1c}%s{eoc}\n\n%*.c", g_debug[3], len, ' ');
	nb = _NB;
	while (nb >= 10 && ft_printf("%s", g_debug[4]))
		nb -= 10;
	ft_printf("%.*s\n%*c", nb * 2 % 20, g_debug[4], len - 1, ' ');
	while (++k < _NB)
		ft_printf(" -");
	k = -1;
	len -= 3;
	while (++k < _NB)
	{
		ft_printf("\n%0*d |", len, k);
		p = -1;
		while (++p < _NB)
		{
			if (_MATRIX[k][p])
				ft_printf(" {1c}1{eoc}");
			else
				ft_printf(" {1a}0{eoc}");
		}
	}
	write(STDOUT_FILENO, "\n", 1);
}

static void			display_rooms(const t_lemin *lemin, const size_t len)
{
	int		k;

	ft_printf("{1c}%s{eoc}\n\n", g_debug[1]);
	ft_printf("Number of ants - %d\n", _ANTS);
	ft_printf("Number of rooms - %hu\n", _NB);
	ft_printf("Number of links - %zu\n", _LINKS);
	ft_printf("\n{1c}%s{eoc}\n\n", g_debug[2]);
	k = -1;
	while (++k < _NB)
	{
		if (_ROOM[k]->flag == E_START)
			ft_printf("{4c}%.*hu{eoc} : {4c}%s{eoc}\n", len, k, _ROOM[k]->name);
		else if (_ROOM[k]->flag == E_END)
			ft_printf("{4C}%.*hu{eoc} : {4C}%s{eoc}\n", len, k, _ROOM[k]->name);
		else
			ft_printf("%.*hu : %s\n", len, k, _ROOM[k]->name);
	}
}

void				debug_output(t_lemin *lemin)
{
	if (!_DEBUG)
		BYEZ;
	ft_printf("\n{c}%s{eoc}\n\n", g_debug[0]);
	display_rooms(lemin, ft_intlen(_NB));
	display_matrix(lemin, ft_intlen(_NB) + 3, -1, -1);
}
