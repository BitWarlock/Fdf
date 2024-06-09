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

char	*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(*str) * (size + 1))))
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}

static int	count_size(int n)
{
	int i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int num)
{
	char		*dst;
	int			count;
	int			i;
	long int	n;

	n = num;
	count = count_size(n);
	i = 0;
	if (n < 0 || count == 0)
		count++;
	if (!(dst = ft_strnew(count)))
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		dst[0] = '-';
		i++;
	}
	while (count > i)
	{
		count--;
		dst[count] = (n % 10) + '0';
		n /= 10;
	}
	return (dst);
}

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

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

void	free_vertex(t_vertex **points)
{
	t_vertex	*next;
	t_vertex	*tmp;

	if (!(*points))
		return ;
	tmp = *points;
	while ((*points))
	{
		next = (*points)->next;
		free(*points);
		*points = next;
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
		last->next = new;
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
// void	print_points(t_mlx *mlx)
// {
// 	t_vertex	*points;
// 	char	*str;
// 	int	i = 0;
//
// 	points = mlx->points;
// 	while(points)
// 	{
// 		str = ft_itoa(points->point.z);
// 		// printf("Point %d: (%f, %f, %f)\n", i, points->point.x, points->point.y, points->point.z);
// 		mlx_string_put(mlx->mlx, mlx->win, points->point.x, points->point.y, 0xFFFFFF, str);
// 		points = points->next;
// 		i++;
// 	}
// }

// void draw_grid(t_mlx *mlx)
// {
// 	t_point *points;
// 	int x;
// 	int y;
// 	int i;
//
// 	points = mlx->coords;
// 	x = -1;
// 	while (++x < mlx->cols * mlx->rows)
// 	{
// 		if (x % mlx->rows != 0)
// 		{
// 			draw_line_bres(points[x - 1], points[x], mlx);
// 		}
// 	}
// 	x = 0;
// 	y = 0;
// 	while (y < mlx->rows)
// 	{
// 		draw_line_bres(points[y], points[y + mlx->rows], mlx);
// 		y++;
// 	}
// 	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
// }
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
		{
			// printf("(%f, %f)->(%f, %f)\n", points[x-1].x, points[x-1].y, points[x].x, points[x].y);
			draw_line_bres(points[x - 1], points[x], mlx);
		}
	}
	x = mlx->rows;
	y = -1;
	while (++y + x < mlx->cols * mlx->rows)
			draw_line_bres(points[y], points[y + x], mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
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

t_point	*get_values(t_mlx *mlx)
{
	t_point	*points;
	int	i;

	points = malloc(sizeof(t_point) * mlx->cols * mlx->rows);
	if (!points)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < mlx->cols * mlx->rows)
	{
		points[i].x = mlx->points->point.x;
		points[i].y = mlx->points->point.y;
		points[i].z = mlx->points->point.z;
		mlx->points = mlx->points->next;
		i++;
	}
	mlx->coords = points;
	free_vertex((t_vertex **)points);
	return (points);
}

void rotate_vec(t_point *point, float x, float y, float z)
{
	float radX = x;
	float radY = y;
	float radZ = z;
	// float newX = (point->x - point->y) * sqrt(2) / 2;
	// float newY = (point->x + point->y) * sqrt(2) / 2 - point->z;
	// point->x = newX;
	// point->y = newY;
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

	// float cosZ = cos(radZ);
	// float sinZ = sin(radZ);
	// newX = cosZ * point->x - sinZ * point->y;
	// newY = sinZ * point->x + cosZ * point->y;
	// point->x = newX;
	// point->y = newY;
}

void rotate_for_iso_projection(t_point *point)
{
    float newX = (point->x - point->y) * sqrt(2) / 2;
    float newY = (point->x + point->y) * sqrt(2) / 2 - point->z;
    point->x = newX;
    point->y = newY;
}
void	rotate(int size, t_mlx *mlx)
{
	float	center_x = 0, center_y = 0, center_z = 0;

	for (int i = 0; i < size; i++)
	{
		center_x += mlx->coords[i].x;
		center_y += mlx->coords[i].y;
		center_z += mlx->coords[i].z;
	}

	center_x /= size;
	center_y /= size;
	center_z /= size;
	for (int i = 0; i < size; i++)
	{
		mlx->coords[i].x -= center_x;
		mlx->coords[i].y -= center_y;
		mlx->coords[i].z -= center_z;

		rotate_for_iso_projection(&mlx->coords[i]);
		// rotate_vec(&mlx->coords[i], 45 * M_PI / 180, 45 * M_PI / 180, 0);
		// rotate_vec(&mlx->coords[i], -(45 * M_PI / 180), (35 * M_PI / 180), 0);
		printf("%f\n", mlx->coords[i].z);
		mlx->coords[i].x += WIDTH / 2;
		mlx->coords[i].y += HEIGHT / 2;
	}
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
	get_values(&mlx);
	rotate(mlx.cols * mlx.rows, &mlx);
	draw_grid(&mlx);
	free_vertex(&mlx.points);
	mlx_loop(mlx.mlx);
	return (EXIT_SUCCESS);
}
