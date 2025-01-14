#include "fractol.h"
#include <X11/keysym.h>
#include <float.h>
#include <limits.h>
#include <math.h>

// double	map(double unscaled_num, double new_min, double new_max, double old_min,
// 		double old_max)
// {
// 	return ((new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min)
// 		+ new_min);
// }

void	my_mlx_pixel_put(f_data *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->img_addr + (y * img->line_lenght + x * (img->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

int	apply_mandelbrot(f_data *data, int x, int y)
{
	int		i;
	double	zx2;
	double	zy2;

	i = 0;
	data->zx = 0.0;
	data->zy = 0.0;
	zx2 = 0.0;
	zy2 = 0.0;
	data->cx = (x - WIDTH / 2.0) / data->zoom + data->offset_x;
	data->cy = (y - HEIGHT / 2.0) / data->zoom + data->offset_y;
	while (i <= MAX_ITERATIONS)
	{
		if ((zx2 * zx2) + (zy2 * zy2) > 4)
			return (i);
		zx2 = (data->zx * data->zx) - (data->zy * data->zy) + data->cx;
		zy2 = (2 * data->zx * data->zy) + data->cy;
		// Aggiorniamo z per la prossima iterazione
		data->zx = zx2;
		data->zy = zy2;
		i++;
	}
	return (MAX_ITERATIONS);
}

int	get_gradient_color(double t, unsigned int start_color,
		unsigned int end_color)
{
	unsigned char	r_start;
	unsigned char	g_start;
	unsigned char	b_start;
	unsigned char	r_end;
	unsigned char	g_end;
	unsigned char	b_end;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r_start = (start_color >> 16) & 0xFF;
	g_start = (start_color >> 8) & 0xFF;
	b_start = start_color & 0xFF;
	r_end = (end_color >> 16) & 0xFF;
	g_end = (end_color >> 8) & 0xFF;
	b_end = end_color & 0xFF;
	// Apply a smooth step function for better blending
	r = (unsigned char)(r_start + (r_end - r_start) * t);
	g = (unsigned char)(g_start + (g_end - g_start) * t);
	b = (unsigned char)(b_start + (b_end - b_start) * t);
	return ((r << 16) | (g << 8) | b);
}

int	apply_julia(f_data *data, int x, int y)
{
	int		i;
	double	tmp;

	i = 0;
	data->zx = (x - WIDTH / 2.0) / data->zoom + data->offset_x;
	data->zy = (y - HEIGHT / 2.0) / data->zoom + data->offset_y;
	while (i <= MAX_ITERATIONS)
	{
		if ((data->zx * data->zx) + (data->zy * data->zy) >= 4)
			return (i);
		tmp = data->zx;
		data->zx = data->zx * data->zx - data->zy * data->zy + data->cx;
		data->zy = 2 * data->zy * tmp + data->cy;
		i++;
	}
	return (MAX_ITERATIONS);
}

int	apply_burning_ship(f_data *fractal,int x, int y)
{
	int		i;
	double	x_temp;

	i = 0;
	fractal->zx = 0.0;
	fractal->zy = 0.0;
	fractal->cx = (x - WIDTH / 2.0) / fractal->zoom + fractal->offset_x;
	fractal->cy = (y - HEIGHT / 2.0) / fractal->zoom + fractal->offset_y;
	while (i <= MAX_ITERATIONS)
	{
		x_temp = fractal->zx * fractal->zx - fractal->zy * fractal->zy
			+ fractal->cx;
		if (fractal->zx * fractal->zx + fractal->zy * fractal->zy >= 4)
			return i;
		fractal->zy = fabs(2.0 * fractal->zx * fractal->zy) + fractal->cy;
		fractal->zx = fabs(x_temp);
		i++;
	}
	return MAX_ITERATIONS;
}

void	cycle_and_apply(f_data *data, int fractal_type)
{
	int	x;
	int	y;
	int	depth;
	int	color;

	x = 0;
	y = 0;
	depth = 0;
	double t; // Variable for smooth gradient transition
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			if (fractal_type == MANDELBROT)
				depth = apply_mandelbrot(data, x, y);
			else if (fractal_type == JULIA)
				depth = apply_julia(data, x, y);
			else if (fractal_type == BURNINGSHIPS)
				depth = apply_burning_ship(data,x,y);
			if (depth != MAX_ITERATIONS)
			{
				t = (double)depth / MAX_ITERATIONS;
				t = pow(t, 0.3);
				color = get_gradient_color(t, data->inf_color, data->fin_color);
				my_mlx_pixel_put(data, x, y, color);
			}
			else
			{
				t = (double)depth / (MAX_ITERATIONS);
				t = pow(t, 0.5);
				color = get_gradient_color(t, data->fin_color, 0x00000000);
				my_mlx_pixel_put(data, x, y, color);
			}
			x++;
		}
		x = 0;
		y++;
	}
}
