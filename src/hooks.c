#include "func_drawer.h"

int handle_key_press(int keycode, t_data *drawer)
{
	if (keycode == W)
		drawer->keys.w = true;
	else if (keycode == A)
		drawer->keys.a = true;
	else if (keycode == S)
		drawer->keys.s = true;
	else if (keycode == D)
		drawer->keys.d = true;
	else if (keycode == ARROW_UP)
		drawer->keys.up = true;
	else if (keycode == ARROW_DOWN)
		drawer->keys.down = true;
	else if (keycode == ESC)
		on_destroy(drawer);
	return (0);
}

int handle_key_released(int keycode, t_data *drawer)
{
	if (keycode == W)
		drawer->keys.w = false;
	else if (keycode == A)
		drawer->keys.a = false;
	else if (keycode == S)
		drawer->keys.s = false;
	else if (keycode == D)
		drawer->keys.d = false;
	else if (keycode == ARROW_UP)
		drawer->keys.up = false;
	else if (keycode == ARROW_DOWN)
		drawer->keys.down = false;
	return (0);
}

int loop_hook(t_data *drawer)
{
	if (drawer->keys.w)
		drawer->y_offset -= 10;
	if (drawer->keys.s)
		drawer->y_offset += 10;
	if (drawer->keys.a)
		drawer->x_offset -= 10;
	if (drawer->keys.d)
		drawer->x_offset += 10;
	if (drawer->keys.up)
		drawer->zoom *= 1.01;
	if (drawer->keys.down)
		drawer->zoom /= 1.01;

	draw_function(drawer->function, drawer);
	mlx_put_image_to_window(drawer->mlx, drawer->win, drawer->img.img, 0, 0);
	return (0);
}
