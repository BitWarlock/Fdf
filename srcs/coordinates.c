/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 04:52:03 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/13 05:52:05 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_values(t_mlx *mlx)
{
	t_point		*points;
	t_vertex	*head;
	int			i;

	points = malloc(sizeof(t_point) * mlx->cols * mlx->rows);
	if (!points)
		exit(EXIT_FAILURE);
	i = 0;
	head = mlx->points;
	while (i < mlx->cols * mlx->rows)
	{
		points[i].x = mlx->points->point.x;
		points[i].y = mlx->points->point.y;
		points[i].z = mlx->points->point.z;
		if (!mlx->points->next)
			break ;
		mlx->points = mlx->points->next;
		i++;
	}
	mlx->coords = points;
	free_vertex(head);
}
