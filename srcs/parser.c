/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 16:09:14 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/15 16:09:15 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#define BUFF_SIZE 4096

static t_vector		g_vec_null = {NULL, 0, 0, sizeof(struct s_map *)};
static t_vector		*g_vec = &g_vec_null;

static bool				add_room(t_lemin *lemin, const char *line,
						const t_flag flag)
{
	struct s_room		*room;

	if (ft_strchr(line, '-') || !(_NB + 1))
		GIMME(true);
	room = (struct s_room *)ft_wralloc(sizeof(struct s_room));
	lemin->debug_len = 0;
	while (line[lemin->debug_len] && line[lemin->debug_len] != ' ')
		++lemin->debug_len;
	room->name = ft_strndup(line, lemin->debug_len);
	if (!line[(lemin->debug_len += 1)] || !ft_isdigit(line[lemin->debug_len]))
		errhdl(lemin, NULL, line, E_ROOMNOXY);
	room->x = ft_atoi(&line[lemin->debug_len]);
	if (!line[(lemin->debug_len += ft_intlen(room->x) + 1)]
		|| !ft_isdigit(line[lemin->debug_len]))
		errhdl(lemin, NULL, line, E_ROOMNOY);
	room->y = ft_atoi(&line[lemin->debug_len]);
	if (line[lemin->debug_len + ft_intlen(room->y)])
		errhdl(lemin, NULL, line, E_ROOMZ);
	room->flag = flag;
	verif_entry(lemin, room, line);
	room->nb = _NB++;
	*(struct s_room **)ft_vecpush(g_vec) = room;
	_ROOM = g_vec->buff;
	KTHXBYE;
}

static t_flag			get_flag(t_lemin *lemin, char *line)
{
	copy_line(lemin, line);
	if (ft_strequ(line, "##start"))
	{
		if (_START != UINT32_MAX)
			errhdl(lemin, NULL, line, E_MULTISTART);
		_START = _NB;
		GIMME(E_START);
	}
	else if (ft_strequ(line, "##end"))
	{
		if (_END != UINT32_MAX)
			errhdl(lemin, NULL, line, E_MULTIEND);
		_END = _NB;
		GIMME(E_END);
	}
	GIMME(E_VOID);
}

static int				map_link(t_lemin *lemin, const char *line)
{
	char		n1[BUFF_SIZE];
	char		n2[BUFF_SIZE];
	int			k;
	int			a;
	int			b;

	ft_memnccpy(n1, line, (int)'-', BUFF_SIZE);
	ft_snprintf(n2, BUFF_SIZE, "%s", line + lemin->debug_len + 1);
	a = -1;
	b = -1;
	k = -1;
	while (++k < _NB)
	{
		if (ft_strequ(n1, _ROOM[k]->name))
			a = k;
		else if (ft_strequ(n2, _ROOM[k]->name))
			b = k;
	}
	if (a == -1 || b == -1)
		ONOES;
	_MATRIX[a][b] = true;
	_MATRIX[b][a] = true;
	KTHXBYE;
}

static int				do_matrix(t_lemin *lemin, const char *line)
{
	int		k;

	if (line[0] == '#')
		KTHXBYE;
	if (!_MATRIX)
	{
		_MATRIX = (bool **)ft_memalloc(sizeof(bool *) * _NB);
		k = -1;
		while (++k < _NB)
			_MATRIX[k] = (bool *)ft_memalloc(sizeof(bool) * _NB);
	}
	lemin->debug_len = 0;
	while (line[lemin->debug_len] && line[lemin->debug_len] != '-')
		++lemin->debug_len;
	if (!line[lemin->debug_len + 1] || map_link(lemin, line) == -1)
		ONOES;
	++_LINKS;
	KTHXBYE;
}

void					parse(t_lemin *lemin, bool links, t_flag flag)
{
	char		*line;

	get_next_line(STDIN_FILENO, &line);
	while (line[++lemin->debug_len])
		if (!ft_isdigit(line[lemin->debug_len]))
			errhdl(lemin, NULL, line, E_FIRSTLINE);
	if (ft_strlen(line) > 10 || (_ANTS = ft_atoi(line)) < 1)
		errhdl(lemin, NULL, line, E_FIRSTLINE);
	copy_line(lemin, line);
	while (get_next_line(STDIN_FILENO, &line))
	{
		if (!links && line[0] == '#' && (flag = get_flag(lemin, line)))
			MOAR;
		else if (line[0] == 'L' && !finish_read(lemin, line))
			NOMOAR;
		else if ((!links && (links = add_room(lemin, line, flag))) || links)
			if (do_matrix(lemin, line) == -1 && !finish_read(lemin, line))
				NOMOAR;
		flag = E_VOID;
		copy_line(lemin, line);
	}
	if (!lemin->links)
		errhdl(lemin, NULL, line, E_NOLINKS);
	if (line)
		ft_strdel(&line);
}
