/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:09:56 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/22 15:34:40 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	parallel_projection(t_point *point)
{
	float	oldx;
	float	oldy;

	oldy = point->y;
	oldx = point->x;
	point->x = (oldx * sqrt(2) + oldy * sqrt(2)) / 2;
	point->y = (-oldx * sqrt(2) + oldy * sqrt(2)) / 2;
	point->z = oldy - (point->x + point->y) / sqrt(2);
}

void	iso_projection(t_point *point)
{
	float	newx;
	float	newy;

	newx = (point->x - point->y) * sqrt(2) / 2;
	newy = (point->x + point->y) * sqrt(2) / 2 - point->z;
	point->x = newx;
	point->y = newy;
}

void	parallel(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < mlx->rows * mlx->cols)
	{
		mlx->coords[i].x -= mlx->mid_x;
		mlx->coords[i].y -= mlx->mid_y;
		parallel_projection(&mlx->coords[i]);
		mlx->coords[i].x += mlx->mid_x;
		mlx->coords[i].y += mlx->mid_y;
		i++;
	}
	draw_grid(mlx);
}

void	iso(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < mlx->rows * mlx->cols)
	{
		mlx->coords[i].x -= mlx->mid_x;
		mlx->coords[i].y -= mlx->mid_y;
		iso_projection(&mlx->coords[i]);
		mlx->coords[i].x += mlx->mid_x;
		mlx->coords[i].y += mlx->mid_y;
		i++;
	}
	draw_grid(mlx);
}
