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
}		point;

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
	int     width;
	int     height;
	int     bpp;
	int     end;
	int     len;
	char    *addr;
	point	*vec;
}		t_mlx;

#endif // ! FDF_H
