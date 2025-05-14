#include "func_drawer.h"

void error_message(char *message, t_data *drawer)
{
	ft_putstr_fd("Error: ", STDOUT_FILENO);
	ft_putendl_fd(message, STDOUT_FILENO);
	if (drawer)
		on_destroy(drawer);
	exit(EXIT_FAILURE);
}

void create_plane(t_data *drawer)
{
	int x, y;

	ft_memset(drawer->img.addr, 0, WINDOW_HEIGHT * drawer->img.line_length);

	for (y = 0; y < WINDOW_HEIGHT; y++)
	{
		for (x = 0; x < WINDOW_WIDTH; x++)
		{
			if (((x + drawer->x_offset) % 50 == 0) || ((y + drawer->y_offset) % 50 == 0))
			{
				int pixel_index = (y * drawer->img.line_length) + (x * (drawer->img.bpp / 8));
				*(unsigned int *)(drawer->img.addr + pixel_index) = 0x2F2F2F; // Grid color
			}
		}
	}

	for (y = 0; y < WINDOW_HEIGHT; y++)
	{
		for (x = 0; x < WINDOW_WIDTH; x++)
		{
			if ((x + drawer->x_offset) == WINDOW_WIDTH / 2)
			{
				int pixel_index = (y * drawer->img.line_length) + (x * (drawer->img.bpp / 8));
				*(unsigned int *)(drawer->img.addr + pixel_index) = 0xFFFFFF; // Axis color
			}
			if ((y + drawer->y_offset) == WINDOW_HEIGHT / 2)
			{
				int pixel_index = (y * drawer->img.line_length) + (x * (drawer->img.bpp / 8));
				*(unsigned int *)(drawer->img.addr + pixel_index) = 0xFFFFFF; // Axis color
			}
		}
	}
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

double evaluate_expression(const char *expression, double x)
{
	double result;
	char **tokens;
	int i;

	i = 0;
	result = 0.0;
	tokens = ft_split(expression, ' ');
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], 'x'))
		{
			double coefficient = 1.0;
			int power = 1;
			char *x_pos = ft_strchr(tokens[i], 'x');
			char *power_pos = ft_strchr(tokens[i], '^');

			if ((tokens[i][0] == '-' || tokens[i][0] == '+') && tokens[i][1] == 'x')
			{
				if (tokens[i][0] == '-')
					coefficient = -1.0;
			}
			else if (x_pos != tokens[i])
				coefficient = atof(tokens[i]);

			if (power_pos)
				power = atoi(power_pos + 1);

			result += coefficient * pow(x, power);
		}
		else
			result += atof(tokens[i]);
		i++;
	}

	for (int j = 0; tokens[j]; j++)
		free(tokens[j]);
	free(tokens);
	return (result);
}

void draw_function(char *function, t_data *drawer)
{
	int x, y;
	double result;
	int prev_y = 0;

	create_plane(drawer);
	for (x = -WINDOW_WIDTH / 2; x < WINDOW_WIDTH / 2; x++)
	{
		result = evaluate_expression(function, x + drawer->x_offset);
		y = (int)(WINDOW_HEIGHT / 2 - result) - drawer->y_offset;

		if (x != -WINDOW_WIDTH / 2)
		{
			int dx = x + WINDOW_WIDTH / 2;
			int prev_dx = (x - 1) + WINDOW_WIDTH / 2;

			int clipped_prev_y = prev_y;
			int clipped_y = y;

			if (prev_y < 0)
				clipped_prev_y = 0;
			else if (prev_y >= WINDOW_HEIGHT)
				clipped_prev_y = WINDOW_HEIGHT - 1;

			if (y < 0)
				clipped_y = 0;
			else if (y >= WINDOW_HEIGHT)
				clipped_y = WINDOW_HEIGHT - 1;

			if ((prev_y >= 0 && prev_y < WINDOW_HEIGHT) || (y >= 0 && y < WINDOW_HEIGHT))
			{
				int step_y = (clipped_y > clipped_prev_y) ? 1 : -1;
				for (int curr_y = clipped_prev_y; curr_y != clipped_y + step_y; curr_y += step_y)
				{
					if (curr_y >= 0 && curr_y < WINDOW_HEIGHT)
					{
						int pixel_index = (curr_y * drawer->img.line_length) + (prev_dx * (drawer->img.bpp / 8));
						*(unsigned int *)(drawer->img.addr + pixel_index) = 0xFF0000;
					}
				}
			}
		}
		prev_y = y;
	}
}

int main(int ac, char **av)
{
	t_data drawer;

	if (ac != 2)
		error_message("Wrong number of arguments. \
			\nUsage: ./draw <function>",
					  NULL);

	init_struct(&drawer);
	drawer.function = av[1];
	create_window(&drawer);
	mlx_loop_hook(drawer.mlx, loop_hook, &drawer);
	mlx_hook(drawer.win, 2, 1L << 0, handle_key_press, &drawer);
	mlx_hook(drawer.win, 3, 1L << 1, handle_key_released, &drawer);
	mlx_hook(drawer.win, 17, 1L << 17, on_destroy, &drawer);
	mlx_loop(drawer.mlx);

	return (0);
}
