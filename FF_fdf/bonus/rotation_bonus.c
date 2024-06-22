/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:12:36 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/22 15:34:43 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	centroid(t_point *points, int size, t_mlx *mlx)
{
	float	center_x;
	float	center_y;
	float	center_z;
	int		i;

	center_x = 0;
	center_y = 0;
	center_z = 0;
	i = 0;
	while (i < size)
	{
		center_x += points[i].x;
		center_y += points[i].y;
		center_z += points[i].z;
		i++;
	}
	mlx->centroid.x = center_x / size;
	mlx->centroid.y = center_y / size;
	mlx->centroid.z = center_z / size;
}

void	scale_up(t_point *points, float scale, float z)
{
	points->x *= scale;
	points->y *= scale;
	points->z *= scale / z;
}

void	rotate(int size, t_mlx *mlx)
{
	float	z;
	int		i;

	i = 0;
	centroid(mlx->coords, size, mlx);
	z = max(_abs(max_z(mlx->coords, size)), _abs(min_z(mlx->coords, size)));
	if (z > 100)
		z = 10;
	while (i < size)
	{
		translate(&mlx->coords[i], -mlx->centroid.x,
			-mlx->centroid.y, -mlx->centroid.z);
		scale_up(&mlx->coords[i], get_scale(mlx), z);
		iso_projection(&mlx->coords[i]);
		mlx->coords[i].x += mlx->mid_x;
		mlx->coords[i].y += mlx->mid_y;
		i++;
	}
}

void	rotate_shape(t_mlx *mlx, float x, float y, float z)
{
	int	i;

	i = 0;
	centroid(mlx->coords, mlx->cols * mlx->rows, mlx);
	while (i < mlx->rows * mlx->cols)
	{
		translate(&mlx->coords[i], -mlx->centroid.x,
			-mlx->centroid.y, -mlx->centroid.z);
		rotate_xyz(&mlx->coords[i], x, y, z);
		mlx->coords[i].x += mlx->mid_x;
		mlx->coords[i].y += mlx->mid_y;
		i++;
	}
	draw_grid(mlx);
}

void	rotate_xyz(t_point *point, float x, float y, float z)
{
	float	newx;
	float	newy;
	float	newz;

	newy = cos(x) * point->y - sin(x) * point->z;
	newz = sin(x) * point->y + cos(x) * point->z;
	point->y = newy;
	point->z = newz;
	newx = cos(y) * point->x + sin(y) * point->z;
	newz = -sin(y) * point->x + cos(y) * point->z;
	point->x = newx;
	point->z = newz;
	newx = cos(z) * point->x - sin(z) * point->y;
	newy = sin(z) * point->x + cos(z) * point->y;
	point->x = newx;
	point->y = newy;
}
