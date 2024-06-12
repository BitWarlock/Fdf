/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 03:35:33 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/11 03:35:35 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_extension(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[len - 1] == 'f'
		&& str[len - 2] == 'd'
		&& str[len - 3] == 'f'
		&& str[len - 4] == '.')
		return ;
	else
		print_error(WRONG_EXT);
}

void	parse_map(char *map, t_mlx *mlx)
{
	char	*tmp;
	int		fd;
	int		cols;

	tmp = NULL;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		print_error(EIO);
	cols = 0;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		get_coord(tmp, mlx, cols);
		free(tmp);
		cols++;
	}
	mlx->cols = cols;
}

void	add_to_vertex(t_vertex **head, int x, int y, int z)
{
	t_vertex	*new;
	t_vertex	*last;

	new = malloc(sizeof(t_vertex));
	if (!new)
		print_error(EIO);
	if (!*head)
	{
		*head = new;
		new->point.x = (float)x;
		new->point.y = (float)y;
		new->point.z = (float)z;
		new->next = NULL;
	}
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new;
		new->next = NULL;
		new->point.x = (float)x;
		new->point.y = (float)y;
		new->point.z = (float)z;
	}
}
void	get_coord(char *str, t_mlx *mlx, int cols)
{
	t_vertex	*last;
	t_vertex	*new;
	t_vertex	*current;
	char		**strs;
	int		rows;

	strs = ft_split(str, ' ');
	new = NULL;
	rows = 0;
	while (strs[rows])
	{
		add_to_vertex(&new, rows * 30, cols * 30, ft_atoi(strs[rows]) * 3);
		rows++;
	}
	mlx->rows = rows;
	if (mlx->points == NULL)
		mlx->points = new;
	else
	{
		last = mlx->points;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	ft_free_all(strs);
}

