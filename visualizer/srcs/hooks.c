/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 21:48:52 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/24 21:49:28 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hex.h"
#include "../../libft/includes/mlx_keys.h"

static _Noreturn void			cleanup(t_hex *hex)
{
	mlx_destroy_window(_MLX, _WIN);
	ft_memdel((void **)&hex);
	exit(EXIT_SUCCESS);
}

int								key_hook(int keycode, void *param)
{
	if (keycode == MLX_KEY_ESCAPE)
		cleanup((t_hex *)param);
	KTHXBYE;
}
