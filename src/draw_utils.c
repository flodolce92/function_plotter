#include "func_drawer.h"

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char *dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void draw_line_bresenham(t_data *drawer, int x1, int y1, int x2, int y2, int color)
{
	int dx = abs(x2 - x1);
	int dy = -abs(y2 - y1); // Use negative dy for standard algorithm with positive error terms
	int sx = x1 < x2 ? 1 : -1;
	int sy = y1 < y2 ? 1 : -1;
	int err = dx + dy; // Error term
	int e2;

	while (1)
	{
		my_mlx_pixel_put(&drawer->img, x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break;
		e2 = 2 * err;
		if (e2 >= dy) // equivalent to e2 >= -abs(y2-y1)
		{
			err += dy;
			x1 += sx;
		}
		if (e2 <= dx) // equivalent to e2 <= abs(x2-x1)
		{
			err += dx;
			y1 += sy;
		}
	}
}
