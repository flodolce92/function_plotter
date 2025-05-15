#ifndef FUNCTDRAWER_H
# define FUNCTDRAWER_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <math.h>

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 600

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
	bool	a;
	bool	d;
	bool	s;
	bool	w;
	bool	up;
	bool	down;
}	t_key_press;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			x_offset;
	int			y_offset;
	double		zoom;
	char		*function;
	t_image		img;
	t_key_press	keys;
}	t_data;

void	init_struct(t_data *drawer);
int		on_destroy(t_data *drawer);
int		handle_key_press(int keycode, t_data *drawer);
int		handle_key_released(int keycode, t_data *drawer);
int		loop_hook(t_data *drawer);
void	draw_function(char *function, t_data *drawer);

#endif
