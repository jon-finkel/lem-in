/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errhdl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 11:10:01 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/11 17:33:12 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static const char		*g_err[ERRNUM] =
{
	"The map has multiple ending points",
	"The map has multiple starting points",
	"The map doesn't have a starting point",
	"The map doesn't have an ending point",
	"Two rooms have the same coordinates",
	"Two rooms have the same name",
	"This map has no solution",
	"Room definition is invalid (no Y axis)",
	"Room definition is invalid (no coordinates)",
	"First line should be a valid number of ants.",
	"Number of ants is invalid."
};

_Noreturn void			errhdl(const t_lemin *lemin, const struct s_room *room,
						const char *line, t_error err)
{
	if (err == E_FIRSTLINE && (line[0] == '0' || _ANTS < 0))
		err = E_NOANTS;
	if (_DEBUG)
	{
		ft_dprintf(STDERR_FILENO, "ERROR: %s\n", g_err[err]);
		if (err != E_NOSOLUTION && err != E_NOSTART && err != E_NOEND
			&& err != E_MULTISTART && err != E_MULTIEND)
			ft_dprintf(STDERR_FILENO, "%s\n", line);
		if (err != E_NOSOLUTION && err != E_SAMEXY && err != E_SAMENAME
			&& err != E_NOSTART && err != E_NOEND && err != E_MULTISTART
			&& err != E_MULTIEND)
			ft_dprintf(STDERR_FILENO, "{1d}%*c{eoc}\n", lemin->debug_len, '^');
		if (err == E_SAMEXY || err == E_SAMENAME)
			ft_dprintf(STDERR_FILENO, "%s %d %d\n", room->name, room->x,\
				room->y);
	}
	else
		ft_dprintf(STDERR_FILENO, "ERROR\n");
	exit(EXIT_FAILURE);
}
