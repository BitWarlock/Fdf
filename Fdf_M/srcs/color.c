/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 03:40:28 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/22 15:32:06 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
