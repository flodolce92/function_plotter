#include "func_drawer.h"

void create_plane(t_data *drawer)
{
	int px, py;	   // screen pixel coordinates
	int sx, sy;	   // screen pixel coordinates for grid/axis lines
	double mx, my; // math coordinates

	// Clear image (background to dark grey)
	ft_memset(drawer->img.addr, 0x1A1A1A, WINDOW_HEIGHT * drawer->img.line_length);

	// Determine visible math range
	double math_x_min = drawer->center_math_x - (WINDOW_WIDTH / 2.0) / drawer->zoom;
	double math_x_max = drawer->center_math_x + (WINDOW_WIDTH / 2.0) / drawer->zoom;
	double math_y_min = drawer->center_math_y - (WINDOW_HEIGHT / 2.0) / drawer->zoom;
	double math_y_max = drawer->center_math_y + (WINDOW_HEIGHT / 2.0) / drawer->zoom;

	// Adaptive grid step
	double grid_step = 1.0;
	if (drawer->zoom < 5)
		grid_step = 10.0;
	else if (drawer->zoom < 20)
		grid_step = 5.0;
	else if (drawer->zoom < 75)
		grid_step = 1.0;
	else if (drawer->zoom < 150)
		grid_step = 0.5;
	else if (drawer->zoom < 300)
		grid_step = 0.25;
	else
		grid_step = 0.1;

	// Vertical grid lines
	for (mx = floor(math_x_min / grid_step) * grid_step; mx <= math_x_max; mx += grid_step)
	{
		sx = (int)((mx - drawer->center_math_x) * drawer->zoom + WINDOW_WIDTH / 2.0);
		if (sx >= 0 && sx < WINDOW_WIDTH)
		{
			for (py = 0; py < WINDOW_HEIGHT; py++)
				my_mlx_pixel_put(&drawer->img, sx, py, 0x303030); // Dim grid
		}
	}

	// Horizontal grid lines
	for (my = floor(math_y_min / grid_step) * grid_step; my <= math_y_max; my += grid_step)
	{
		sy = (int)(WINDOW_HEIGHT / 2.0 - (my - drawer->center_math_y) * drawer->zoom);
		if (sy >= 0 && sy < WINDOW_HEIGHT)
		{
			for (px = 0; px < WINDOW_WIDTH; px++)
				my_mlx_pixel_put(&drawer->img, px, sy, 0x303030); // Dim grid
		}
	}

	// Y-axis (mathematical x=0)
	int axis_y_sx = (int)((0.0 - drawer->center_math_x) * drawer->zoom + WINDOW_WIDTH / 2.0);
	if (axis_y_sx >= 0 && axis_y_sx < WINDOW_WIDTH)
	{
		for (py = 0; py < WINDOW_HEIGHT; py++)
			my_mlx_pixel_put(&drawer->img, axis_y_sx, py, 0xBBBBBB); // Brighter axis
	}

	// X-axis (mathematical y=0)
	int axis_x_sy = (int)(WINDOW_HEIGHT / 2.0 - (0.0 - drawer->center_math_y) * drawer->zoom);
	if (axis_x_sy >= 0 && axis_x_sy < WINDOW_HEIGHT)
	{
		for (px = 0; px < WINDOW_WIDTH; px++)
			my_mlx_pixel_put(&drawer->img, px, axis_x_sy, 0xBBBBBB); // Brighter axis
	}
}
