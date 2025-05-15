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
		drawer->center_math_y += PAN_SPEED / drawer->zoom;
	if (drawer->keys.s)
		drawer->center_math_y -= PAN_SPEED / drawer->zoom;
	if (drawer->keys.a)
		drawer->center_math_x -= PAN_SPEED / drawer->zoom;
	if (drawer->keys.d)
		drawer->center_math_x += PAN_SPEED / drawer->zoom;

	if (drawer->keys.up)
		drawer->zoom *= ZOOM_FACTOR;
	if (drawer->keys.down)
		drawer->zoom /= ZOOM_FACTOR;

	if (drawer->zoom < MIN_ZOOM)
		drawer->zoom = MIN_ZOOM;
	if (drawer->zoom > MAX_ZOOM)
		drawer->zoom = MAX_ZOOM;

	draw_function(drawer->function, drawer);
	mlx_put_image_to_window(drawer->mlx, drawer->win, drawer->img.img, 0, 0);
	return (0);
}
