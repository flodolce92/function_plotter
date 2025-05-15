#include "func_drawer.h"

void	init_struct(t_data *drawer)
{
	drawer->mlx = NULL;
	drawer->win = NULL;
	drawer->x_offset = 0;
	drawer->y_offset = 0;
	drawer->zoom = 1.0;
	drawer->function = NULL;
	drawer->img.img = NULL;
	drawer->img.addr = NULL;
	drawer->img.bpp = 0;
	drawer->img.line_length = 0;
	drawer->img.endian = 0;
	drawer->keys.w = false;
	drawer->keys.a = false;
	drawer->keys.s = false;
	drawer->keys.d = false;
	drawer->keys.up = false;
	drawer->keys.down = false;
}
