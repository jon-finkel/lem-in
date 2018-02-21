/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edkarp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 08:14:23 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/20 20:25:56 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#define _HEAD ((struct s_path *)(deque->head->data))
#define _TAIL ((struct s_path *)(deque->tail->data))
#define _POS _HEAD->rooms[_HEAD->len - 1]

static t_vector		g_vec_null = {NULL, 0, 0, sizeof(struct s_path *)};
static t_vector		*g_vec = &g_vec_null;

static struct s_path			*clear_deq(const t_lemin *lemin, t_deque *deque)
{
	uint16_t			k;
	struct s_path		*path;

	path = (struct s_path *)ft_memalloc(sizeof(struct s_path));
	ft_memmove(path, _TAIL, sizeof(*_TAIL));
	ft_deqdel(&deque, dqtor);
	k = -1;
	while (++k < path->len - 1)
		_CHECK[path->rooms[k]] = true;
	GIMME(path);
}

static struct s_path			*bfs(const t_lemin *lemin, const uint16_t start,
								bool *check)
{
	uint16_t			k;
	struct s_path		*path;
	t_deque				*deque;

	deque = (t_deque *)ft_memalloc(sizeof(t_deque));
	path = (struct s_path *)ft_memalloc(sizeof(struct s_path));
	path->rooms[path->len++] = start;
	check[start] = true;
	ft_deqadd(deque, ft_dlstnew(path, sizeof(*path)));
	free(path);
	while (deque->head && (k = -1))
	{
		while (++k < _NB)
			if (_MATRIX[_POS][k] && check[k] == false)
			{
				ft_deqappend(deque, ft_dlstnew(_HEAD, sizeof(*_HEAD)));
				_TAIL->rooms[_TAIL->len++] = k;
				check[k] = true;
				if (k == _END)
					GIMME(clear_deq(lemin, deque));
			}
		ft_deqpop(deque, dqtor);
	}
	ft_memdel((void **)&deque);
	ZOMG;
}

void							edkarp(t_lemin *lemin)
{
	bool				check[_NB];
	uint16_t			k;
	struct s_path		*path;

	k = -1;
	while (++k < _NB)
		if (_MATRIX[_START][k])
		{
			ft_memset(check, '\0', sizeof(bool) * _NB);
			ft_memmove(check, _CHECK, sizeof(bool) * _NB);
			if ((path = bfs(lemin, _START, check)))
				*(struct s_path **)ft_vecpush(g_vec) = path;
		}
	if (!(_PATH = g_vec->buff))
		errhdl(lemin, NULL, NULL, E_NOSOLUTION);
}
