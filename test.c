#include "/home/doge/fractolup/libft/libft.h"
#include "/home/doge/fractolup/mlx/mlx.h"
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
	data->zoom = 150.0;
	if(data->fractal_type == BURNINGSHIPS)
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
	mlx_destroy_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_lenght, &data->endian);
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
	// Destroy the previous image and create a new one with the updated zoom and offsets
	mlx_destroy_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_lenght, &data->endian);
	// Redraw the fractal with the updated zoom and offsets
	draw_fractal(data, data->fractal_type);
	return (0);
}

void	cycle_colors(f_data *data)
{
	static int	i = 0;

	if (i == 15)
		i = 0;
	i += 1;
	unsigned int fin_colors[] = {
		0x00291F1F, // Dark charcoal
		0x00614BC4, // Deep purple
		0x003498DB, // Bright blue
		0x002980B9, // Ocean blue
		0x0016A085, // Teal
		0x001ABC9C, // Turquoise
		0x002ECC71, // Emerald
		0x0027AE60, // Forest green
		0x00F1C40F, // Sunflower yellow
		0x00E67E22, // Carrot orange
		0x00D35400, // Pumpkin
		0x00C0392B, // Pomegranate
		0x009B59B6, // Amethyst
		0x008E44AD, // Wisteria
		0x002C3E50  // Midnight blue
	};
	// Colors for interior points (infinite iterations)
	unsigned int inf_colors[] = {
		0x00000000, // Pure black
		0x00121212, // Nearly black
		0x00171717, // Very dark gray
		0x001C1C1C, // Dark charcoal
		0x00212121, // Charcoal
		0x00262626, // Dark slate
		0x002B2B2B, // Deep gray
		0x00303030, // Slate gray
		0x00353535, // Medium dark gray
		0x003A3A3A, // Granite
		0x003F3F3F, // Steel gray
		0x00444444, // Storm gray
		0x00494949, // Gray
		0x004E4E4E  // Medium gray
	};
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
		cycle_and_apply(data,BURNINGSHIPS);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

int	handle_input(int keycode, f_data *data)
{
	if (keycode == XK_Escape)
		destroy_event(data);
	if (keycode == XK_a)
	{
		cycle_colors(data);
		mlx_destroy_image(data->mlx_ptr, data->img);
		data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
		data->img_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
				&data->line_lenght, &data->endian);
		draw_fractal(data, data->fractal_type);
	}
	return (0);
}

int	check_fractal(char *av)
{
	char	fractals[3][20] = {"Mandelbrot", "Julia", "Burning Ships"};

	// Check mandelbrot
	if (!ft_strncmp(av, fractals[0], ft_strlen(av)))
		return (MANDELBROT); // Draw Fractal function has to be called here
	// Check Julia
	if (!ft_strncmp(av, fractals[1], ft_strlen(av)))
		return (JULIA);
	// Check burningships
	if (!ft_strncmp(av, fractals[2], ft_strlen(av)))
		return (BURNINGSHIPS);
	return (0);
}

void	init_julia(f_data *data)
{
	data->zoom = 200.0;
	data->offset_x = 0.0;
	data->offset_y = 0.0;
	data->zx = 0.0;
	data->zy = 0.0;
}

int	main(int ac, char **av)
{
	f_data	data;

	if (ac < 0)
		return (0);
	data.fractal_type = check_fractal(av[1]);
	if (data.fractal_type == MANDELBROT || data.fractal_type == BURNINGSHIPS)
		clean_init(&data);
	else if (data.fractal_type == JULIA)
	{
		init_julia(&data);
		if (av[2] && av[3])
		{
			data.cx = ft_atof(av[2]);
			data.cy = ft_atof(av[3]);
		}
		else
		{
			data.cx = -0.79;
			data.cy = 0.15;
		}
	}
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	// Create window
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "FRACTOL");
	// Img creation
	data.img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	data.img_addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_lenght, &data.endian);
	draw_fractal(&data, data.fractal_type);
	// Hooks
	if (data.fractal_type == MANDELBROT || data.fractal_type == BURNINGSHIPS)
		mlx_mouse_hook(data.win_ptr, mouse_hook_event, &data);
	else if (data.fractal_type == JULIA)
		mlx_mouse_hook(data.win_ptr, mouse_zoom_julia, &data);
	mlx_key_hook(data.win_ptr, handle_input, &data);
	mlx_hook(data.win_ptr, 17, 0, destroy_event, &data);
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