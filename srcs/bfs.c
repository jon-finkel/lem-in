/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 17:15:58 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/24 17:20:34 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

#define _HEAD ((t_path *)(deq->head->data))
#define _TAIL ((t_path *)(deq->tail->data))
#define _POS _HEAD->rooms[_HEAD->len - 1]

static t_path			*clear_deq(t_lemin *lemin, t_deque *deq,
						const t_flag flag)
{
	uint16_t		k;
	t_path			*path;

	if (_TAIL->len == 2 && !_TP)
			_TP = true;
	else if (_TAIL->len == 2 && _TP)
	{
		ft_deqdel(&deq, dqtor);
		ZOMG;
	}
	path = (t_path *)ft_memalloc(sizeof(t_path));
	ft_memmove(path, _TAIL, sizeof(*_TAIL));
	ft_deqdel(&deq, dqtor);
	k = -1;
	while (++k < path->len - 1)
		_CHECK[path->rooms[k]] = true;
	if (flag != E_REDIRECT)
	{
		_MOVES += path->len - 2;
		++_VALID_PATHS;
	}
	GIMME(path);
}

static bool				is_hit(t_lemin *lemin, bool *check, const uint16_t x)
{
	bool			stop;
	uint16_t		p;
	uintmax_t		k;

	stop = false;
	if (check[x] == false)
		GIMME(false);
	else if (!_MATRIX[_START][x] && x != _START && _CHECK[x] == true)
	{
		if (_HIT == false && (k = -1))
			while (stop == false && _PATH[++k] && (p = -1))
				while (stop == false && ++p < _PATH[k]->len)
					if (x == _PATH[k]->rooms[p] && (stop = true))
					{
						_HIT_X = p;
						_HIT_PATH = k;
					}
		_HIT = true;
	}
	GIMME(true);
}

t_path					*bfs(t_lemin *lemin, bool *check, const t_flag flag)
{
	t_deque			*deq;
	t_path			*path;
	uint16_t		k;

	deq = (t_deque *)ft_memalloc(sizeof(t_deque));
	path = (t_path *)ft_memalloc(sizeof(t_path));
	path->rooms[path->len++] = _START;
	ft_deqadd(deq, ft_dlstnew(path, sizeof(*path)));
	free(path);
	while (deq->head && (k = -1))
	{
		while (++k < _NB)
			if (_MATRIX[_POS][k] && !is_hit(lemin, check, k))
			{
				ft_deqappend(deq, ft_dlstnew(_HEAD, sizeof(*_HEAD)));
				_TAIL->rooms[_TAIL->len++] = k;
				if (k == _END)
					GIMME(clear_deq(lemin, deq, flag));
				check[k] = true;
			}
		ft_deqpop(deq, dqtor);
	}
	ft_memdel((void **)&deq);
	ZOMG;
}
