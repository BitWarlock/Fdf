/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 05:52:08 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/14 03:38:10 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*add;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		add = mlx->addr + (y * mlx->len + x * (mlx->bpp / 8));
		*(unsigned int *)add = color;
	}
}

void	draw_grid(t_mlx *mlx)
{
	t_point	*points;
	int		x;
	int		y;

	clear_mlx(mlx);
	points = mlx->coords;
	x = -1;
	while (++x < mlx->cols * mlx->rows)
		if (x % mlx->rows != 0)
			draw_line_bres(points[x - 1], points[x], mlx);
	x = mlx->rows;
	y = -1;
	while (++y + x < mlx->cols * mlx->rows)
		draw_line_bres(points[y], points[y + x], mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
