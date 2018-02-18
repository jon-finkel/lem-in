/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edkarp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 08:14:23 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/18 15:14:06 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#define _PATH_HEAD ((struct s_path *)(deque->head->data))
#define _PATH_TAIL ((struct s_path *)(deque->tail->data))
#define _POS _PATH_HEAD->rooms[_PATH_HEAD->len - 1]

static t_vector		g_vec_null = {NULL, 0, 0, sizeof(struct s_path *)};
static t_vector		*g_vec = &g_vec_null;

static void						dqtor(void *data, size_t data_size)
{
	ft_memset(data, '\0', data_size);
	free(data);
}

void		ft_deqdel(t_deque **adeq, t_dqtor dqtor)
{
	t_dlist		*head;
	t_dlist		*tmp;

	head = (*adeq)->head;
	while (head)
	{
		tmp = head;
		head = head->next;
		dqtor(tmp->data, tmp->data_size);
		free(tmp);
	}
	free(*adeq);
}

static struct s_path			*clear_deque(t_deque *deque)
{
	struct s_path		*path;

	path = (struct s_path *)ft_memalloc(sizeof(struct s_path));
	ft_memmove(path, _PATH_TAIL, sizeof(*_PATH_TAIL));
	ft_deqdel(&deque, (t_dqtor)&dqtor);
	GIMME(path);
}

static struct s_path			*bfs(const t_lemin *lemin, const uint16_t start)
{
	uint16_t			k;
	struct s_path		*path;
	t_deque				*deque;

	deque = (t_deque *)ft_memalloc(sizeof(t_deque));
	path = (struct s_path *)ft_memalloc(sizeof(struct s_path));
	path->rooms[path->len++] = start;
	_CHECK[start] = true;
	ft_deqadd(deque, ft_dlstnew(path, sizeof(*path)));
	free(path);
	while (deque->head && (k = -1))
	{
		while (++k < _NB)
			if (_MATRIX[_POS][k] && _CHECK[k] == false)
			{
				ft_deqappend(deque, ft_dlstnew(_PATH_HEAD, sizeof(*_PATH_HEAD)));
				_PATH_TAIL->rooms[_PATH_TAIL->len++] = k;
				_CHECK[k] = true;
				if (k == _END)
					GIMME(clear_deque(deque));
			}
		ft_deqpop(deque, (t_dqtor)&dqtor);
	}
	ft_memdel((void **)&deque);
	ZOMG;
}

void							edkarp(t_lemin *lemin)
{
	struct s_path		*path;

	if (!(path = bfs(lemin, _START)))
		errhdl(lemin, NULL, NULL, E_NOSOLUTION);
	*(struct s_path **)ft_vecpush(g_vec) = path;
	_PATH = g_vec->buff;
}
