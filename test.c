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

void	init_struct(f_data *data)
{
	data->zoom = 1.0;
	data->offset_x = 0.0;
	data->offset_y = 0.0;
	data->fractal_type = 0;
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
    //Destroy previous fractal, generate new one
     mlx_destroy_image(data->mlx_ptr,data->img);
        data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	    data->img_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_lenght, &data->endian);
	draw_fractal(data, data->fractal_type);
	return (0);
}

void	cycle_colors(f_data *data)
{
	static int	i = 0;
    if (i == 13)
    i = 0;

	i+=1;
     unsigned int fin_colors[] = {
        0x00FF0000, 0x0000FF00, 0x000000FF, 0x00FFFF00,
        0x0000FFFF, 0x00FF00FF, 0x00800000, 0x00808000,
        0x00008000, 0x00800080, 0x00008080, 0x00000080, 
        0x00A52A2A, 0x00D3D3D3
    };
    
    unsigned int inf_colors[] = {
        0x006bb31b, 0x009dc0fc, 0x000af38e, 0x0027d189,
        0x00e7bf33, 0x00774f0d, 0x00b9cc9d, 0x0076f4b8,
        0x000a4b95, 0x0037ad0d, 0x00b313c9, 0x00634bb1,
        0x0061a110, 0x005e6cd3
    };
	data->inf_color = inf_colors[i];
	data->fin_color = fin_colors[i];
}

void	draw_fractal(f_data *data, int fractal_type)
{
	if (fractal_type == MANDELBROT)
		cycle_and_apply(data, MANDELBROT);
	if (fractal_type == JULIA)
		cycle_and_apply(data,JULIA);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

int	handle_input(int keycode, f_data *data)
{
	if (keycode == XK_Escape)
		destroy_event(data);
	if (keycode == XK_a)
    {
		cycle_colors(data);
        mlx_destroy_image(data->mlx_ptr,data->img);
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

int	main(int ac, char **av)
{
	f_data	data;

	if (ac != 2)
		return (0);
	init_struct(&data);
	// Initialize the connection to the X server
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	// Check and assign fractal type
	data.fractal_type = check_fractal(av[1]);
	// Create window
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "FRACTOL");
	// Img creation
	data.img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	mlx_mouse_hook(data.win_ptr, mouse_hook_event, &data);
	// Clean exit
	mlx_key_hook(data.win_ptr, handle_input, &data);
	// To keep the window alive we've t use mix_loop.
	mlx_loop(data.mlx_ptr);
	return (0);
}
