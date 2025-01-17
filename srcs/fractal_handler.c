/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:49:39 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/16 17:49:40 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_fractal(t_data *data)
{
	cycle_and_apply(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

int	apply_mandelbrot(t_data *data, int x, int y)
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
		data->zx = zx2;
		data->zy = zy2;
		i++;
	}
	return (MAX_ITERATIONS);
}

int	apply_julia(t_data *data, int x, int y)
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

int	apply_burning_ship(t_data *fractal, int x, int y)
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
			return (i);
		fractal->zy = fabs(2.0 * fractal->zx * fractal->zy) + fractal->cy;
		fractal->zx = fabs(x_temp);
		i++;
	}
	return (MAX_ITERATIONS);
}

int	apply_fractal(int depth, int x, int y, t_data *data)
{
	if (data->fractal_type == MANDELBROT)
		depth = apply_mandelbrot(data, x, y);
	else if (data->fractal_type == JULIA)
		depth = apply_julia(data, x, y);
	else if (data->fractal_type == BURNINGSHIPS)
		depth = apply_burning_ship(data, x, y);
	return (depth);
}
