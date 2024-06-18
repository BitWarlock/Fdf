/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 01:47:16 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/15 01:47:17 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

void	conic_projection(t_point *point, float angle)
{
	float	distance;
	float	newx;
	float	newy;
	float	scale;

	distance = sqrt(point->x * point->x + point->y * point->y);
	if (distance != 0)
	{
		scale = (distance - point->z * tan(angle)) / distance;
		newx = point->x * scale;
		newy = point->y * scale;
	}
	else
	{
		newx = 0;
		newy = 0;
	}
	point->x = newx;
	point->y = newy;
}

void	conic(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < mlx->rows * mlx->cols)
	{
		mlx->coords[i].x -= mlx->mid_x;
		mlx->coords[i].y -= mlx->mid_y;
		conic_projection(&mlx->coords[i], 1);
		mlx->coords[i].x += mlx->mid_x;
		mlx->coords[i].y += mlx->mid_y;
		i++;
	}
	draw_grid(mlx);
}
