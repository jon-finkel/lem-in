/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 20:56:49 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/22 13:33:42 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"

# define _ANTS lemin->ants
# define _CHECK lemin->check
# define _DEBUG lemin->debug
# define _END lemin->end
# define _FILE lemin->file
# define _HIT lemin->s_flow.__hit
# define _HIT_PATH lemin->s_flow.__hit_path
# define _LINKS lemin->links
# define _MATRIX lemin->matrix
# define _MOVES lemin->moves
# define _NB lemin->room_nb
# define _PATH lemin->paths
# define _ROOM lemin->rooms
# define _START lemin->start
# define _VALID_PATHS lemin->valid_paths

typedef enum		s_error
{
	E_NOROOMS = 0,
	E_NOLINKS = E_NOROOMS + 1,
	E_MULTISTART = E_NOLINKS + 1,
	E_MULTIEND = E_MULTISTART + 1,
	E_NOSTART = E_MULTIEND + 1,
	E_NOEND = E_NOSTART + 1,
	E_SAMEXY = E_NOEND + 1,
	E_SAMENAME = E_SAMEXY + 1,
	E_NOSOLUTION = E_SAMENAME + 1,
	E_ROOMINVALID = E_NOSOLUTION + 1,
	E_BADNAME = E_ROOMINVALID + 1,
	E_ROOMNOY = E_BADNAME + 1,
	E_ROOMNOXY = E_ROOMNOY + 1,
	E_FIRSTLINE = E_ROOMNOXY + 1,
	E_NOANTS = E_FIRSTLINE + 1
}					t_error;

# define ERRNUM E_NOANTS + 1

typedef enum		s_flag
{
	E_VOID = 1,
	E_START = 21,
	E_END = 42,
	E_FILE,
	E_MATRIX,
	E_REDIRECT
}					t_flag;

typedef struct		s_lemin
{
	bool			debug;
	bool			*check;
	bool			**matrix;
	char			**file;
	int				ants;
	size_t			debug_len;
	size_t			debug_line;
	struct
	{
		bool		__hit;
		uintmax_t	__hit_path;
	}				s_flow;
	struct s_path	**paths;
	struct s_room	**rooms;
	uint16_t		room_nb;
	uint32_t		end;
	uint32_t		start;
	uintmax_t		links;
	uintmax_t		moves;
	uintmax_t		valid_paths;
}					t_lemin;

typedef struct		s_path
{
	uint16_t		rooms[UINT16_MAX];
	uint16_t		len;
}					t_path;

struct				s_room
{
	char			*name;
	int				x;
	int				y;
	t_flag			flag;
	uint16_t		nb;
};

extern bool			add_room(t_lemin *lemin, const char *line, t_flag *flag,
					int k);
extern void			edmonds_karp(t_lemin *lemin);
extern void			copy_line(t_lemin *lemin, char *line);
extern void			debug_output(const t_lemin *lemin);
extern void			errhdl(const t_lemin *lemin, const struct s_room *room,
					const char *line, t_error err);
extern int			finish_read(t_lemin *lemin, char *line);
extern void			move(const t_lemin *lemin, int ants);
extern void			parse(t_lemin *lemin, bool link, t_flag flag);

extern void			dqtor(void *data, size_t data_size, va_list ap);
extern void			vdtor(void *data, va_list ap);

#endif
