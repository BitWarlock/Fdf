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

#include "../incs/fdf.h"

void	rotation_keys(t_mlx *mlx, int key)
{
	if (key == UP)
		translate_shape(mlx, 0, -40, 0);
	if (key == DOWN)
		translate_shape(mlx, 0, 40, 0);
	if (key == LEFT)
		translate_shape(mlx, 40, 0, 0);
	if (key == RIGHT)
		translate_shape(mlx, -40, 0, 0);
	if (key == X_KEY)
		rotate_shape(mlx, 0.2, 0, 0);
	if (key == Y_KEY)
		rotate_shape(mlx, 0, 0.2, 0);
	if (key == Z_KEY)
		rotate_shape(mlx, 0, 0, 0.2);
	if (key == P_KEY)
		parallel(mlx);
	if (key == I_KEY)
		iso(mlx);
	if (key == B_KEY)
		conic(mlx);
}

int	key(int key, t_mlx *mlx)
{
	if (key == ESC)
		exit(EXIT_SUCCESS);
	if (key == N_PLUS || key == M_PLUS)
		scale(mlx, 1.1);
	if (key == N_MINUS || key == M_MINUS)
		scale(mlx, 0.9);
	if (key == UP || key == DOWN
		|| key == RIGHT || key == LEFT
		|| key == X_KEY || key == Y_KEY
		|| key == Z_KEY || key == P_KEY
		|| key == I_KEY || key == B_KEY)
		rotation_keys(mlx, key);
	if (key == C_KEY)
		change_color(mlx);
	if (key == SP_KEY)
		mlx->centroid.rotate |= 1;
	if (key == O_KEY)
		mlx->centroid.rotate &= ~1;
	if (key == F_KEY)
		mlx->centroid.rotate |= 2;
	return (0);
}

int	quit(int key, t_mlx *mlx)
{
	exit(EXIT_SUCCESS);
}

int	mouse_hook(int key, int x, int y, t_mlx *mlx)
{
	ft_printf(1, "mouse: %d\n", key);
	if (key == UP_MOUSE)
		scale(mlx, 1.1);
	if (key == DOWN_MOUSE)
		scale(mlx, 0.9);
	return (0);
}

void	mlx_hooks(t_mlx *mlx)
{
	mlx_key_hook(mlx->win, key, mlx);
	mlx_hook(mlx->win, 17, 0, quit, mlx);
	mlx_mouse_hook(mlx->win, mouse_hook, mlx);
}
