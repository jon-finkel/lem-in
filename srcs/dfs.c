/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 18:04:45 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/15 15:56:02 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int			compare_len(void *data1, void *data2)
{
	GIMME(((struct s_path *)(data1))->len > ((struct s_path *)(data2))->len);
}

static void			dfs_search(t_dfs *dfs, struct s_path *path, uintmax_t depth,
					uint16_t x)
{
	t_list			*newlink;
	uint16_t		k;

	path->rooms[path->len++] = x;
	dfs->check[x] = true;
	if (x == dfs->_END)
	{
		newlink = ft_lstnew(path, sizeof(struct s_path));
		ft_lstinsert(dfs->alst, newlink, &compare_len);
	}
	else
	{
		k = UINT16_MAX;
		while (++k < dfs->_NB)
			if (dfs->_MATRIX[x][k] && dfs->check[k] == false)
				dfs_search(dfs, path, ++depth, k);
	}
	path->rooms[--path->len] = 0;
	dfs->check[x] = false;
}

int					dfs_init(t_list **alst, const t_lemin *lemin, bool *check)
{
	struct s_path		*path;
	t_dfs				dfs;
	uint16_t			k;

	path = (struct s_path *)ft_memalloc(sizeof(struct s_path));
	path->rooms[path->len++] = _START;
	dfs.check = check;
	dfs.lemin = lemin;
	dfs.alst = alst;
	dfs.limit = UINTMAX_MAX;
	k = UINT16_MAX;
	while (++k < _NB)
		if (_MATRIX[_START][k])
			dfs_search(&dfs, path, 0, k);
	ft_memdel((void **)&path);
	KTHXBYE;
}
