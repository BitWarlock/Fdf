/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghostface <ghostface@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:28:32 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/20 19:47:06 by ghostface        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_free_all(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = -1;
	while (strs[++i])
	{
		free(strs[i]);
		strs[i] = NULL;
	}
	free(strs);
	strs = NULL;
}

void	free_vertex(t_vertex *head)
{
	t_vertex	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void	clear_mlx(t_mlx *mlx)
{
	ft_memset(mlx->addr, 0, WIDTH * HEIGHT * (mlx->bpp / 8));
}
