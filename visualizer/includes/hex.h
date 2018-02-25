/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 21:30:43 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/24 21:50:56 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEX_H
# define HEX_H

# include "../../libft/includes/libft.h"
# include "../ressources/mlx/mlx.h"

# define _MLX hex->mlx
# define _WIN hex->win

typedef struct		s_hex
{
	void			*mlx;
	void			*win;
}					t_hex;

extern int			key_hook(int keycode, void *param);

extern void			ft_errhdl(void **aptr, size_t size, int errcode);

#endif
