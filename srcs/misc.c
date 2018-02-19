/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 10:50:56 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/19 20:53:05 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static t_vector		g_vec_null = {NULL, 0, 0, sizeof(struct s_path *)};
static t_vector		*g_vec = &g_vec_null;

void			dqtor(void *data, size_t data_size)
{
	ft_memset(data, '\0', data_size);
	free(data);
}

void			copy_line(t_lemin *lemin, char *line)
{
	*(char **)ft_vecpush(g_vec) = ft_strdup(line);
	lemin->file = g_vec->buff;
	++lemin->debug_line;
	ft_strdel(&line);
}

int				finish_read(t_lemin *lemin, char *line)
{
	copy_line(lemin, line);
	while (get_next_line(STDIN_FILENO, &line))
		copy_line(lemin, line);
	KTHXBYE;
}
