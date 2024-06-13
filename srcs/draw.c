/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 05:52:08 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/13 05:52:09 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_x(t_mlx *mlx)
{
	draw_line_bres((t_point){mlx->mid_x, 0},
		(t_point){mlx->mid_x, HEIGHT}, mlx);
	draw_line_bres((t_point){0, mlx->mid_y},
		(t_point){WIDTH, mlx->mid_y}, mlx);
}

void	draw_grid(t_mlx *mlx)
{
	t_point	*points;
	int		x;
	int		y;
	int		i;

	points = mlx->coords;
	x = -1;
	while (++x < mlx->cols * mlx->rows)
	{
		if (x % mlx->rows != 0)
			draw_line_bres(points[x - 1], points[x], mlx);
	}
	x = mlx->rows;
	y = -1;
	while (++y + x < mlx->cols * mlx->rows)
		draw_line_bres(points[y], points[y + x], mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
