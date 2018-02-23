/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:51:49 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/23 18:48:37 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

#define _POS _PATH[k]->rooms[p]
#define _P_LEN(x) _PATH[(x)]->len
#define _TARGET _PATH[k]->rooms[p + 1]

static bool			check_ant(const t_lemin *lemin, int *ants, uint16_t *colony,
					const int x)
{
	uint16_t		k;
	uint16_t		p;

	k = -1;
	while (_PATH[++k] && (p = -1))
	{
		if (k > 0 && colony[x] == _START && _P_LEN(k) > *ants + _P_LEN(0))
			NOMOAR;
		while (++p < _PATH[k]->len)
			if (colony[x] == _POS && (!_CHECK[_TARGET] || _TARGET == _END))
			{
				colony[x] == _START ? --(*ants) : 0;
				_CHECK[colony[x]] = false;
				colony[x] = _TARGET;
				_CHECK[colony[x]] = true;
				ft_printf("L%d-%r ", x + 1, _ROOM[_TARGET]->name);
				if (colony[x] == _END)
					GIMME(true);
				else
					GIMME(false);
			}
	}
	GIMME(false);
}

void				move(const t_lemin *lemin, int ants)
{
	int				k;
	int				p;
	int				nb;
	uint16_t		*colony;

	nb = _ANTS;
	colony = (uint16_t *)ft_wralloc(sizeof(uint16_t) * _ANTS);
	k = -1;
	while (++k < ants)
		colony[k] = _START;
	ft_memset(_CHECK, false, _NB);
	while (ants && (k = write(STDOUT_FILENO, "\n", 1) - 2))
		while (++k < lemin->ants)
			if (colony[k] != _END && (p = -1))
				if (check_ant(lemin, &nb, colony, k) == true)
					--ants;
	write(STDOUT_FILENO, "\n", 1);
	free(colony);
}
