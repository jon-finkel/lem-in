/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 10:50:56 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/25 09:54:47 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_vary		g_file_null = {NULL, 0, 0, sizeof(char *)};
t_vary		*g_file = &g_file_null;

_Noreturn void			ft_errhdl(void **aptr, size_t size, int errcode)
{
	(void)aptr;
	(void)size;
	(void)errcode;
	ft_fatal("Cannot allocate memory");
}

void					dqtor(void *data, size_t data_size, va_list ap)
{
	(void)ap;
	ft_memset(data, '\0', data_size);
	free(data);
}

void					vdtor(void *data, va_list ap)
{
	t_flag		flag;

	if ((flag = va_arg(ap, t_flag)) == E_FILE)
		ft_memdel((void **)&*(char **)data);
	else if (flag == E_PATHS)
		ft_memdel((void **)&*(t_path **)data);
	else
	{
		ft_strdel(&(*(struct s_room **)data)->name);
		ft_memdel((void **)&*(struct s_room **)data);
	}
}

void					copy_line(t_lemin *lemin, char *line)
{
	*(char **)ft_varypush(g_file) = ft_strdup(line);
	_FILE = g_file->buff;
	++lemin->debug_line;
	ft_strdel(&line);
}

int						finish_read(t_lemin *lemin, char **line)
{
	copy_line(lemin, *line);
	while (get_next_line(STDIN_FILENO, line))
		copy_line(lemin, *line);
	*line = NULL;
	KTHXBYE;
}
