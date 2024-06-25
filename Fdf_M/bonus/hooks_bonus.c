/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 05:52:21 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/22 15:34:14 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "keys_macos.h"

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

void	rotation_speed(int key, t_mlx *mlx)
{
	if (key == N_PLUS)
	{
		mlx->x_angle += 0.002;
		mlx->y_angle += 0.002;
		mlx->z_angle += 0.002;
	}
	if (key == N_MINUS)
	{
		mlx->x_angle -= 0.002;
		mlx->y_angle -= 0.002;
		mlx->z_angle -= 0.002;
	}
}

int	key(int key, t_mlx *mlx)
{
	if (key == H_KEY)
	{
		if (mlx->text)
			mlx->text = 0;
		else
			mlx->text = 1;
	}
	if (key == W_KEY)
		mlx->reflect = 1;
	if (key == ESC)
		exit(EXIT_SUCCESS);
	if (key == N_PLUS || key == N_MINUS)
		rotation_speed(key, mlx);
	if (key == M_PLUS)
		scale(mlx, 1.1);
	if (key == M_MINUS)
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
	{
		mlx->reflect = 0;
		mlx->centroid.rotate &= ~1;
	}
	if (key == F_KEY)
		mlx->centroid.rotate |= 2;
	return (0);
}

int	quit(t_mlx *mlx)
{
	(void)mlx;
	exit(EXIT_SUCCESS);
}

void	mlx_hooks(t_mlx *mlx)
{
	mlx_key_hook(mlx->win, key, mlx);
	mlx_mouse_hooks(mlx);
}
