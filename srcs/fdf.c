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

void	add_to_vertex(t_vertex **head, int x, int y, int z)
{
	t_vertex	*new;
	t_vertex	*last;

	new = malloc(sizeof(t_vertex));
	if (!new)
		print_error(EIO);
	if (!*head)
	{
		*head = new;
		new->point.x = (float)x;
		new->point.y = (float)y;
		new->point.z = (float)z;
		new->next = NULL;
	}
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new;
		new->next = NULL;
		new->point.x = (float)x;
		new->point.y = (float)y;
		new->point.z = (float)z;
	}
}
void	get_coord(char *str, t_mlx *mlx, int cols)
{
	t_vertex	*last;
	t_vertex	*new;
	t_vertex	*current;
	char		**strs;
	int		rows;

	strs = ft_split(str, ' ');
	new = NULL;
	rows = 0;
	while (strs[rows])
	{
		add_to_vertex(&new, rows * 30, cols * 30, ft_atoi(strs[rows]) * 3);
		rows++;
	}
	mlx->rows = rows;
	if (mlx->points == NULL)
		mlx->points = new;
	else
	{
		last = mlx->points;
		while (last->next)
			last = last->next;
		current = new;
		while (current)
		{
			last->next = current;
			last = current;
			current = current->next;
		}
	}
	ft_free_all(strs);
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "FDF");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->len, &mlx->end);
	mlx->color = 0xFFFFFF;
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
void	draw_grid(t_mlx *mlx)
{
	float	**points;
	int	x;
	int	y;
	int	i;

	points = mlx->xyz;
	x = -1;
	while (++x < mlx->cols * mlx->rows)
	{
		if (x % mlx->rows != 0)
			draw_line_bres((t_point){points[x - 1][0], points[x - 1][1]},
			(t_point){points[x][0], points[x][1]}, mlx);
	}
	x = mlx->rows;
	y = -1;
	while (++y + x < mlx->cols * mlx->rows)
		draw_line_bres((t_point){points[y][0], points[y][1]},
			(t_point){points[x + y][0], points[x + y][1]}, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	// for (int i = 0; i < mlx->cols * mlx->rows; i++)
		// free(mlx->xyz[i]);
	// free_arr(mlx->xyz, mlx->cols * mlx->rows);
}

void	parse_map(char *map, t_mlx *mlx)
{
	char	*tmp = NULL;
	int		fd;
	int		cols;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		print_error(EIO);
	cols = 0;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		get_coord(tmp, mlx, cols);
		free(tmp);
		cols++;
	}
	mlx->cols = cols;
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

void	get_values(t_mlx *mlx)
{
	int	i;
	float	**arr;

	arr = malloc(sizeof(float *) * mlx->cols * mlx->rows);
	if (!arr)
		exit(1);
	printf("%d\n", mlx->cols * mlx->rows);
	for (int i = 0; i < mlx->cols * mlx->rows; i++)
		arr[i] = (float *)malloc(sizeof(float));
	i = 0;
	while (i < mlx->rows * mlx->cols)
	{
		arr[i][0] = mlx->points->point.x;
		arr[i][1] = mlx->points->point.y;
		arr[i][2] = mlx->points->point.z;
		mlx->points = mlx->points->next;
		i++;
	}
	mlx->xyz = arr;
	// i = 0;
	// while (i < mlx->cols * mlx->rows)
	// {
	// 	free(arr[i]);
	// 	i++;
	// }
	// free(arr);
	// free_vertex(mlx->points);
	// free_arr(arr, mlx->cols * mlx->rows);
	// free_arr(arr);
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

void	rotate_for_iso_projection(float *point)
{
	float	newX;
	float	newY;

	newX = (point[0] - point[1]) * sqrt(2) / 2;
	newY = (point[0] + point[1]) * sqrt(2) / 2 - point[2];
	point[0] = newX;
	point[1] = newY;
}

void	rotate(int size, t_mlx *mlx)
{
	float	center_x = 0, center_y = 0, center_z = 0;

	for (int i = 0; i < size; i++)
	{
		center_x += mlx->xyz[i][0];
		center_y += mlx->xyz[i][1];
		center_z += mlx->xyz[i][2];
	}

	center_x /= size;
	center_y /= size;
	center_z /= size;
	for (int i = 0; i < size; i++)
	{
		mlx->xyz[i][0] -= center_x;
		mlx->xyz[i][1] -= center_y;
		mlx->xyz[i][2] -= center_z;
		rotate_for_iso_projection(mlx->xyz[i]);
		mlx->xyz[i][0] += WIDTH / 2;
		mlx->xyz[i][1] += HEIGHT / 2;
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
