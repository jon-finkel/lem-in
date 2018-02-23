/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 22:12:52 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/23 18:11:00 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static const char		*g_debug[8] =
{
	"---------- DEBUG MODE ENABLED ----------\n",
	"- Data:\n",
	"- Rooms ID:\n",
	"- Adjacency matrix:\n",
	"0 1 2 3 4 5 6 7 8 9 ",
	"- Possible paths:\n",
	"- Chosen path(s):\n",
	"---------- END OF DEBUG MODE -----------\n"
};

static void			display_matrix(const t_lemin *lemin, size_t len)
{
	uint16_t	nb;
	uint16_t	k;
	uint16_t	p;

	ft_printf("\n{1c}%s{eoc}\n%*.c", g_debug[3], len, ' ');
	nb = _NB;
	while (nb >= 10 && ft_printf("%s", g_debug[4]))
		nb -= 10;
	ft_printf("%.*s\n%*c", nb * 2 % 20, g_debug[4], len - 1, ' ');
	k = -1;
	while (++k < _NB)
		ft_printf(" -");
	k = -1;
	len -= 3;
	while (++k < _NB && (p = -1) && ft_printf("\n%0*d |", len, k))
		while (++p < _NB)
		{
			if (_MATRIX[k][p])
				ft_printf(" {1c}1{eoc}");
			else
				ft_printf(" {1a}0{eoc}");
		}
	write(STDOUT_FILENO, "\n", 1);
}

static void			display_rooms(const t_lemin *lemin, const size_t len)
{
	int		k;

	ft_printf("\n{1c}%s{eoc}\n", g_debug[2]);
	k = -1;
	while (++k < _NB)
	{
		if (_ROOM[k]->flag == E_START)
			ft_printf("{4c}%.*hu{eoc} : {4c}%r{eoc}\n", len, k, _ROOM[k]->name);
		else if (_ROOM[k]->flag == E_END)
			ft_printf("{4C}%.*hu{eoc} : {4C}%r{eoc}\n", len, k, _ROOM[k]->name);
		else
			ft_printf("%.*hu : %s\n", len, k, _ROOM[k]->name);
	}
}

void				debug_output(const t_lemin *lemin)
{
	uintmax_t		k;
	uint16_t		p;

	ft_printf("\n{c}%s{eoc}\n", g_debug[0]);
	ft_printf("{1c}%s{eoc}\n", g_debug[1]);
	ft_printf("Number of ants - %d\n", _ANTS);
	ft_printf("Number of rooms - %hu\n", _NB);
	ft_printf("Number of links - %zu\n", _LINKS);
	if (!_DEBUG_MATRIX)
	{
		display_rooms(lemin, ft_intlen(_NB));
		display_matrix(lemin, ft_intlen(_NB) + 3);
	}
	ft_printf("\n{1c}%s{eoc}\n", g_debug[6]);
	k = -1;
	while (_PATH[++k] && (p = -1))
		while (++p < _PATH[k]->len)
		{
			ft_printf("%r ", _ROOM[_PATH[k]->rooms[p]]->name);
			if (p < _PATH[k]->len - 1)
				ft_printf("{1a}->{eoc} ");
			else
				write(STDOUT_FILENO, "\n", 1);
		}
	ft_printf("\n{c}%s{eoc}", g_debug[7]);
}
