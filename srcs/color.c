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
		return (0xFFFFFF);
}

int	random_color(void)
{
	static int	i;
	int			r;
	int			g;
	int			b;
	long		divisor;

	i++;
	divisor = 4206923 * i;
	r = (divisor >> 16) % 256;
	g = (divisor >> 8) % 256;
	b = divisor % 256;
	return ((r << 16) | (g << 8) | b);
}

void	change_color(t_mlx *mlx)
{
	int	i;

	i = 0;
	mlx->color = random_color();
	while (i < mlx->rows * mlx-> cols)
	{
		if (mlx->coords[i].standard == 1)
			mlx->coords[i].color = mlx->color;
		i++;
	}
	draw_grid(mlx);
}
