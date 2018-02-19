/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:51:49 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/19 15:19:47 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#define _TARGET _PATH[k]->rooms[p + 1]

static bool			check_ant(const t_lemin *lemin, uint16_t *colony, int x)
{
	uint16_t		k;
	uint16_t		p;

	k = -1;
	while (_PATH[++k] && (p = -1))
		while (++p < _PATH[k]->len)
			if (colony[x] == _PATH[k]->rooms[p])
			{
				if (_TARGET != _END && _CHECK[_TARGET])
					MOAR;
				_CHECK[colony[x]] = false;
				colony[x] = _TARGET;
				_CHECK[colony[x]] = true;
				ft_printf("L%d-%s ", x + 1, _ROOM[_TARGET]->name);
				if (colony[x] == _END)
					GIMME(true);
				else
					GIMME(false);
			}
	GIMME(false);
}

void				move(const t_lemin *lemin)
{
	int				ants;
	int				k;
	uint16_t		colony[lemin->ants];

	ants = lemin->ants;
	ft_memset(colony, _START, ants * sizeof(uint16_t));
	ft_memset(_CHECK, false, _NB);
	while (ants)
	{
		k = -1;
		while (++k < lemin->ants)
			if (colony[k] != _END && check_ant(lemin, colony, k) == true)
				--ants;
		write(STDOUT_FILENO, "\n", 1);
	}
}
