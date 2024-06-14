/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 05:52:21 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/14 03:38:25 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key(int key, t_mlx *mlx)
{
	if (key == ESC)
		exit(EXIT_SUCCESS);
	if (key == N_PLUS || key == M_PLUS)
		scale(mlx);
	if (key == N_MINUS || key == M_MINUS)
		scale_down(mlx);
	if (key == UP)
		translate_shape(mlx, 0, -20, 0);
	if (key == DOWN)
		translate_shape(mlx, 0, 20, 0);
	if (key == RIGHT)
		translate_shape(mlx, 20, 0, 0);
	if (key == LEFT)
		translate_shape(mlx, -20, 0, 0);
	return (0);
}

int	quit(int key)
{
	exit(EXIT_SUCCESS);
}

void	mlx_hooks(t_mlx *mlx)
{
	mlx_key_hook(mlx->win, key, mlx);
	mlx_hook(mlx->win, 17, 0, quit, mlx);
}
