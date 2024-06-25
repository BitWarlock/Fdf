/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:09:56 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/22 15:32:38 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	iso_projection(t_point *point)
{
	float	newx;
	float	newy;

	newx = (point->x - point->y) * sqrt(2) / 2;
	newy = (point->x + point->y) * sqrt(2) / 2 - point->z;
	point->x = newx;
	point->y = newy;
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
