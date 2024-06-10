#include "/usr/local/include/mlx.h"
#include <libc.h>

typedef struct s_mlx
{
	float	x_angle;
	float	y_angle;
	float	z_angle;
	float	mid_x;
	float	mid_y;
	float	scale;
	void    *mlx;
	void    *win;
	void    *img;
	int     width;
	int     height;
	int     bpp;
	int     end;
	int     len;
	int	color;
	int	rotate;
	int	flash;
	int	reflect;
	char    *addr;
	float	**arr;
}       t_mlx;

void	get_values(t_mlx *mlx)
{
	int	i;
	float	**arr;

	arr = malloc(sizeof(float *) * 6);
	if (!arr)
		exit(1);
	for (int i = 0; i < 6; i++)
		arr[i] = (float *)malloc(sizeof(float));
	i = 0;
	while (i < 6)
	{
		arr[i][0] = 7;
		arr[i][1] = 8;
		arr[i][2] = 9;
		i++;
	}
	for (int i = 0; i < 6; i++)
		printf("(%f, %f, %f)\n", arr[i][0], arr[i][1], arr[i][2]);
	mlx->arr = arr;
	// for (int i = 0; i < 6; i++)
		// free(arr[i]);
	// free(arr);
}

void	test(t_mlx *mlx)
{
	int	i;
	float	**arr;

	arr = malloc(sizeof(float *) * 6);
	if (!arr)
		exit(1);
	for (int i = 0; i < 6; i++)
		arr[i] = (float *)malloc(sizeof(float));
	i = 0;
	while (i < 6)
	{
		arr[i][0] = 7;
		arr[i][1] = 8;
		arr[i][2] = 9;
		i++;
	}
	// for (int i = 0; i < 6; i++)
	// 	free(mlx->arr[i]);
	// free(mlx->arr);

}
void	f(){system("leaks a.out");};
int	main(int argc, char *argv[])
{
	t_mlx mlx;
	atexit(f);
	get_values(&mlx);
	test(&mlx);

	return (0);
}
