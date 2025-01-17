/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:50:17 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/16 17:50:18 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_data *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->img_addr + (y * img->line_lenght + x * (img->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	hooks(t_data *data)
{
	if (data->fractal_type == MANDELBROT || data->fractal_type == BURNINGSHIPS)
		mlx_mouse_hook(data->win_ptr, mouse_hook_event, data);
	else if (data->fractal_type == JULIA)
		mlx_mouse_hook(data->win_ptr, mouse_zoom_julia, data);
	mlx_key_hook(data->win_ptr, handle_input, data);
	mlx_hook(data->win_ptr, 17, 0, destroy_event, data);
}

int	destroy_event(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}
