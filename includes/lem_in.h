/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 20:56:49 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/07 17:18:19 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"

# define BUFF_SIZE 4

typedef enum		s_error
{
	E_NOANTS = 0,
	E_FIRSTLINE = 1,
	E_ROOMNOXY = 2,
	E_ROOMNOY = 3
}					t_error;

typedef enum		s_flag
{
	E_VOID = 1,
	E_START = 21,
	E_END = 42
}					t_flag;

typedef struct		s_lemin
{
	bool			debug;
	char			**matrice;
	int				ants;
	size_t			debug_len;
	struct s_room	**rooms;
	uint16_t		room_nb;
}					t_lemin;

struct				s_room
{
	char			*name;
	int				x;
	int				y;
	t_flag			flag;
	uint16_t		nb;
};

extern void			errhdl(const t_lemin *lemin, const char *line, t_error err);
extern int			parse(t_lemin *lemin, bool links);
extern bool			usage(int argc, const char *argv[]);

#endif