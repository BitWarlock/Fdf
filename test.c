#include "/usr/local/include/mlx.h"

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
}       t_mlx;

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	// init_mlx(&mlx);
	// test_gr(&mlx);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 800, 800, "Spinning cube");
	mlx.img = mlx_new_image(mlx.mlx, 800, 800);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.len, &mlx.end);
	mlx_string_put(mlx.mlx, mlx.win, 100, 100, 0xFFFFFF, "ABC");
	// mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);
	return (0);
}
