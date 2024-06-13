/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:07:29 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/13 05:52:13 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_error(int error)
{
	if (error == INVALID_ARGS)
		ft_printf(2, RED"Usage: ./fdf maps/map.fdf\n");
	if (error == WRONG_EXT)
		ft_printf(2, RED"Wrong extension: should end with .fdf\n");
	if (error == EIO)
		ft_printf(2, RED"Error: %s\n", strerror(error));
	exit(EXIT_FAILURE);
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "FDF");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->len, &mlx->end);
	mlx->color = 0xFFFFFF;
	mlx->mid_x = (float)WIDTH / 2;
	mlx->mid_y = (float)HEIGHT / 2;
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

void	f(void)
{
	system("leaks -quiet fdf");
}

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	if (argc != 2)
		print_error(INVALID_ARGS);
	check_extension(argv[1]);
	init_mlx(&mlx);
	mlx_hooks(&mlx);
	parse_map(argv[1], &mlx);
	get_values(&mlx);
	rotate(mlx.cols * mlx.rows, &mlx);
	draw_grid(&mlx);
	mlx_loop(mlx.mlx);
	return (EXIT_SUCCESS);
}
