/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 10:50:56 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/19 15:38:45 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void			dqtor(void *data, size_t data_size)
{
	ft_memset(data, '\0', data_size);
	free(data);
}

void			copy_line(t_lemin *lemin, char *line)
{
	lemin->file = ft_strcjoin(lemin->file, line, '\n', true);
	++lemin->debug_line;
	ft_strdel(&line);
}

void			verif_entry(const t_lemin *lemin, const struct s_room *room,
				const char *line, t_flag flag)
{
	size_t			len;
	uint16_t		k;

	if (flag == E_LETTERS)
	{
		len = lemin->debug_len;
		while (line[++len])
			if (!ft_isdigit(line[len]) && line[len] != ' ')
				errhdl(lemin, NULL, line, E_BADCOORD);
	}
	else if (flag == E_DUP && (k = -1))
		while (++k < _NB)
		{
			if (ft_strequ(_ROOM[k]->name, room->name))
				errhdl(lemin, _ROOM[k], line, E_SAMENAME);
			else if (_ROOM[k]->x == room->x && _ROOM[k]->y == room->y)
				errhdl(lemin, _ROOM[k], line, E_SAMEXY);
		}
}

bool			verif_link(const t_lemin *lemin, const char *line)
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
		errhdl(lemin, NULL, line, E_BADCOORD);
	GIMME(false);
}

int				finish_read(t_lemin *lemin, char *line)
{
	copy_line(lemin, line);
	while (get_next_line(STDIN_FILENO, &line))
		copy_line(lemin, line);
	KTHXBYE;
}
