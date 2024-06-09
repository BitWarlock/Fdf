/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:07:13 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/07 17:07:17 by mrezki           ###   ########.fr       */
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

static int	_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

static void	horizontal_line(t_mlx *mlx, t_point a, t_point b, t_bres line)
{
	int	p;

	p = 2 * line.dy - line.dx;
	while (a.x <= b.x)
	{
		draw_pixel(mlx, a.x, a.y, mlx->color);
		a.x += line.x_step;
		if (p < 0)
			p += 2 * line.dy;
		else
		{
			a.y += line.y_step;
			p += 2 * (line.dy - line.dx);
		}
	}
}

static void	vertical_line(t_mlx *mlx, t_point a, t_point b, t_bres line)
{
	int	p;

	p = 2 * line.dx - line.dy;
	while (a.y <= b.y)
	{
		draw_pixel(mlx, a.x, a.y, mlx->color);
		a.y += line.y_step;
		if (p < 0)
			p += 2 * line.dx;
		else
		{
			a.x += line.x_step;
			p += 2 * (line.dx - line.dy);
		}
	}
}
void	draw_line_bres(t_point a, t_point b, t_mlx *mlx)
{
	int x0 = a.x;
	int x1 = b.x;
	int y0 = a.y;
	int y1 = b.y;
	int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
	int err = dx + dy, e2; /* error value e_xy */

	for (;;){  /* loop */
		draw_pixel (mlx, x0,y0, mlx->color);
		if (x0 == x1 && y0 == y1) break;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
	}
}
// void	draw_line_bres(t_point a, t_point b, t_mlx *mlx)
// {
// 	t_bres	line;
//
// 	printf("Line from (%f, %f) to (%f, %f)\n", a.x, a.y, b.x, b.y);
// 	line.dx = _abs(b.x - a.x);
// 	line.dy = _abs(b.y - a.y);
// 	if (a.x < b.x)
// 		line.x_step = 1;
// 	else
// 		line.x_step = -1;
// 	if (a.y < b.y)
// 		line.y_step = 1;
// 	else
// 		line.y_step = -1;
// 	if (line.dx >= line.dy)
// 		horizontal_line(mlx, a, b, line);
// 	else
// 		vertical_line(mlx, a, b, line);
// }

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
