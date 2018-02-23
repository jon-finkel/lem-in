/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 20:51:17 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/23 18:24:54 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_vector		g_rooms_null = {NULL, 0, 0, sizeof(struct s_room *)};
t_vector		*g_rooms = &g_rooms_null;

static void			check_coord(const t_lemin *lemin, const char *line)
{
	size_t			len;

	len = _LEN;
	while (line[++len])
		if (!ft_isdigit(line[len]) && line[len] != ' ')
			errhdl(lemin, NULL, line, E_ROOMINVALID);
}

static void			check_dup(const t_lemin *lemin, const struct s_room *room,
					const char *line)
{
	uint16_t		k;

	k = -1;
	while (++k < _NB)
	{
		if (ft_strequ(_ROOM[k]->name, room->name))
			errhdl(lemin, _ROOM[k], line, E_SAMENAME);
		else if (_ROOM[k]->x == room->x && _ROOM[k]->y == room->y)
			errhdl(lemin, _ROOM[k], line, E_SAMEXY);
	}
}

static bool			check_link(const t_lemin *lemin, const char *line)
{
	int			minus;
	int			space;
	size_t		len;

	len = -1;
	minus = 0;
	space = 0;
	while (line[++len])
	{
		if (line[len] == ' ')
			++space;
		else if (line[len] == '-')
			++minus;
	}
	if (!space && minus == 1)
		GIMME(true);
	if (space && minus)
		errhdl(lemin, NULL, line, E_ROOMINVALID);
	GIMME(false);
}

static bool			add_vec(t_lemin *lemin, struct s_room *room, t_flag *flag)
{
	*(struct s_room **)ft_vecpush(g_rooms) = room;
	_ROOM = g_rooms->buff;
	if (*flag == E_START)
		_START = _NB;
	else if (*flag == E_END)
		_END = _NB;
	*flag = E_VOID;
	room->nb = _NB++;
	GIMME(false);
}

bool				add_room(t_lemin *lemin, const char *line, t_flag *flag,
					int k)
{
	struct s_room		*room;

	if (check_link(lemin, line) == true || !(_NB + 1))
		GIMME(true);
	room = (struct s_room *)ft_wralloc(sizeof(struct s_room));
	_LEN = 0;
	while (line[_LEN] && line[_LEN] != ' ')
		++_LEN;
	room->name = ft_strndup(line, _LEN);
	while (room->name[++k])
		if (!ft_isprint(room->name[k]))
			errhdl(lemin, NULL, line, E_ROOMINVALID);
	check_coord(lemin, line);
	if (!line[++_LEN] || !ft_isdigit(line[_LEN]))
		errhdl(lemin, NULL, line, E_ROOMNOXY);
	room->x = ft_atoi(&line[_LEN]);
	_LEN += ft_intlen(room->x) + 1;
	if (!line[_LEN] || !ft_isdigit(line[_LEN]))
		errhdl(lemin, NULL, line, E_ROOMNOY);
	room->y = ft_atoi(&line[_LEN]);
	if (line[_LEN + ft_intlen(room->y)])
		errhdl(lemin, NULL, line, E_ROOMINVALID);
	room->flag = *flag;
	check_dup(lemin, room, line);
	GIMME(add_vec(lemin, room, flag));
}
