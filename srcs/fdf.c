/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:22:12 by mrezki            #+#    #+#             */
/*   Updated: 2024/05/11 21:22:14 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void clear_mlx(t_mlx *mlx)
{
	memset(mlx->addr, 0, mlx->width * mlx->height * (mlx->bpp / 8));
}

void draw_pixel(t_mlx *mlx, int x, int y, int color)
{
	char    *add;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		add = mlx->addr + (y * mlx->len + x * (mlx->bpp / 8));
		*(unsigned int *)add = color;
	}
}

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

void	check_extension(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[len - 1] == 'f' &&
		str[len - 2] == 'd' &&
		str[len - 3] == 'f' &&
		str[len - 4] == '.')
			return ;
	else
		print_error(WRONG_EXT);
}

// void	get_coord()

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "FDF");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->mlx, &mlx->bpp, &mlx->len, &mlx->end);
}

void	parse_map(char *map, t_mlx *mlx)
{
	(void)mlx;
	char	*str = NULL;
	char	*tmp = NULL;
	int		fd;
	int		rows;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		print_error(EIO);
	rows = 0;
	while (1)
	{
		// get_coord(str, &mlx);
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		str = ft_strjoin(str, tmp);
		printf("str: %s\ntmp: %s\n", str, tmp);
		free(tmp);
		rows++;
	}
	free(str);
}

int	key(int key, t_mlx *mlx)
{
	(void)mlx;
	if (key == 53)
		exit(EXIT_SUCCESS);
	return (0);
}

void	mlx_hooks(t_mlx *mlx)
{
	mlx_key_hook(mlx->win, key, &mlx);
}

void	f(){system("leaks fdf");};

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	atexit(f);
	if (argc != 2)
		print_error(INVALID_ARGS);
	check_extension(argv[1]);
	init_mlx(&mlx);
	mlx_hooks(&mlx);
	parse_map(argv[1], &mlx);
	// mlx_loop(mlx.mlx);
	return (EXIT_SUCCESS);
}
