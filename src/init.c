#include "func_drawer.h"

void init_struct(t_data *drawer)
{
	drawer->mlx = NULL;
	drawer->win = NULL;
	drawer->center_math_x = 0.0;
	drawer->center_math_y = 0.0;
	drawer->zoom = 50.0;
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
