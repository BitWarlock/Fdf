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

#include "../minilibx/mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <sys/errno.h>
#include "../libft/libft.h"

typedef struct s_point
{
	float x;
	float y;
	float z;
}		t_point;

typedef struct s_vertex
{
	t_point	point;
	struct s_vertex	*next;
}		t_vertex;

typedef struct s_mlx
{
	float	x_angle;
	float	y_angle;
	float	z_angle;
	float	mid_x;
	float	mid_y;
	void    *mlx;
	void    *win;
	void    *img;
	int     bpp;
	int     end;
	int     len;
	int	rows;
	int	cols;
	int	color;
	char    *addr;
	t_vertex	*points;
	t_point		*coords;
}		t_mlx;

typedef struct s_bres
{
	int	x_step;
	int	y_step;
	int	dx;
	int	dy;
}		t_bres;

// void	print_points(t_vertex *head);
void	draw_line_bres(t_point a, t_point b, t_mlx *mlx);
void rotate_vec(t_point *point, float x, float y, float z);

#endif // ! FDF_H
