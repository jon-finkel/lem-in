/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 16:09:14 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/12 19:35:42 by nfinkel          ###   ########.fr       */
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
	if (!line[(lemin->debug_len += 1)])
		errhdl(lemin, NULL, line, E_ROOMNOXY);
	room->x = ft_atoi(&line[lemin->debug_len]);
	if (!line[(lemin->debug_len += ft_intlen(room->x) + 1)])
		errhdl(lemin, NULL, line, E_ROOMNOY);
	room->y = ft_atoi(&line[lemin->debug_len]);
	room->flag = flag;
	verif_entry(lemin, room, line);
	room->nb = _NB++;
	*(struct s_room **)ft_vecpush(g_vec) = room;
	_ROOM = g_vec->buff;
	KTHXBYE;
}

static t_flag			get_flag(t_lemin *lemin, char *line)
{
	uint16_t		k;
	t_flag			flag;

	flag = E_VOID;
	if (ft_strequ(line, "##start"))
	{
		k = UINT16_MAX;
		while (++k < _NB)
			if (_ROOM[k]->flag == E_START)
				errhdl(lemin, _ROOM[k], line, E_MULTISTART);
		_START = _NB;
		flag = E_START;
	}
	else if (ft_strequ(line, "##end"))
	{
		k = UINT16_MAX;
		while (++k < _NB)
			if (_ROOM[k]->flag == E_END)
				errhdl(lemin, _ROOM[k], line, E_MULTIEND);
		_END = _NB;
		flag = E_END;
	}
	copy_line(lemin, line);
	GIMME(flag);
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
	if ((_ANTS = ft_atoi(line)) < 1)
		errhdl(lemin, NULL, line, E_FIRSTLINE);
	copy_line(lemin, line);
	while (get_next_line(STDIN_FILENO, &line))
	{
		if (!links && line[0] == '#' && (flag = get_flag(lemin, line)))
			MOAR;
		if (line[0] == 'L' && !finish_read(lemin, line))
			NOMOAR;
		else if ((!links && (links = add_room(lemin, line, flag))) || links)
			if (do_matrix(lemin, line) == -1 && !finish_read(lemin, line))
				NOMOAR;
		flag = E_VOID;
		copy_line(lemin, line);
	}
	if (line)
		ft_strdel(&line);
}
