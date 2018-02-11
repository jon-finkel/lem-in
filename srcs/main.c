/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 20:56:08 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/11 19:06:26 by nfinkel          ###   ########.fr       */
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
	ft_lstdel(&list, &ft_lstfree);
}

static bool			check_collision(const t_lemin *lemin, struct s_path *path)
{
	uint16_t		k;
	uint16_t		p;
	uint16_t		q;

	if (!_PATH)
		KTHXBYE;
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
	struct s_path		**ptr;

	while (list)
	{
		if (!check_collision(lemin, _LIST))
		{
			FAILZ(ptr = (struct s_path **)ft_vecpush(g_vec), -1);
			*ptr = _LIST;
			_PATH = g_vec->buff;
		}
		list = list->next;
	}
	KTHXBYE;
}

int					main(int argc, const char *argv[])
{
	t_list		*list;
	t_lemin		*lemin;

	if (!(lemin = (t_lemin *)ft_memalloc(sizeof(t_lemin))))
		ft_fatal("allocation failed");
	_DEBUG = usage(argc, argv);
	_END = UINT32_MAX;
	_START = UINT32_MAX;
	list = NULL;
	if (!(lemin->file = ft_strnew(0)) || parse(lemin, false, E_VOID)
		|| dfs_init(&list, lemin) == -1)
		ft_fatal("allocation failed");
	if (!list)
		errhdl(lemin, NULL, NULL, E_NOSOLUTION);
	if (choose_path(lemin, list) == -1)
		ft_fatal("allocation failed");
	print_debug_and_clean(list, lemin);
	KTHXBYE;
}
