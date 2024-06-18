/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 05:52:25 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/14 03:38:28 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

float	max_z(t_point *p, int size)
{
	float	max;
	int		i;

	i = 0;
	max = 0;
	while (i < size)
	{
		if (p[i].z > max)
			max = p[i].z;
		i++;
	}
	return (max);
}

float	min_z(t_point *p, int size)
{
	float	min;
	int		i;

	i = 0;
	min = 0;
	while (i < size)
	{
		if (p[i].z < min)
			min = p[i].z;
		i++;
	}
	return (min);
}

float	min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

float	max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

float	get_scale(int size, t_mlx *mlx)
{
	return (min((float)WIDTH / mlx->rows / 2, (float)HEIGHT / mlx->cols / 2));
}
