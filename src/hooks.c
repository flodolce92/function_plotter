#include "func_drawer.h"

int	handle_key_press(int keycode, t_data *drawer)
{
	// if (keycode == W)
	// {
	// 	drawer->p_pos.direction = BACK;
	// 	drawer->keys.w = true;
	// }
	// else if (keycode == A)
	// {
	// 	drawer->p_pos.direction = LEFT;
	// 	drawer->keys.a = true;
	// }
	// else if (keycode == S)
	// {
	// 	drawer->p_pos.direction = FRONT;
	// 	drawer->keys.s = true;
	// }
	// else if (keycode == D)
	// {
	// 	drawer->p_pos.direction = RIGHT;
	// 	drawer->keys.d = true;
	// }
	// else
	if (keycode == ESC)
		on_destroy(drawer);
	return (0);
}

int	handle_key_released(int keycode, t_data *drawer)
{
	if (keycode == W)
		drawer->keys.w = false;
	else if (keycode == A)
		drawer->keys.a = false;
	else if (keycode == S)
		drawer->keys.s = false;
	else if (keycode == D)
		drawer->keys.d = false;
	return (0);
}

// int	loop_hook(t_data *drawer)
// {
// 	drawer->frames++;
// 	update_player_position(drawer);
// 	fill_window(drawer);
// 	usleep(80000);
// 	return (0);
// }
