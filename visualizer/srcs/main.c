/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 21:32:28 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/24 22:02:46 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hex.h"

#define _MAP_FILE "./ressources/assets/background.xpm"
#define _WIN_TITLE "An anthill visualizer, by Jon Finkel"

static t_hex			*init_hex(t_hex *hex)
{
	int			height;
	int			width;
	void		*xpm;

	hex = (t_hex *)ft_memalloc(sizeof(t_hex));
	if (!(_MLX = mlx_init()))
		ft_fatal("could not initiate mlx.");
	if (!(_WIN = mlx_new_window(_MLX, 1920, 1080, _WIN_TITLE)))
		ft_fatal("could not initiate window.");
	if (!(xpm = mlx_xpm_file_to_image(_MLX, _MAP_FILE, &width, &height)))
		ft_fatal("could not locate xpm file, restart from lem-in directory.");
	mlx_put_image_to_window(_MLX, _WIN, xpm, 0, 0);
	GIMME(hex);
}

int						main(void)
{
	t_hex		*hex;

	hex = init_hex(NULL);
	mlx_key_hook(_WIN, key_hook, hex);
	mlx_loop(_MLX);
	KTHXBYE;
}
