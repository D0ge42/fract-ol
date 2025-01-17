/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:50:10 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/16 17:50:11 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	handle_input(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		destroy_event(data);
	if (keycode == XK_a)
	{
		cycle_colors(data);
		draw_fractal(data);
	}
	if (keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_LEFT
		|| keycode == KEY_RIGHT)
	{
		move_camera(data, keycode);
		draw_fractal(data);
	}
	return (0);
}

int	check_fractal(char **av, int ac)
{
	char	*fractals[3];

	fractals[0] = "Mandelbrot";
	fractals[1] = "Julia";
	fractals[2] = "Burning Ships";
	if (av[1] && av[2])
	{
		if ((!ft_strncmp(av[1], "Burning", 9999999) && !ft_strncmp(av[2],
					"Ships", 9999999)))
			return (BURNINGSHIPS);
	}
	if (!ft_strncmp(av[1], fractals[0], 9999999))
		return (MANDELBROT);
	if (!ft_strncmp(av[1], fractals[1], 9999999))
		return (JULIA);
	if (!ft_strncmp(av[1], fractals[2], 9999999))
	{
		if (ac == 3)
			return (0);
		return (BURNINGSHIPS);
	}
	return (0);
}

int	create_img(t_data *data)
{
	if (!data->mlx_ptr)
		return (0);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "FRACTOL");
	if (!data->win_ptr)
		return (0);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img)
		return (0);
	data->img_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_lenght, &data->endian);
	return (1);
}

void	cycle_and_apply(t_data *data)
{
	int		x;
	int		y;
	int		depth;
	double	t;

	x = 0;
	y = 0;
	depth = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			depth = apply_fractal(depth, x, y, data);
			if (depth != MAX_ITERATIONS)
				my_mlx_pixel_put(data, x, y, get_color(&t, data, &depth));
			else
				my_mlx_pixel_put(data, x, y, get_color(&t, data, &depth));
			x++;
		}
		x = 0;
		y++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 1 || ac > 4 || !check_fractal(av, ac))
	{
		help_menu();
		return (1);
	}
	data.fractal_type = check_fractal(av, ac);
	if ((data.fractal_type == MANDELBROT && ac > 2)
		|| ((data.fractal_type == BURNINGSHIPS && ac > 3)))
	{
		help_menu();
		return (0);
	}
	if (!fract_initializer(&data, av))
		return (0);
	data.mlx_ptr = mlx_init();
	if (!create_img(&data))
		return (0);
	draw_fractal(&data);
	hooks(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
// Cool julia coordinates to test out
// cx = -0.7, cy = 0.27015
// cx = 0.285, cy = 0.01
// cx = 0.355, cy = 0.355
// cx = -0.70176, cy = -0.3842 Dragon set
// cx = 0.37, cy = 0.1
// cx = -0.8, cy = 0.156
