/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:49:11 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/16 17:49:13 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "/nfs/homes/lonulli/Fractol/libft/libft.h"
# include "/nfs/homes/lonulli/Fractol/mlx/mlx.h"
# include <X11/keysym.h>
# include <limits.h>
# include <math.h>

# define MAX_ITERATIONS 1000
# define WHEEL_UP 4
# define WHEEL_DOWN 5
# define WIDTH 400
# define HEIGHT 400
# define MANDELBROT 1
# define JULIA 2
# define BURNINGSHIPS 3
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_mlx_data
{
	// Window pointer, mlx pointer and zoom.
	void			*mlx_ptr;
	void			*win_ptr;
	double			zoom;
	double			offset_x;
	double			offset_y;

	// Fractal type
	int				fractal_type;
	unsigned int	inf_color;
	unsigned int	fin_color;

	// Image variables.
	void			*img;
	char			*img_addr;
	int				bits_per_pixel;
	int				line_lenght;
	int				endian;

	// Complex number x and y.
	double			cx;
	double			cy;

	// Complex number z.
	double			zx;
	double			zy;
}					t_data;

void				my_mlx_pixel_put(t_data *data, int x, int y,
						unsigned int color);
void				cycle_and_apply(t_data *data);
int					apply_mandelbrot(t_data *data, int x, int y);
int					apply_julia(t_data *data, int x, int y);
double				ft_atof(const char *str);
void				help_menu(void);
int					get_gradient_color(double t, unsigned int start_color,
						unsigned int end_color);
void				hooks(t_data *data);
int					destroy_event(t_data *data);

int					mouse_hook_event(int key, int x, int y, t_data *data);
int					mouse_zoom_julia(int key, int x, int y, t_data *data);
int					move_camera(t_data *data, int keycode);

int					get_gradient_color(double t, unsigned int start_color,
						unsigned int end_color);
void				cycle_colors(t_data *data);
int					get_color(double *t, t_data *data, int *depth);
int					fract_initializer(t_data *data, char **av);
int					apply_fractal(int depth, int x, int y, t_data *data);
int					check_fractal(char **av, int ac);
void				draw_fractal(t_data *data);
int					handle_input(int keycode, t_data *data);

#endif
