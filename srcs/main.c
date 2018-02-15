/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 20:56:08 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/15 09:12:54 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static t_vector		g_vec_null = {NULL, 0, 0, sizeof(struct s_path *)};
static t_vector		*g_vec = &g_vec_null;

static void			print_debug_and_clean(t_list *list, t_lemin *lemin)
{
	uint16_t		k;

	ft_printf("%s\n", lemin->file);
	ft_strdel(&lemin->file);
	if (_DEBUG)
		debug_output(list, lemin);
	k = UINT16_MAX;
	while (++k < _NB)
		free(_MATRIX[k]);
	ft_memdel((void **)&_MATRIX);
}

static bool			check_collision(const t_lemin *lemin, struct s_path *path)
{
	uint16_t		k;
	uint16_t		p;
	uint16_t		q;

	k = 0;
	while (++k < path->len - 1)
	{
		p = UINT16_MAX;
		while (_PATH[++p])
		{
			q = 0;
			while (++q < _PATH[p]->len - 1)
				if (path->rooms[k] == _PATH[p]->rooms[q])
					GIMME(true);
		}
	}
	KTHXBYE;
}

static int			choose_path(t_lemin *lemin, const t_list *list)
{
	while (list)
	{
		if (!_PATH || !check_collision(lemin, _LIST))
		{
			*(struct s_path **)ft_vecpush(g_vec) = _LIST;
			_PATH = g_vec->buff;
		}
		list = list->next;
	}
	KTHXBYE;
}

int					main(int argc, const char *argv[])
{
	bool		*check;
	t_list		*list;
	t_lemin		*lemin;

	lemin = (t_lemin *)ft_memalloc(sizeof(t_lemin));
	_DEBUG = usage(argc, argv);
	_END = UINT32_MAX;
	_START = UINT32_MAX;
	list = NULL;
	lemin->file = ft_strnew(0);
	lemin->debug_len = -1;
	lemin->debug_line = 1;
	parse(lemin, false, E_VOID);
	check = (bool *)ft_memalloc(sizeof(bool) * _NB);
	check[_START] = true;
	dfs_init(&list, lemin, check);
	if (!list)
		errhdl(lemin, NULL, NULL, E_NOSOLUTION);
	choose_path(lemin, list);
	print_debug_and_clean(list, lemin);
	move(lemin, check);
	KTHXBYE;
}
