/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errhdl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 11:10:01 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/07 21:16:51 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static const char		*g_err[BUFF_SIZE] =
{
	"Number of ants is invalid.",
	"First line should be a valid number of ants.",
	"Room definition is invalid (no coordinates)",
	"Room definition is invalid (no Y axis)"
};

void			errhdl(const t_lemin *lemin, const char *line, t_error err)
{
	if (err == E_FIRSTLINE && (line[0] == '0' || _ANTS < 0))
		err = E_NOANTS;
	if (_DEBUG)
	{
		ft_printf("%s\n%s\n", g_err[err], line);
		ft_printf("{1d}%*c{eoc}\n", lemin->debug_len, '^');
	}
	else
		ft_printf("ERROR\n");
	exit(EXIT_FAILURE);
}
