/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 03:38:37 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/14 03:38:38 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale(t_mlx *mlx)
{
	int	i;

	i = -1;
	centroid(mlx->coords, mlx->cols * mlx->rows, mlx);
	while (++i < mlx->cols * mlx->rows)
	{
		translate(&mlx->coords[i], -mlx->centroid.x,
			-mlx->centroid.y, -mlx->centroid.z);
		mlx->coords[i].x *= 1.1;
		mlx->coords[i].y *= 1.1;
		mlx->coords[i].z *= 1.1;
		mlx->coords[i].x += mlx->mid_x;
		mlx->coords[i].y += mlx->mid_y;
	}
	draw_grid(mlx);
}

void	scale_down(t_mlx *mlx)
{
	int	i;

	i = -1;
	centroid(mlx->coords, mlx->cols * mlx->rows, mlx);
	while (++i < mlx->cols * mlx->rows)
	{
		translate(&mlx->coords[i], -mlx->centroid.x,
			-mlx->centroid.y, -mlx->centroid.z);
		mlx->coords[i].x /= 1.1;
		mlx->coords[i].y /= 1.1;
		mlx->coords[i].z /= 1.1;
		mlx->coords[i].x += mlx->mid_x;
		mlx->coords[i].y += mlx->mid_y;
	}
	draw_grid(mlx);
}

void	translate_shape(t_mlx *mlx, float tx, float ty, float tz)
{
	int	i;

	i = -1;
	while (++i < mlx->cols * mlx->rows)
		translate(&mlx->coords[i], tx, ty, tz);
	draw_grid(mlx);
}

void	translate(t_point *p, float tx, float ty, float tz)
{
	p->x += tx;
	p->y += ty;
	p->z += tz;
}
