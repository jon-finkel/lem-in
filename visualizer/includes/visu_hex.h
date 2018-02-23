/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_hex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 14:37:15 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/23 08:38:21 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_HEX_H
# define VISU_HEX_H

# include <SDL2/SDL.h>
# include "../../libft/includes/libft.h"

# define _WIN hex->window

enum				e_sdlflags
{
	E_ACCEL = SDL_RENDERER_ACCELERATED,
	E_CENTER = SDL_WINDOWPOS_CENTERED,
	E_TEXTURE = SDL_RENDERER_TARGETTEXTURE,
	E_VIDEO = SDL_INIT_VIDEO
};

typedef struct		s_hex
{
	SDL_Window		*window;
}					t_hex;

_Noreturn void		ft_errhdl(void **aptr, size_t size, int errcode);
_Noreturn void		errsdl(void);

#endif
