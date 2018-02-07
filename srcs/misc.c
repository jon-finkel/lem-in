/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 10:50:56 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/07 14:53:50 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static const char		*g_usage[2] =
{
	"usage: lem-in [-d || -r] < map_file\n\n"\
	"-d  --debug        enable debug mode\n"\
	"-r  --rules        display parsing rules\n",
	"A valid map file is defined as follows:\n"\
	" - first line should contain a valid number of ants\n"\
	" - the number of ants should fit in a signed integer\n"\
	" - the next lines should respect the format [n x y] where:\n"\
	"   * n is the name of the room\n"\
	"   * room name can contain any printable character except '-' and ' ' "\
	"and must not begin with '#' or 'L'\n"\
	"   * x is a signed integer that represents the X axis of the room\n"\
	"   * y is a signed integer that represents the Y axis of the room\n"\
	" - the number of rooms should fit in an unsigned 16bits integer\n"\
	" - preceding any room definition, a comment beginning by any number of "\
	"hashtags can modify the properties of the following room:\n"\
	"   * ##start will define the room as the ants starting point\n"\
	"   * ##end will define the room that the ants need to reach\n"\
	"   * any other comment serves no purpose and will be ignored\n"\
	" - any map without a start and an ending is considered invalid\n"\
	" - the next lines should represents the links between the rooms "\
	"and respect the format [n1-n2] where:\n"\
	"   * n1 is the name of the first room and n2 the name of the second\n"\
	" - any line not respecting these rules will invalid the next ones\n"\
	" - program will still try to proceed with the valid lines acquired\n"
};

inline bool			usage(int argc, const char *argv[])
{
	bool		debug;

	debug = false;
	if (argc == 2)
	{
		if (ft_strequ(argv[1], "-d") || (ft_strequ(argv[1], "--debug")))
			debug = true;
		else if (ft_strequ(argv[1], "-r") || (ft_strequ(argv[1], "--rules")))
		{
			ft_printf("%s", g_usage[1]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			ft_printf("%s", g_usage[0]);
			exit(EXIT_SUCCESS);
		}
	}
	else if (argc > 2)
	{
		ft_printf("%s", g_usage[0]);
		exit(EXIT_SUCCESS);
	}
	GIMME(debug);
}
