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

#include "../incs/fdf.h"

void	draw_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*add;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		add = mlx->addr + (y * mlx->len + x * (mlx->bpp / 8));
		*(unsigned int *)add = color;
	}
}

int	print_strings(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->win, WIDTH / 2 - 15, 0, mlx->color, "FDF");
	mlx_string_put(mlx->mlx, mlx->win, 40, 100, mlx->color,
		"         CONTROLS");
	mlx_string_put(mlx->mlx, mlx->win, 40, 130, mlx->color, "+/-: Zoom ");
	mlx_string_put(mlx->mlx, mlx->win, 40, 160, mlx->color,
		"x/y/z: Rotate X/Y/Z axis");
	mlx_string_put(mlx->mlx, mlx->win, 40, 190, mlx->color,
		"Scroll: zoom in/out");
	mlx_string_put(mlx->mlx, mlx->win, 40, 220, mlx->color, "P: Parallel");
	mlx_string_put(mlx->mlx, mlx->win, 40, 250, mlx->color, "I: Isometric");
	mlx_string_put(mlx->mlx, mlx->win, 40, 280, mlx->color, "B: Blackhole");
	mlx_string_put(mlx->mlx, mlx->win, 40, 310, mlx->color, "C: Change color");
	mlx_string_put(mlx->mlx, mlx->win, 40, 340, mlx->color, "F: Flash");
	mlx_string_put(mlx->mlx, mlx->win, 40, 370, mlx->color,
		"Space/0: Rotate/Stop");
	mlx_string_put(mlx->mlx, mlx->win, 40, 400, mlx->color,
		"Arrows: Translate");
	return (0);
}

void	draw_grid(t_mlx *mlx)
{
	t_point	*points;
	int		x;
	int		y;
	int		i;

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
	print_strings(mlx);
}
