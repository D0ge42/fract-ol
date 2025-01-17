/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:49:20 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/16 17:49:22 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_hook_event(int key, int x, int y, t_data *data)
{
	double	prev_cx;
	double	prev_cy;

	prev_cx = (x - WIDTH / 2.0) / data->zoom + data->offset_x;
	prev_cy = (y - HEIGHT / 2.0) / data->zoom + data->offset_y;
	if (key == WHEEL_UP)
		data->zoom *= 1.35;
	else if (key == WHEEL_DOWN)
		data->zoom /= 1.35;
	data->cx = (x - WIDTH / 2.0) / data->zoom + data->offset_x;
	data->cy = (y - HEIGHT / 2.0) / data->zoom + data->offset_y;
	data->offset_x += prev_cx - data->cx;
	data->offset_y += prev_cy - data->cy;
	draw_fractal(data);
	return (0);
}

int	mouse_zoom_julia(int key, int x, int y, t_data *data)
{
	double	prev_cx;
	double	prev_cy;

	prev_cx = (x - WIDTH / 2.0) / data->zoom + data->offset_x;
	prev_cy = (y - HEIGHT / 2.0) / data->zoom + data->offset_y;
	if (key == WHEEL_UP)
		data->zoom *= 1.35;
	else if (key == WHEEL_DOWN)
		data->zoom /= 1.35;
	data->offset_x = prev_cx - (x - WIDTH / 2.0) / data->zoom;
	data->offset_y = prev_cy - (y - HEIGHT / 2.0) / data->zoom;
	draw_fractal(data);
	return (0);
}

int	move_camera(t_data *data, int keycode)
{
	if (keycode == KEY_UP)
		data->offset_y -= 42 / data->zoom;
	if (keycode == KEY_DOWN)
		data->offset_y += 42 / data->zoom;
	if (keycode == KEY_LEFT)
		data->offset_x -= 42 / data->zoom;
	if (keycode == KEY_RIGHT)
		data->offset_x += 42 / data->zoom;
	return (0);
}
