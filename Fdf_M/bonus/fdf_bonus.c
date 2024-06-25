/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:07:29 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/22 15:34:07 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	print_error(int error)
{
	if (error == INVALID_ARGS)
		ft_printf(2, RED"Usage: ./fdf maps/map.fdf\n");
	if (error == WRONG_EXT)
		ft_printf(2, RED"Wrong extension: should end with .fdf\n");
	else
		ft_printf(2, RED"Error: %s\n", strerror(error));
	exit(EXIT_FAILURE);
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		print_error(EIO);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "FDF");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img || !mlx->win)
		print_error(EIO);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->len, &mlx->end);
	if (!mlx->addr)
		print_error(EIO);
	mlx->color = 0xffffff;
	mlx->points = NULL;
	mlx->mid_x = (float)WIDTH / 2;
	mlx->mid_y = (float)HEIGHT / 2;
	mlx->centroid.rotate = 0;
	mlx->x_angle = 0.002;
	mlx->y_angle = 0.002;
	mlx->z_angle = 0.002;
	mlx->reflect = 0;
	mlx->text = 1;
}

void	spin(t_mlx *mlx, float x, float y, float z)
{
	int	i;

	i = 0;
	while (i < mlx->rows * mlx->cols)
	{
		mlx->coords[i].x -= mlx->mid_x;
		mlx->coords[i].y -= mlx->mid_y;
		rotate_xyz(&mlx->coords[i], x, y, z);
		mlx->coords[i].x += mlx->mid_x;
		mlx->coords[i].y += mlx->mid_y;
		i++;
	}
	draw_grid(mlx);
}

int	fdf(t_mlx *mlx)
{
	static int	frame;

	if (!frame)
		rotate(mlx->rows * mlx->cols, mlx);
	frame++;
	if (mlx->centroid.rotate & 1)
		spin(mlx, mlx->x_angle, mlx->y_angle, mlx->z_angle);
	if (((mlx->centroid.rotate >> 1) & 1) && frame % 9 == 0)
		change_color(mlx);
	draw_grid(mlx);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	if (argc != 2)
		print_error(INVALID_ARGS);
	check_extension(argv[1]);
	init_mlx(&mlx);
	parse_map(argv[1], &mlx);
	get_values(&mlx);
	mlx_loop_hook(mlx.mlx, fdf, &mlx);
	mlx_hooks(&mlx);
	free_vertex(mlx.points);
	mlx_loop(mlx.mlx);
	return (EXIT_SUCCESS);
}
