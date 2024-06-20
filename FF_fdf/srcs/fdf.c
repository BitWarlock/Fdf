/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghostface <ghostface@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:07:29 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/20 19:45:22 by ghostface        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	mlx->color = 0xffffff;
	mlx->points = NULL;
	mlx->mid_x = (float)WIDTH / 2;
	mlx->mid_y = (float)HEIGHT / 2;
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
	rotate(mlx.cols * mlx.rows, &mlx);
	draw_grid(&mlx);
	mlx_hooks(&mlx);
	free_vertex(mlx.points);
	mlx_loop(mlx.mlx);
	return (EXIT_SUCCESS);
}
