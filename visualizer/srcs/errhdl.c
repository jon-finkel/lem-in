/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errhdl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 18:59:56 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/23 08:31:16 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visu_hex.h"

_Noreturn void			ft_errhdl(void **aptr, size_t size, int errcode)
{
	(void)aptr;
	(void)size;
	(void)errcode;
	ft_fatal("Cannot allocate memory");
}

_Noreturn void			errsdl(void)
{
	ft_dprintf(STDERR_FILENO, "fatal: %s\n", SDL_GetError());
	exit(EXIT_FAILURE);
}
