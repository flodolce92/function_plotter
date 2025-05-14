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

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

enum e_keys
{
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	ESC = 65307
};

typedef struct s_key_press
{
	bool	a;
	bool	d;
	bool	s;
	bool	w;
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
	t_image		img;
	t_key_press	keys;
}	t_data;

void	init_struct(t_data *drawer);
int		on_destroy(t_data *drawer);
int		handle_key_press(int keycode, t_data *drawer);
int		handle_key_released(int keycode, t_data *drawer);

#endif
