/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 20:56:49 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/20 09:50:57 by nfinkel          ###   ########.fr       */
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
# define _LINKS lemin->links
# define _LIST ((struct s_path *)(list->data))
# define _MATRIX lemin->matrix
# define _NB lemin->room_nb
# define _PATH lemin->paths
# define _ROOM lemin->rooms
# define _START lemin->start

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
	E_BADCOORD = E_NOSOLUTION + 1,
	E_BADNAME = E_BADCOORD + 1,
	E_ROOMNOY = E_BADNAME + 1,
	E_ROOMNOXY = E_ROOMNOY + 1,
	E_ROOMZ = E_ROOMNOXY + 1,
	E_FIRSTLINE = E_ROOMZ + 1,
	E_NOANTS = E_FIRSTLINE + 1
}					t_error;

# define ERRNUM E_NOANTS + 1

typedef enum		s_flag
{
	E_VOID = 1,
	E_START = 21,
	E_END = 42,
	E_FILE,
	E_MATRIX
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
	struct s_path	**paths;
	struct s_room	**rooms;
	uint16_t		room_nb;
	uint32_t		end;
	uint32_t		start;
	uintmax_t		links;
}					t_lemin;

struct				s_room
{
	char			*name;
	int				x;
	int				y;
	t_flag			flag;
	uint16_t		nb;
};

struct				s_path
{
	uint16_t		rooms[UINT16_MAX];
	uint16_t		len;
};

extern bool			add_room(t_lemin *lemin, const char *line, t_flag *flag);
extern void			edkarp(t_lemin *lemin);
extern void			copy_line(t_lemin *lemin, char *line);
extern void			debug_output(const t_lemin *lemin);
extern void			errhdl(const t_lemin *lemin, const struct s_room *room,
					const char *line, t_error err);
extern int			finish_read(t_lemin *lemin, char *line);
extern void			move(const t_lemin *lemin);
extern void			parse(t_lemin *lemin, bool links, t_flag flag);

extern void			dqtor(void *data, size_t data_size, va_list ap);
extern void			vdtor(void *data, va_list ap);

#endif
