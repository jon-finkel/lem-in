/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 16:09:14 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/08 21:30:47 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_vector		g_vec_null = {NULL, 0, 0, sizeof(struct s_map *)};
t_vector		*g_vec = &g_vec_null;

static bool						add_room(t_lemin *lemin, const char *line,
								const t_flag flag)
{
	struct s_room		*room;
	struct s_room		**ptr;

	if ((ft_strchr(line, '-') || !(_NB + 1)) && (_ROOM = g_vec->buff))
		GIMME(true);
	if (!(room = (struct s_room *)malloc(sizeof(struct s_room))))
		ft_fatal("allocation failed");
	lemin->debug_len = 0;
	while (line[lemin->debug_len] && line[lemin->debug_len] != ' ')
		++lemin->debug_len;
	room->name = ft_strndup(line, lemin->debug_len);
	if (!line[(lemin->debug_len += 1)])
		errhdl(lemin, line, E_ROOMNOXY);
	room->x = ft_atoi(&line[lemin->debug_len]);
	lemin->debug_len += ft_intlen(room->x);
	if (!line[(lemin->debug_len += 1)])
		errhdl(lemin, line, E_ROOMNOY);
	room->y = ft_atoi(&line[lemin->debug_len]);
	room->flag = flag;
	room->nb = _NB++;
	if (!(ptr = (struct s_room **)ft_vecpush(g_vec)))
		ft_fatal("allocation failed");
	*ptr = room;
	KTHXBYE;
}

static inline t_flag			get_flag(char **line)
{
	t_flag		flag;

	flag = E_VOID;
	if (ft_strequ(*line, "##start"))
		flag = E_START;
	else if (ft_strequ(*line, "##end"))
		flag = E_END;
	ft_strdel(line);
	GIMME(flag);
}

static inline int				map_link(t_lemin *lemin, const char *line)
{
	int		k;
	int		a;
	int		b;

	a = -1;
	b = -1;
	k = -1;
	while (++k < _NB)
	{
		if (ft_strequ(line + lemin->debug_len + 1, _ROOM[k]->name))
			a = k;
		else if (ft_strnequ(line, _ROOM[k]->name, lemin->debug_len))
			b = k;
	}
	if (a == -1 || b == -1)
		ONOES;
	_MATRIX[a][b] = true;
	_MATRIX[b][a] = true;
	KTHXBYE;
}

static int						do_matrix(t_lemin *lemin, const char *line)
{
	int		k;

	if (line[0] == '#')
		KTHXBYE;
	if (!_MATRIX)
	{
		if (!(_MATRIX = (bool **)ft_memalloc(sizeof(bool *) * _NB)))
			ft_fatal("allocation failed");
		k = -1;
		while (++k < _NB)
			if (!(_MATRIX[k] = (bool *)ft_memalloc(sizeof(bool) * _NB)))
				ft_fatal("allocation failed");
	}
	lemin->debug_len = 0;
	while (line[lemin->debug_len] && line[lemin->debug_len] != '-')
		++lemin->debug_len;
	if (!line[lemin->debug_len + 1] || map_link(lemin, line) == -1)
		ONOES;
	++_LINKS;
	KTHXBYE;
}

int								parse(t_lemin *lemin, bool links, t_flag flag)
{
	char		*line;
	int			ret;

	EPICFAILZ(get_next_line(STDIN_FILENO, &line), -1);
	if ((_ANTS = ft_atoi(line)) < 1)
		errhdl(lemin, line, E_FIRSTLINE);
	ft_strdel(&line);
	while ((ret = get_next_line(STDIN_FILENO, &line)))
	{
		EPICFAILZ(ret, -1);
		if (!links && line[0] == '#' && (flag = get_flag(&line)))
			MOAR;
		if (line[0] == 'L')
			NOMOAR;
		else if ((!links && (links = add_room(lemin, line, flag)))
			|| links)
			if (do_matrix(lemin, line) == -1)
				NOMOAR;
		flag = E_VOID;
		ft_strdel(&line);
	}
	KTHXBYE;
}
