#include "func_drawer.h"

void error_message(char *message, t_data *drawer)
{
	ft_putstr_fd("Error: ", STDOUT_FILENO);
	ft_putendl_fd(message, STDOUT_FILENO);
	if (drawer)
		on_destroy(drawer);
	exit(EXIT_FAILURE);
}

void create_window(t_data *drawer)
{
	drawer->mlx = mlx_init();
	if (!drawer->mlx)
		error_message("mlx_init failed.", drawer);

	drawer->win = mlx_new_window(drawer->mlx,
								 WINDOW_WIDTH,
								 WINDOW_HEIGHT,
								 "so_long");
	if (!drawer->win)
		error_message("mlx_new_window failed.", drawer);

	drawer->img.img = mlx_new_image(drawer->mlx,
									WINDOW_WIDTH,
									WINDOW_HEIGHT);
	if (!drawer->img.img)
		error_message("mlx_new_image failed.", drawer);

	drawer->img.addr = mlx_get_data_addr(drawer->img.img,
										 &drawer->img.bpp,
										 &drawer->img.line_length,
										 &drawer->img.endian);
	if (!drawer->img.addr)
		error_message("mlx_get_data_addr failed.", drawer);
}

int main(int ac, char **av)
{
	t_data drawer;

	if (ac < 2)
		error_message("Wrong number of arguments. \
			\nUsage: ./draw <function>",
					  NULL);

	init_struct(&drawer);
	drawer.functions = av + 1;
	create_window(&drawer);
	mlx_loop_hook(drawer.mlx, loop_hook, &drawer);
	mlx_hook(drawer.win, 2, 1L << 0, handle_key_press, &drawer);
	mlx_hook(drawer.win, 3, 1L << 1, handle_key_released, &drawer);
	mlx_hook(drawer.win, 17, 1L << 17, on_destroy, &drawer);
	mlx_loop(drawer.mlx);

	return (0);
}
