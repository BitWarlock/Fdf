/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:07:29 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/07 17:07:30 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void clear_mlx(t_mlx *mlx)
{
	memset(mlx->addr, 0, WIDTH * HEIGHT * (mlx->bpp / 8));
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

void	ft_free_all(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = -1;
	while (strs[++i])
	{
		free(strs[i]);
		strs[i] = NULL;
	}
	free(strs);
	strs = NULL;
}

void free_vertex(t_vertex *head)
{
	t_vertex *tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
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

void print_points(t_mlx *mlx)
{
	t_point *points = mlx->coords;
	int i;

	for (i = 0; i < mlx->cols * mlx->rows; i++) {
		printf("P: %d | (%f, %f, %f)\n", i, points[i].x, points[i].y, points[i].z);
		mlx_string_put(mlx->mlx, mlx->win, points[i].x, points[i].y, 0xFFFFFF, "P");
	}
}

void	free_arr(float **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
void	draw_x(t_mlx *mlx)
{
	draw_line_bres((t_point){mlx->mid_x, 0}, (t_point){mlx->mid_x, HEIGHT}, mlx);
	draw_line_bres((t_point){0, mlx->mid_y}, (t_point){WIDTH, mlx->mid_y}, mlx);
}

void	draw_grid(t_mlx *mlx)
{
	t_point	*points;
	int	x;
	int	y;
	int	i;

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
	// draw_x(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void rotate_vec(t_point *point, float x, float y, float z)
{
	float radX = x;
	float radY = y;
	float radZ = z;

	float cosX = cos(radX);
	float sinX = sin(radX);
	float newY = cosX * point->y - sinX * point->z;
	float newZ = sinX * point->y + cosX * point->z;
	point->y = newY;
	point->z = newZ;

	float cosY = cos(radY);
	float sinY = sin(radY);
	float newX = cosY * point->x + sinY * point->z;
	newZ = -sinY * point->x + cosY * point->z;
	point->x = newX;
	point->z = newZ;

	float cosZ = cos(radZ);
	float sinZ = sin(radZ);
	newX = cosZ * point->x - sinZ * point->y;
	newY = sinZ * point->x + cosZ * point->y;
	point->x = newX;
	point->y = newY;
}

void	rotate_for_iso_projection(t_point *point)
{
	float	newX;
	float	newY;

	newX = (point->x - point->y) * sqrt(2) / 2;
	newY = (point->x + point->y) * sqrt(2) / 2 - point->z;
	point->x = newX;
	point->y = newY;
}

void	translate(t_point *p, float tx, float ty, float tz)
{
	p->x += tx;
	p->y += ty;
	p->z += tz;
}

void	centroid(t_point *points, int size, t_mlx *mlx)
{
	float	center_x;
	float	center_y;
	float	center_z;
	int	i;

	center_x = 0;
	center_y = 0;
	center_z = 0;
	i = 0;
	while (i < size)
	{
		center_x += points[i].x;
		center_y += points[i].y;
		center_z += points[i].z;
		i++;
	}
	mlx->centroid.x = center_x / size;
	mlx->centroid.y = center_y / size;
	mlx->centroid.z = center_z / size;
}

void	rotate(int size, t_mlx *mlx)
{
	int	i;

	i = 0;
	centroid(mlx->coords, size, mlx);
	while (i < size)
	{
		translate(&mlx->coords[i], -mlx->centroid.x, -mlx->centroid.y, -mlx->centroid.z);
		rotate_for_iso_projection(&mlx->coords[i]);
		mlx->coords[i].x += mlx->mid_x;
		mlx->coords[i].y += mlx->mid_y;
		i++;
	}
}

void	f(){
	// system ("export MallocStackLogging=1");
	system("leaks -quiet fdf");};

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	// atexit(f);
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
