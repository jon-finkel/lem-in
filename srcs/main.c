/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 20:56:08 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/25 09:27:03 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static const char		*g_usage[2] =
{
	"usage: lem-in [-dn || -r] < map_file\n\n"\
	"-d  --debug        enable debug mode\n"\
	"-n  --no-matrix    disable adjacency matrix display for debug mode\n"\
	"-r  --rules        display parsing rules\n",
	"A valid map file is defined as follows:\n"\
	" - the first valid line should contain a valid number of ants\n"\
	" - comments can be inserted before the first line but will be ignored\n"\
	" - the number of ants should fit in a signed integer\n"\
	" - the next lines should respect the format [n x y] where:\n"\
	"   * n is the name of the room\n"\
	"   * a room name can contain any printable character except '-' and ' ' "\
	"and must not begin with '#' or 'L'\n"\
	"   * two rooms cannot have the same name\n"\
	"   * x must be a positive integer that represents the room's X axis\n"\
	"   * y must be a positive integer that represents the room's Y axis\n"\
	"   * two rooms cannot have the same coordinates\n"\
	" - preceding any room definition, a comment beginning by any number of "\
	"hashtags can modify the properties of the following room:\n"\
	"   * ##start will define the room as the ants starting point\n"\
	"   * ##end will define the room that the ants need to reach\n"\
	"   * any other comment serves no purpose and will be ignored\n"\
	" - any map without a start and an ending is considered invalid\n"\
	" - any map with more than one start and/or one ending is considered "\
	"invalid\n"\
	" - the next lines should represents the links between the rooms "\
	"and respect the format [n1-n2] where:\n"\
	"   * n1 is the name of the first room and n2 the name of the second\n"\
	" - any line not respecting these rules will invalid the next ones\n"\
	" - program will still try to proceed with the valid lines acquired\n"
};

static void			usage(t_lemin *lemin, int argc, const char *argv[])
{
	if (argc == 2 || argc == 3)
	{
		if (ft_strequ(argv[1], "-d") || (ft_strequ(argv[1], "--debug"))
			|| (ft_strequ(argv[1], "-dn") && (_DEBUG_MATRIX = true)))
		{
			_DEBUG = true;
			if (argc == 3 && (ft_strequ(argv[2], "-n")
				|| ft_strequ(argv[2], "--no-matrix")))
				_DEBUG_MATRIX = true;
			else if (argc == 3 && ft_printf("%s", g_usage[0]))
				exit(EXIT_SUCCESS);
		}
		else if ((ft_strequ(argv[1], "-r") || (ft_strequ(argv[1], "--rules")))
			&& ft_printf("%s", g_usage[1]))
			exit(EXIT_SUCCESS);
		else if (!ft_strequ(argv[1], "-n") && !ft_strequ(argv[1], "--no-matrix")
			&& ft_printf("%s", g_usage[0]))
			exit(EXIT_SUCCESS);
	}
	else if (argc > 3 && ft_printf("%s", g_usage[0]))
		exit(EXIT_SUCCESS);
	_DEBUG_MATRIX = (_DEBUG_MATRIX ? false : true);
}

static void			sort_vary(t_lemin *lemin)
{
	uintmax_t		k;
	uintmax_t		p;

	k = -1;
	while (_PATH[++k + 1] && (p = -1))
		while (_PATH[++p + k + 1])
			if (_PATH[p]->len > _PATH[p + 1]->len)
				ft_swap(&_PATH[p], &_PATH[p + 1], sizeof(t_path **));
}

static void			print_debug(t_lemin *lemin)
{
	extern t_vary		*g_file;
	uint16_t			k;

	k = -1;
	while (_FILE[++k])
		ft_printf("%r\n", _FILE[k]);
	sort_vary(lemin);
	if (_DEBUG)
		debug_output(lemin);
	k = -1;
	while (++k < _NB)
		free(_MATRIX[k]);
	ft_memdel((void **)&_MATRIX);
	ft_varydel(&g_file, vdtor, E_FILE);
	g_file = NULL;
	_FILE = NULL;
}

static void			cleanup(t_lemin *lemin)
{
	extern t_vary		*g_paths;
	extern t_vary		*g_rooms;

	ft_memdel((void **)&_CHECK);
	ft_varydel(&g_paths, vdtor, E_PATHS);
	ft_varydel(&g_rooms, vdtor, E_ROOMS);
	ft_memdel((void **)&lemin);
}

int					main(int argc, const char *argv[])
{
	t_lemin		*lemin;

	lemin = (t_lemin *)ft_memalloc(sizeof(t_lemin));
	usage(lemin, argc, argv);
	_END = UINT32_MAX;
	_START = UINT32_MAX;
	lemin->debug_len = -1;
	lemin->debug_line = 1;
	parse(lemin, false, E_VOID);
	if (_START == UINT32_MAX || _END == UINT32_MAX)
		errhdl(lemin, NULL, NULL, _END == UINT32_MAX ? E_NOEND : E_NOSTART);
	_CHECK = (bool *)ft_memalloc(sizeof(bool) * _NB);
	_CHECK[_START] = true;
	edmonds_karp(lemin);
	print_debug(lemin);
	move(lemin, _ANTS);
	cleanup(lemin);
	KTHXBYE;
}
