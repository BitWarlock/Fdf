/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 04:52:03 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/14 03:38:07 by mrezki           ###   ########.fr       */
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
		points[i].color = mlx->points->point.color;
		if (!mlx->points->next)
			break ;
		mlx->points = mlx->points->next;
		i++;
	}
	mlx->coords = points;
	mlx->points = head;
	free_vertex(head);
}

void	get_coord(char *str, t_mlx *mlx, int cols)
{
	t_vertex	*last;
	t_vertex	*new;
	t_vertex	*current;
	char		**strs;
	int			rows;

	strs = ft_split(str, ' ');
	new = NULL;
	rows = 0;
	while (strs[rows])
	{
		add_to_vertex(&new, rows, cols, strs[rows]);
		rows++;
	}
	mlx->rows = rows;
	if (mlx->points == NULL)
		mlx->points = new;
	else
	{
		last = mlx->points;
		while (last && last->next)
			last = last->next;
		last->next = new;
	}
	ft_free_all(strs);
}