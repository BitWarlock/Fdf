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

// void	rotate_for_conic_projection(t_point *point, float angle)
// {
// 	float distance = sqrt(point->x * point->x + point->y * point->y);
// 	float newx, newy;
//
// 	if (distance != 0)
// 	{
// 		float scale = (distance - point->z * tan(angle)) / distance;
// 		newx = point->x * scale;
// 		newy = point->y * scale;
// 	}
// 	else
// {
// 		newx = 0;
// 		newy = 0;
// 	}
//
// 	point->x = newx;
// 	point->y = newy;
// }
//
int	key(int key, t_mlx *mlx)
{
	if (key == ESC)
		exit(EXIT_SUCCESS);
	if (key == N_PLUS || key == M_PLUS)
		scale(mlx, 1.1);
	if (key == N_MINUS || key == M_MINUS)
		scale(mlx, 0.9);
	if (key == UP)
		translate_shape(mlx, 0, -20, 0);
	if (key == DOWN)
		translate_shape(mlx, 0, 20, 0);
	if (key == LEFT)
		translate_shape(mlx, 20, 0, 0);
	if (key == RIGHT)
		translate_shape(mlx, -20, 0, 0);
	if (key == X_KEY)
		rotate_shape(mlx, 0.2, 0, 0);
	if (key == Y_KEY)
		rotate_shape(mlx, 0, 0.2, 0);
	if (key == Z_KEY)
		rotate_shape(mlx, 0, 0, 0.2);
	if (key == P_KEY)
		parallel(mlx);
	return (0);
}

int	quit(int key, t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(EXIT_SUCCESS);
}

void	mlx_hooks(t_mlx *mlx)
{
	mlx_key_hook(mlx->win, key, mlx);
	mlx_hook(mlx->win, 17, 0, quit, mlx);
}
