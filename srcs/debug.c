/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 22:12:52 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/07 22:58:14 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static const char		g_numbers[20] =
{
	"0 1 2 3 4 5 6 7 8 9 "
};

static inline void			display_matrix(t_lemin *lemin)
{
	int		k;
	int		p;
	size_t		len;

	k = -1;
	len = ft_intlen(_NB);
	while (++k < _NB)
	{
		ft_printf("\n%0*d |", len, k);
		p = -1;
		while (++p < _NB)
		{
			if (_MATRIX[k][p])
				ft_printf(" {1c}1{eoc}");
			else
				ft_printf(" {1a}0{eoc}");
		}
	}
	write(STDOUT_FILENO, "\n", 1);
}

void						debug_output(t_lemin *lemin)
{
	int			k;
	size_t		len;

	if (!_DEBUG)
		BYEZ;
	ft_printf("{1c}---------- Adjacency matrix ----------{eoc}\n\n     ");
	len = (size_t)_NB;
	while (len >= 10 && ft_printf("%s", g_numbers))
		len -= 10;
	ft_printf("%.*s\n    ", len * 2 % 20, g_numbers);
	k = -1;
	while (++k < _NB)
		ft_printf(" -");
	display_matrix(lemin);
}
