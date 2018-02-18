/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 20:56:08 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/18 15:10:56 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void			print_debug_and_clean(t_lemin *lemin)
{
	uint16_t		k;

	ft_printf("%s\n", lemin->file);
	ft_strdel(&lemin->file);
	if (_DEBUG)
		debug_output(lemin);
	k = -1;
	while (++k < _NB)
		free(_MATRIX[k]);
	ft_memdel((void **)&_MATRIX);
}

int					main(int argc, const char *argv[])
{
	t_lemin		*lemin;

	lemin = (t_lemin *)ft_memalloc(sizeof(t_lemin));
	_DEBUG = usage(argc, argv);
	_END = UINT32_MAX;
	_START = UINT32_MAX;
	lemin->file = ft_strnew(0);
	lemin->debug_len = -1;
	lemin->debug_line = 1;
	parse(lemin, false, E_VOID);
	if (_START == UINT32_MAX || _END == UINT32_MAX)
		errhdl(lemin, NULL, NULL, _END == UINT32_MAX ? E_NOEND : E_NOSTART);
	_CHECK = (bool *)ft_memalloc(sizeof(bool) * _NB);
	_CHECK[_START] = true;
	edkarp(lemin);
	print_debug_and_clean(lemin);
	move(lemin);
	KTHXBYE;
}
