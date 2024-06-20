/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 03:40:28 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/14 03:40:29 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

int	search_comma(char *str)
{
	while (*str)
	{
		if (*str == ',')
			return (1);
		str++;
	}
	return (0);
}

int	get_color(char *str)
{
	char	**strs;
	int		color;

	if (search_comma(str))
	{
		strs = ft_split(str, ',');
		color = atoi_base(strs[1], 16);
		ft_free_all(strs);
		return (color);
	}
	else
		return (0xFFFFFE);
}

void	change_color(t_mlx *mlx)
{
	int	i;

	i = 0;
	mlx->color = rand() % 0xFFFFFF;
	while (i < mlx->rows * mlx-> cols)
	{
		if (mlx->coords[i].standard == 1)
			mlx->coords[i].color = mlx->color;
		i++;
	}
	draw_grid(mlx);
}
