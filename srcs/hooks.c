#include "fdf.h"

int	key(int key, t_mlx *mlx)
{
	(void)mlx;
	if (key == 53)
		exit(EXIT_SUCCESS);
	return (0);
}

int	quit(int key)
{
	exit(EXIT_SUCCESS);
}

void	mlx_hooks(t_mlx *mlx)
{
	mlx_key_hook(mlx->win, key, &mlx);
	mlx_hook(mlx->win, 17, 0, quit, mlx);
}
