/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edkarp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 08:14:23 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/24 20:47:14 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

#define _LEN_P1_P2 (path1->len - 2 + path2->len - 2)
#define _LEN_HIT (_PATH[_HIT_PATH]->len - 2)
#define _NEW_MOVES (_MOVES - _LEN_HIT + _LEN_P1_P2)
#define _NEW_FLOW ((_ANTS + _NEW_MOVES) / (_VALID_PATHS + 1))
#define _OLD_FLOW ((_ANTS + _MOVES) / _VALID_PATHS)

t_vector		g_paths_null = {NULL, 0, 0, sizeof(t_path *)};
t_vector		*g_paths = &g_paths_null;

static void				clear_check(t_lemin *lemin, const t_path *path, int k,
						const uint16_t stop)
{
	while (++k < stop)
		_CHECK[path->rooms[k]] = false;
}

static t_path			*redirect_flow(t_lemin *lemin, t_path *old, bool *check)
{
	bool			backup[_NB];
	t_path			*path1;
	t_path			*path2;

	ft_memmove(backup, _CHECK, sizeof(bool) * _NB);
	clear_check(lemin, _PATH[_HIT_PATH], _HIT_X - 1, _PATH[_HIT_PATH]->len);
	old ? clear_check(lemin, old, 0, old->len) : 0;
	ft_memmove(check, _CHECK, sizeof(bool) * _NB);
	path1 = bfs(lemin, check, E_REDIRECT);
	clear_check(lemin, _PATH[_HIT_PATH], -1, _HIT_X);
	ft_memmove(check, _CHECK, sizeof(bool) * _NB);
	if ((path2 = bfs(lemin, check, E_REDIRECT)) && _NEW_FLOW < _OLD_FLOW)
	{
		if (old)
			ft_memdel((void **)&old);
		_MOVES = _NEW_MOVES;
		++_VALID_PATHS;
		ft_memmove(_PATH[_HIT_PATH], path2, sizeof(t_path));
		ft_memdel((void **)&path2);
		GIMME(path1);
	}
	ft_memdel((void **)&path1);
	path2 ? ft_memdel((void **)&path2) : 0;
	ft_memmove(_CHECK, backup, sizeof(bool) * _NB);
	GIMME(old);
}

void					edmonds_karp(t_lemin *lemin)
{
	bool		check[_NB];
	t_path		*path;

	while (101010)
	{
		ft_memmove(check, _CHECK, sizeof(bool) * _NB);
		_HIT = false;
		if (((path = bfs(lemin, check, E_VOID)) && !_HIT)
			|| (_HIT && (path = redirect_flow(lemin, path, check))))
			*(t_path **)ft_vecpush(g_paths) = path;
		else
			NOMOAR;
		_PATH = g_paths->buff;
	}
	if (!_PATH)
		errhdl(lemin, NULL, NULL, E_NOSOLUTION);
}
