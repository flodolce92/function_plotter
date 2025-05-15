#ifndef FUNCTDRAWER_H
#define FUNCTDRAWER_H

#include "mlx.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Window dimensions */
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

/* Movement and zoom parameters */
#define PAN_SPEED 10.0
#define MIN_ZOOM 0.1
#define MAX_ZOOM 10000.0
#define ZOOM_FACTOR 1.01

/* Key codes */
enum e_keys
{
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	ESC = 65307,
	ARROW_UP = 65362,
	ARROW_DOWN = 65364,
};

typedef struct s_key_press
{
	bool a;
	bool d;
	bool s;
	bool w;
	bool up;
	bool down;
} t_key_press;

typedef struct s_image
{
	void *img;
	char *addr;
	int bpp;
	int line_length;
	int endian;
} t_image;

typedef struct s_data
{
	void *mlx;
	void *win;
	double center_math_x;
	double center_math_y;
	double zoom;
	char **functions;
	t_image img;
	t_key_press keys;
} t_data;

/* Initialization and cleanup */
void init_struct(t_data *drawer);
void create_window(t_data *drawer);
int on_destroy(t_data *drawer);

/* Event handlers */
int handle_key_press(int keycode, t_data *drawer);
int handle_key_released(int keycode, t_data *drawer);
int loop_hook(t_data *drawer);

/* Drawing functions */
void draw_function(char **functions, t_data *drawer);
void my_mlx_pixel_put(t_image *img, int x, int y, int color);
void draw_line_bresenham(t_data *drawer, int x1, int y1, int x2, int y2, int color);
void create_plane(t_data *drawer);
double evaluate_expression(const char *expression, double x);

#endif
