/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 16:09:14 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/22 09:58:09 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#define BUFF_SIZE 4096

static int				get_flag(t_lemin *lemin, char *line, t_flag *flag)
{
	if (ft_strequ(line, "##start"))
	{
		if (_START != UINT32_MAX)
			errhdl(lemin, NULL, line, E_MULTISTART);
		*flag = E_START;
	}
	else if (ft_strequ(line, "##end"))
	{
		if (_END != UINT32_MAX)
			errhdl(lemin, NULL, line, E_MULTIEND);
		*flag = E_END;
	}
	copy_line(lemin, line);
	KTHXBYE;
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
	if (!_NB)
		errhdl(lemin, NULL, NULL, E_NOROOMS);
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

	while (get_next_line(STDIN_FILENO, &line))
	{
		if (!_ANTS && line[0] != '#')
		{
			while (line[++lemin->debug_len])
				if (!ft_isdigit(line[lemin->debug_len]))
					errhdl(lemin, NULL, line, E_FIRSTLINE);
			if (ft_strlen(line) > 10 || (_ANTS = ft_atoi(line)) < 1)
				errhdl(lemin, NULL, line, E_FIRSTLINE);
		}
		else if (!links && line[0] == '#' && !get_flag(lemin, line, &flag))
			MOAR;
		else if (line[0] == 'L')
			errhdl(lemin, NULL, line, E_BADNAME);
		else if ((!links && (links = add_room(lemin, line, &flag))) || links)
			if (do_matrix(lemin, line) == -1)
				finish_read(lemin, line);
		copy_line(lemin, line);
	}
	if (!lemin->links)
		errhdl(lemin, NULL, line, E_NOLINKS);
	line ? ft_strdel(&line) : 0;
}
