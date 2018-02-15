/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:51:49 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/15 09:17:21 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#define _TARGET _PATH[k]->rooms[p + 1]

static bool			check_ant(const t_lemin *lemin, uint16_t *colony,
					bool *check, int x)
{
	uint16_t		k;
	uint16_t		p;

	k = UINT16_MAX;
	while (_PATH[++k] && (p = UINT16_MAX))
		while (++p < _PATH[k]->len)
			if (colony[x] == _PATH[k]->rooms[p])
			{
				if (_TARGET != _END && check[_TARGET])
					MOAR;
				check[colony[x]] = false;
				colony[x] = _TARGET;
				check[colony[x]] = true;
				ft_printf("L%d-%s ", x + 1, _ROOM[_TARGET]->name);
				if (colony[x] == _END)
					GIMME(true);
				else
					KTHXBYE;
			}
	KTHXBYE;
}

void				move(const t_lemin *lemin, bool *check)
{
	int				ants;
	int				k;
	uint16_t		colony[lemin->ants];

	ants = lemin->ants;
	ft_memset(colony, _START, ants * sizeof(uint16_t));
	while (ants)
	{
		k = -1;
		while (++k < lemin->ants)
			if (colony[k] != _END && check_ant(lemin, colony, check, k) == true)
				--ants;
		write(STDOUT_FILENO, "\n", 1);
	}
}
