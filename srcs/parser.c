/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 16:09:14 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/07 17:19:43 by nfinkel          ###   ########.fr       */
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

	if (ft_strchr(line, '-') || !(lemin->room_nb + 1))
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
	room->nb = lemin->room_nb++;
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

int								parse(t_lemin *lemin, bool links)
{
	char		*line;
	int			ret;
	t_flag		flag;

	EPICFAILZ(get_next_line(STDIN_FILENO, &line), -1);
	if ((lemin->ants = ft_atoi(line)) < 1)
		errhdl(lemin, line, E_FIRSTLINE);
	ft_strdel(&line);
	while ((ret = get_next_line(STDIN_FILENO, &line)))
	{
		EPICFAILZ(ret, -1);
		if (!links && line[0] == '#' && (flag = get_flag(&line)))
			MOAR;
		if (line[0] == 'L')
			NOMOAR;
		else if (!links)
			links = add_room(lemin, line, flag);
		else if (links)
			;
		flag = E_VOID;
		ft_strdel(&line);
	}
	lemin->rooms = g_vec->buff;
	KTHXBYE;
}
