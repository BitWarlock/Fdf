/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bresenham_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:07:13 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/22 15:33:50 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "keys_macos.h"

float	_abs(float a)
{
	if (a < 0)
		return (-a);
	return (a);
}

static void	init_vars_bres(t_bres *line, t_point a, t_point b)
{
	line->x0 = a.x;
	line->x1 = b.x;
	line->y0 = a.y;
	line->y1 = b.y;
	line->dx = _abs(line->x1 - line->x0);
	line->dy = -_abs(line->y1 - line->y0);
	if (a.x < b.x)
		line->x_step = 1;
	else
		line->x_step = -1;
	if (a.y < b.y)
		line->y_step = 1;
	else
		line->y_step = -1;
	if (line->dx >= line->dy)
		line->err = line->dx / 2;
	else
		line->err = -line->dy / 2;
}

void	draw_line_bres(t_point a, t_point b, t_mlx *mlx)
{
	t_bres	line;
	int		e2;
	int		err;

	init_vars_bres(&line, a, b);
	err = line.dx + line.dy;
	while (1)
	{
		if (line.x0 <= WIDTH && line.x0 >= 0
			&& line.y0 <= HEIGHT && line.y0 >= 0)
			draw_pixel(mlx, line.x0, line.y0, a.color);
		if (line.x0 == line.x1 && line.y0 == line.y1)
			break ;
		e2 = 2 * err;
		if (e2 >= line.dy)
		{
			err += line.dy;
			line.x0 += line.x_step;
		}
		if (e2 <= line.dx)
		{
			err += line.dx;
			line.y0 += line.y_step;
		}
	}
}
//
// void	init_mlx(t_mlx *mlx)
// {
// 	mlx->mlx = mlx_init();
// 	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "FDF");
// 	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
// 	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->len, &mlx->end);
// 	mlx->height = HEIGHT;
// 	mlx->width = WIDTH;
// 	mlx->color = 0xFF00FF;
// }
//
// int main(void)
// {
// 	t_mlx mlx;
//
// 	init_mlx(&mlx);
// 	draw_line_bres((t_point){50, 50, 0}, (t_point){300, 300, 0}, &mlx);
// 	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
// 	mlx_loop(mlx.mlx);
//
// 	return EXIT_SUCCESS;
// }
