/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 14:36:20 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/23 08:54:24 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SDL_MAIN_HANDLED
#include "../includes/visu_hex.h"

#define _BACKGROUND "./ressources/background.bmp"
#define _TITLE "Lem-in vizualizer, by Jon Finkel"
#define _X E_CENTER
#define _Y E_CENTER

static void			init_sdl(t_hex *hex)
{
	SDL_Renderer		*render;
	SDL_Surface			*bg;
	SDL_Texture			*texture;

	SDL_SetMainReady();
	SDL_Init(SDL_INIT_VIDEO) ? errsdl() : 0;
	!(_WIN = SDL_CreateWindow(_TITLE, _X, _Y, 1280, 800, 0)) ? errsdl() : 0;
	!(bg = SDL_LoadBMP(_BACKGROUND)) ? errsdl() : 0;
	!(render = SDL_CreateRenderer(_WIN, -1, 0)) ? errsdl() : 0;
	!(texture = SDL_CreateTextureFromSurface(render, bg)) ? errsdl() : 0;
	SDL_RenderCopy(render, texture, NULL, NULL) ? errsdl() : 0;
	SDL_RenderPresent(render);
	SDL_FreeSurface(bg);
	SDL_DestroyTexture(texture);
	SDL_RenderClear(render) ? errsdl() : 0;
	SDL_Delay(10000);
	SDL_DestroyWindow(_WIN);
}

int					main(void)
{
	t_hex		*hex;

	hex = (t_hex *)ft_memalloc(sizeof(t_hex));
	init_sdl(hex);
	SDL_Quit();
	KTHXBYE;
}
