#include "/nfs/homes/lonulli/Fractol/libft/libft.h"
#include "/nfs/homes/lonulli/Fractol/mlx/mlx.h"
#include "fractol.h"
#include <X11/keysym.h>
#include <limits.h>

void	draw_fractal(f_data *data, int fractal_type);

int	destroy_event(f_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}

void	clean_init(f_data *data)
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

int	mouse_hook_event(int key, int x, int y, f_data *data)
{
	double	prev_cx;
	double	prev_cy;

	prev_cx = (x - WIDTH / 2.0) / data->zoom + data->offset_x;
	prev_cy = (y - HEIGHT / 2.0) / data->zoom + data->offset_y;
	if (key == WHEEL_UP)
		data->zoom *= 1.35; // Zoom in
	else if (key == WHEEL_DOWN)
		data->zoom /= 1.35; // Zoom out
	data->cx = (x - WIDTH / 2.0) / data->zoom + data->offset_x;
	data->cy = (y - HEIGHT / 2.0) / data->zoom + data->offset_y;
	// Adjust offsets to center the zoom on the mouse position
	data->offset_x += prev_cx - data->cx;
	data->offset_y += prev_cy - data->cy;
	// Destroy previous fractal, generate new one
	draw_fractal(data, data->fractal_type);
	return (0);
}

int	mouse_zoom_julia(int key, int x, int y, f_data *data)
{
	double	prev_cx;
	double	prev_cy;

	// Calculate the current values of cx, cy before the zoom
	prev_cx = (x - WIDTH / 2.0) / data->zoom + data->offset_x;
	prev_cy = (y - HEIGHT / 2.0) / data->zoom + data->offset_y;
	// Zoom logic
	if (key == WHEEL_UP)
		data->zoom *= 1.35; // Zoom in
	else if (key == WHEEL_DOWN)
		data->zoom /= 1.35; // Zoom out
	// Recalculate the offsets based on the new zoom level
	data->offset_x = prev_cx - (x - WIDTH / 2.0) / data->zoom;
	data->offset_y = prev_cy - (y - HEIGHT / 2.0) / data->zoom;
	// Redraw the fractal with the updated zoom and offsets
	draw_fractal(data, data->fractal_type);
	return (0);
}

void	cycle_colors(f_data *data)
{
	static int		i = 0;
	unsigned int	fin_colors[] = {0xFFFFFF00, 0xFF00FF00, 0x00FFFF00,
			0x00FFCCFF, 0x00FF6600, 0x00FF3399, 0x00FF3333, 0xFFFF0033,
			0xFFFF00FF, 0xFF6600FF, 0xFF0033CC, 0xFFFF0000, 0xFF3399FF,
			0xFF6600FF, 0x00000000};
	unsigned int	inf_colors[] = {0x00000000, 0x00121212, 0x00171717,
			0x001C1C1C, 0x00212121, 0x00262626, 0x002B2B2B, 0x00303030,
			0x00353535, 0x003A3A3A, 0x003F3F3F, 0x00444444, 0x00494949,
			0x004E4E4E, 0x00525252};

	if (i == 15)
		i = 0;
	i += 1;
	data->inf_color = inf_colors[i];
	data->fin_color = fin_colors[i];
}

void	draw_fractal(f_data *data, int fractal_type)
{
	if (fractal_type == MANDELBROT)
		cycle_and_apply(data, MANDELBROT);
	if (fractal_type == JULIA)
		cycle_and_apply(data, JULIA);
	if (fractal_type == BURNINGSHIPS)
		cycle_and_apply(data, BURNINGSHIPS);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

int	move_camera(f_data *data, int keycode)
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

int	handle_input(int keycode, f_data *data)
{
	if (keycode == XK_Escape)
		destroy_event(data);
	if (keycode == XK_a)
	{
		cycle_colors(data);
		draw_fractal(data, data->fractal_type);
	}
	if (keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_LEFT
		|| keycode == KEY_RIGHT)
	{
		move_camera(data, keycode);
		draw_fractal(data, data->fractal_type);
	}
	return (0);
}

int	check_fractal(char **av)
{
	char	fractals[3][20] = {"Mandelbrot", "Julia", "Burning Ships"};

	if(av[1] && av[2])
	{
		if ((!ft_strncmp(av[1],"Burning", 999999) && !ft_strncmp(av[2],"Ships",99999)))
			return (BURNINGSHIPS);
	}
	// Check mandelbrot
	if (!ft_strncmp(av[1], fractals[0], 999999))
		return (MANDELBROT); // Draw Fractal function has to be called here
	// Check Julia
	if (!ft_strncmp(av[1], fractals[1], 999999))
		return (JULIA);
	// Check burningships
	if (!ft_strncmp(av[1], fractals[2], 999999))
		return (BURNINGSHIPS);
	return (0);
}

void	init_julia(f_data *data, char *x, char *y)
{
	if (x && y)
	{
		data->cx = ft_atof(x);
		data->cy = ft_atof(y);
		if (data->cx > 2.0 || data->cy > 2.0)
		{
			help_menu();
			return ;
		}
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

void	hooks(f_data *data)
{
	if (data->fractal_type == MANDELBROT || data->fractal_type == BURNINGSHIPS)
		mlx_mouse_hook(data->win_ptr, mouse_hook_event, data);
	else if (data->fractal_type == JULIA)
		mlx_mouse_hook(data->win_ptr, mouse_zoom_julia, data);
	mlx_key_hook(data->win_ptr, handle_input, data);
	mlx_hook(data->win_ptr, 17, 0, destroy_event, data);
}

int	create_img(f_data *data)
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

int	fract_initializer(f_data *data, char **av, int ac)
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
		if(ac == 3)
		{
			help_menu();
			return 0;
		}
		init_julia(data, av[2], av[3]);
	}
	return (1);
}

int	main(int ac, char **av)
{
	f_data	data;

	if (ac == 1 || ac > 4 || !check_fractal(av))
	{
		help_menu();
		return (1);
	}
	data.fractal_type = check_fractal(av);
	if (data.fractal_type == MANDELBROT && ac > 2)
	{
		help_menu();
		return (0);
	}
	if (data.fractal_type == BURNINGSHIPS && ac > 3)
	{
		help_menu();
		return 0;
	}
	if (!fract_initializer(&data, av,ac))
		return (1);
	data.mlx_ptr = mlx_init();
	if (!create_img(&data))
		return (0);
	draw_fractal(&data, data.fractal_type);
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