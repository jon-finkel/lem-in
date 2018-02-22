/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edkarp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 08:14:23 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/22 12:56:23 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#define _HEAD ((t_path *)(deq->head->data))
#define _TAIL ((t_path *)(deq->tail->data))
#define _POS _HEAD->rooms[_HEAD->len - 1]
#define _LEN_P1_P2 (path1->len - 2 + path2->len - 2)
#define _LEN_HIT (_PATH[_HIT_PATH]->len - 2)
#define _NEW_MOVES (_MOVES - _LEN_HIT + _LEN_P1_P2)
#define _NEW_FLOW ((_ANTS + _NEW_MOVES) / (_VALID_PATHS + 1))
#define _OLD_FLOW ((_ANTS + _MOVES) / _VALID_PATHS)

static t_vector		g_vec_null = {NULL, 0, 0, sizeof(t_path *)};
static t_vector		*g_vec = &g_vec_null;

static t_path			*clear_deq(t_lemin *lemin, t_deque *deq, t_flag flag)
{
	uint16_t		k;
	t_path			*path;

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
	else if (x != _START && _CHECK[x] == true)
	{
		if (_HIT == false && (k = -1))
			while (stop == false && _PATH[++k] && (p = -1))
				while (stop == false && ++p < _PATH[k]->len)
					if (x == _PATH[k]->rooms[p] && (stop = true))
						_HIT_PATH = k;
		_HIT = true;
	}
	GIMME(true);
}

static t_path			*bfs(t_lemin *lemin, bool *check, const uint16_t begin,
						t_flag flag)
{
	t_deque			*deq;
	t_path			*path;
	uint16_t		k;

	deq = (t_deque *)ft_memalloc(sizeof(t_deque));
	path = (t_path *)ft_memalloc(sizeof(t_path));
	path->rooms[path->len++] = _START;
	begin != _END ? path->rooms[path->len++] = begin : 0;
	ft_deqadd(deq, ft_dlstnew(path, sizeof(*path)));
	free(path);
	while (deq->head && (k = -1))
	{
		while (++k < _NB)
			if ((_MATRIX[_POS][k] && !is_hit(lemin, check, k)) || begin == _END)
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

static t_path			*redirect_flow(t_lemin *lemin, bool *check,
						const uint16_t begin1)
{
	bool			backup[_NB];
	t_path			*path1;
	t_path			*path2;
	uint16_t		k;

	ft_memmove(backup, _CHECK, sizeof(bool) * _NB);
	k = 0;
	while (++k < _PATH[_HIT_PATH]->len)
		_CHECK[_PATH[_HIT_PATH]->rooms[k]] = false;
	ft_memmove(check, _CHECK, sizeof(bool) * _NB);
	path1 = bfs(lemin, check, begin1, E_REDIRECT);
	ft_memmove(check, _CHECK, sizeof(bool) * _NB);
	if ((path2 = bfs(lemin, check, _PATH[_HIT_PATH]->rooms[1], E_REDIRECT))
		&& _NEW_FLOW < _OLD_FLOW)
	{
			_MOVES = _NEW_MOVES;
			++_VALID_PATHS;
			ft_memmove(_PATH[_HIT_PATH], path2, sizeof(t_path));
			free(path2);
			GIMME(path1);
	}
	free(path1);
	ft_memmove(_CHECK, backup, sizeof(bool) * _NB);
	ZOMG;
}

void					edmonds_karp(t_lemin *lemin)
{
	bool			check[_NB];
	uint16_t		k;
	t_path			*path;

	k = -1;
	while (++k < _NB)
		if (_MATRIX[_START][k])
		{
			ft_memmove(check, _CHECK, sizeof(bool) * _NB);
			check[k] = true;
			_HIT = false;
			if ((path = bfs(lemin, check, k, E_VOID))
				|| (_HIT && (path = redirect_flow(lemin, check, k))))
				*(t_path **)ft_vecpush(g_vec) = path;
			_PATH = g_vec->buff;
		}
	if (!_PATH)
		errhdl(lemin, NULL, NULL, E_NOSOLUTION);
}
