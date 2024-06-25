/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 05:52:21 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/22 15:32:26 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key(int key, t_mlx *mlx)
{
	(void)mlx;
	if (key == ESC)
		exit(EXIT_SUCCESS);
	return (0);
}

int	quit(int key, t_mlx *mlx)
{
	(void)mlx;
	(void)key;
	exit(EXIT_SUCCESS);
}

void	mlx_hooks(t_mlx *mlx)
{
	mlx_key_hook(mlx->win, key, mlx);
	mlx_hook(mlx->win, 17, 0, quit, mlx);
}
