/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:34:33 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/22 15:34:34 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	released(int key, int x, int y, t_mlx *mlx)
{
	(void)key;
	(void)x;
	(void)y;
	mlx->centroid.rotate &= ~(1 << 2);
	return (0);
}

int	pressed(int key, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (key == UP_MOUSE)
		scale(mlx, 1.1);
	if (key == DOWN_MOUSE)
		scale(mlx, 0.9);
	if (key == LEFT_MOUSE)
		mlx->centroid.rotate |= 4;
	return (0);
}

int	move(int x, int y, t_mlx *mlx)
{
	int	i;

	i = -1;
	mlx->mouse.prev_x = mlx->mouse.x;
	mlx->mouse.prev_y = mlx->mouse.y;
	mlx->mouse.x = x;
	mlx->mouse.y = y;
	if ((mlx->centroid.rotate >> 2) & 1)
	{
		centroid(mlx->coords, mlx->cols * mlx->rows, mlx);
		while (++i < mlx->rows * mlx->cols)
		{
			translate(&mlx->coords[i], -mlx->centroid.x,
				-mlx->centroid.y, -mlx->centroid.z);
			rotate_xyz(&mlx->coords[i],
				(y - mlx->mouse.prev_y) * 0.002,
				(x - mlx->mouse.prev_x) * 0.002, 0);
			mlx->coords[i].x += mlx->mid_x;
			mlx->coords[i].y += mlx->mid_y;
		}
		draw_grid(mlx);
	}
	return (0);
}

void	mlx_mouse_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, 17, 0, quit, mlx);
	mlx_hook(mlx->win, 4, 0, pressed, mlx);
	mlx_hook(mlx->win, 5, 0, released, mlx);
	mlx_hook(mlx->win, 6, 0, move, mlx);
}
