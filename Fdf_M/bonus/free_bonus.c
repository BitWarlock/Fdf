/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:28:32 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/22 15:34:12 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "keys_macos.h"

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
	ft_memset(mlx->addr, 0x003300, WIDTH * HEIGHT * (mlx->bpp / 8));
}

void reflection(t_mlx *mlx)
{
	memset(mlx->addr, 0x000FFF, WIDTH * HEIGHT * (mlx->bpp / 8));
}
