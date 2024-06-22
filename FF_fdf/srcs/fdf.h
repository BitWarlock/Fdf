/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:22:49 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/22 15:32:21 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* Error Codes */

# define INVALID_ARGS	30
# define WRONG_EXT	31

/* Colors */

# define RED		"\033[31m"

# include "keys_macos.h"
# include "/usr/local/include/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <sys/errno.h>
# include "../libft/libft.h"

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
	int		standard;
	int		rotate;
}		t_point;

typedef struct s_vertex
{
	struct s_vertex	*next;
	t_point			point;
}		t_vertex;

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
	int	*c;
}		t_bres;

typedef struct s_mlx
{
	t_vertex	*points;
	t_point		*coords;
	t_point		centroid;
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

void	add_to_vertex(t_vertex **head, int x, int y, char *z);
void	translate(t_point *p, float tx, float ty, float tz);
void	draw_line_bres(t_point a, t_point b, t_mlx *mlx);
void	scale_up(t_point *points, float scale, float z);
void	draw_pixel(t_mlx *mlx, int x, int y, int color);
void	centroid(t_point *points, int size, t_mlx *mlx);
void	get_coord(char *str, t_mlx *mlx, int cols);
void	parse_map(char *map, t_mlx *mlx);
void	iso_projection(t_point *point);
void	rotate(int size, t_mlx *mlx);
void	free_vertex(t_vertex *head);
void	check_extension(char *str);
void	ft_free_all(char **strs);
void	print_error(int error);
void	get_values(t_mlx *mlx);
void	draw_grid(t_mlx *mlx);
void	mlx_hooks(t_mlx *mlx);
void	clear_mlx(t_mlx *mlx);
void	iso(t_mlx *mlx);

float	get_scale(int size, t_mlx *mlx);
float	max_z(t_point *p, int size);
float	min_z(t_point *p, int size);
float	min(float a, float b);
float	max(float a, float b);
float	_abs(float a);

int		get_color(char *str);

#endif // ! FDF_H
