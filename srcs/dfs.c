/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 18:04:45 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/11 17:37:55 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static inline int			compare_len(void *data1, void *data2)
{
	GIMME(((struct s_path *)(data1))->len > ((struct s_path *)(data2))->len);
}

static int					dfs_traversal(t_list **alst, const t_lemin *lemin,
							struct s_path *path, uint16_t x)
{
	t_list			*newlink;
	uint16_t		k;
	uint16_t		p;

	path->rooms[path->len++] = x;
	if (x == _END)
	{
		FAILZ(newlink = ft_lstnew(path, sizeof(struct s_path)), -1);
		ft_lstinsert(alst, newlink, &compare_len);
		path->rooms[--path->len] = 0;
		KTHXBYE;
	}
	k = UINT16_MAX;
	while (++k < _NB)
		if (_MATRIX[x][k])
		{
			p = UINT16_MAX;
			while (++p < path->len)
				if (path->rooms[p] == k)
					NOMOAR;
			if (p == path->len)
				dfs_traversal(alst, lemin, path, k);
		}
	path->rooms[--path->len] = 0;
	KTHXBYE;
}

int							dfs_init(t_list **alst, const t_lemin *lemin)
{
	struct s_path		*path;
	uint16_t			k;

	if (_START == UINT32_MAX)
		errhdl(lemin, NULL, NULL, E_NOSTART);
	if (_END == UINT32_MAX)
		errhdl(lemin, NULL, NULL, E_NOEND);
	k = UINT16_MAX;
	FAILZ(path = (struct s_path *)ft_memalloc(sizeof(struct s_path)), -1);
	path->rooms[path->len++] = _START;
	while (++k < _NB)
		if (_MATRIX[_START][k])
			dfs_traversal(alst, lemin, path, k);
	ft_memdel((void **)&path);
	KTHXBYE;
}
