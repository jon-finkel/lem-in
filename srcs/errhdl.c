/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errhdl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 11:10:01 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/15 16:07:29 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <string.h>
#include <errno.h>
#define _LINE lemin->debug_line

static const char		*g_err[ERRNUM] =
{
	"The map doesn't have any links",
	"The map has multiple starting points",
	"The map has multiple ending points",
	"The map doesn't have a starting point",
	"The map doesn't have an ending point",
	"Two rooms have the same coordinates",
	"Two rooms have the same name",
	"This map has no solution",
	"Room definition is invalid (no Y axis)",
	"Room definition is invalid (no coordinates)",
	"Room definition is invalid (too many coordinates)",
	"First line should be a valid number of ants.",
	"Number of ants is invalid."
};

_Noreturn void			ft_errhdl(int errcode)
{
	if (errcode == ENOMEM)
		ft_putendl_fd("Cannot allocate memory", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

_Noreturn void			errhdl(const t_lemin *lemin, const struct s_room *room,
						const char *line, t_error err)
{
	if (err == E_FIRSTLINE && (line[0] == '0' || _ANTS < 0))
		err = E_NOANTS;
	if (_DEBUG)
	{
		ft_dprintf(STDERR_FILENO, "ERROR: %s\n", g_err[err]);
		if (err >= E_SAMEXY && err != E_NOSOLUTION)
			ft_dprintf(STDERR_FILENO, "LINE[%lu]: %s\n", _LINE, line);
		if (err == E_SAMEXY || err == E_SAMENAME)
			ft_dprintf(STDERR_FILENO, "%s %d %d\n", room->name, room->x,\
				room->y);
	}
	else
		ft_dprintf(STDERR_FILENO, "ERROR\n");
	exit(EXIT_FAILURE);
}
