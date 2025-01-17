/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:49:51 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/16 17:49:52 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_julia(t_data *data, char *x, char *y)
{
	if (x && y)
	{
		data->cx = ft_atof(x);
		data->cy = ft_atof(y);
	}
	else
	{
		data->cx = -0.79;
		data->cy = 0.15;
	}
	data->zoom = 200.0;
	data->offset_x = 0.0;
	data->offset_y = 0.0;
	data->zx = 0.0;
	data->zy = 0.0;
}

void	clean_init(t_data *data)
{
	data->zoom = 90.0;
	if (data->fractal_type == BURNINGSHIPS)
		data->zoom = 50.0;
	data->offset_x = 0.0;
	data->offset_y = 0.0;
	data->cx = 0.0;
	data->cy = 0.0;
	data->zx = 0.0;
	data->zy = 0.0;
}

int	fract_initializer(t_data *data, char **av)
{
	if (data->fractal_type == MANDELBROT || data->fractal_type == BURNINGSHIPS)
		clean_init(data);
	else if (data->fractal_type == JULIA)
	{
		if (av[2] && av[3])
		{
			if (!ft_strchr('.', av[2]) || !ft_strchr('.', av[3]))
			{
				help_menu();
				return (0);
			}
			if ((ft_atof(av[2]) > 2.0 || ft_atof(av[3]) > 2.0)
				|| (ft_atof(av[2]) < -2.0 || ft_atof(av[3]) < -2.0))
			{
				help_menu();
				return (0);
			}
		}
		init_julia(data, av[2], av[3]);
	}
	return (1);
}
