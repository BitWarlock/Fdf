/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:22:49 by mrezki            #+#    #+#             */
/*   Updated: 2024/05/11 21:22:50 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* Error Codes */

# define INVALID_ARGS 30
# define WRONG_EXT 31

/* Colors */

# define RED "\033[31m"

# define HEIGHT 1000
# define WIDTH 1400

# define X 0
# define Y 1
# define Z 2

# include "../minilibx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <sys/errno.h>
# include "../libft/libft.h"

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}		t_point;

typedef struct s_vertex
{
	struct s_vertex	*next;
	t_point			point;
}		t_vertex;

typedef struct s_mlx
{
	t_vertex	*points;
	t_point		*coords;
	t_point		centroid;
	float		x_angle;
	float		y_angle;
	float		z_angle;
	float		mid_x;
	float		mid_y;
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			end;
	int			len;
	int			rows;
	int			cols;
	int			color;
}		t_mlx;

typedef struct s_bres
{
	int	x0;
	int	x1;
	int	y0;
	int	y1;
	int	x_step;
	int	y_step;
	int	dx;
	int	dy;
	int	err;
}		t_bres;

void	draw_line_bres(t_point a, t_point b, t_mlx *mlx);
void	mlx_hooks(t_mlx *mlx);
void	rotate_vec(t_point *point, float x, float y, float z);
void	check_extension(char *str);
void	parse_map(char *map, t_mlx *mlx);
void	add_to_vertex(t_vertex **head, int x, int y, int z);
void	get_coord(char *str, t_mlx *mlx, int cols);
void	print_error(int error);
void	ft_free_all(char **strs);
void	free_vertex(t_vertex *head);
void	get_values(t_mlx *mlx);

#endif // ! FDF_H
