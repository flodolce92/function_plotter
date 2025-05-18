#include "func_drawer.h"

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

void draw_function(char **functions, t_data *drawer)
{
	double mx_math;
	double my_math_result;
	int sx_pixel, sy_pixel;
	int prev_sx_pixel, prev_sy_pixel;
	int i;
	int colors[] = {0xFF0000, 0x00FF00, 0x0000FF, 0xFF00FF, 0xFFFF00, 0x00FFFF};

	create_plane(drawer);

	i = 0;
	while (functions[i])
	{
		prev_sx_pixel = -1;
		prev_sy_pixel = -1;

		for (sx_pixel = 0; sx_pixel < WINDOW_WIDTH; sx_pixel++)
		{
			mx_math = drawer->center_math_x + (sx_pixel - WINDOW_WIDTH / 2.0) / drawer->zoom;
			my_math_result = evaluate_expression(functions[i], mx_math);

			// Check for NaN or Inf to prevent issues with drawing
			if (isnan(my_math_result) || isinf(my_math_result) || my_math_result > 1e4 || my_math_result < -1e4)
			{
				// Discontinue drawing if the result is out of bounds
				prev_sx_pixel = -1;
				prev_sy_pixel = -1;
				continue;
			}

			sy_pixel = (int)(WINDOW_HEIGHT / 2.0 - (my_math_result - drawer->center_math_y) * drawer->zoom);

			if (prev_sx_pixel != -1)
			{
				// Draw line from (prev_sx_pixel, prev_sy_pixel) to (sx_pixel, sy_pixel)
				draw_line_bresenham(drawer, prev_sx_pixel, prev_sy_pixel, sx_pixel, sy_pixel, colors[i % 6]); // Cycle through colors
			}
			prev_sx_pixel = sx_pixel;
			prev_sy_pixel = sy_pixel;
		}
		i++;
	}
}
