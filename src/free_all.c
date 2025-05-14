#include "func_drawer.h"

int	on_destroy(t_data *drawer)
{
	if (drawer->mlx)
	{
		mlx_destroy_image(drawer->mlx, drawer->img.img);
		mlx_destroy_window(drawer->mlx, drawer->win);
		mlx_destroy_display(drawer->mlx);
		free(drawer->mlx);
	}
	exit(EXIT_SUCCESS);
	return (0);
}
