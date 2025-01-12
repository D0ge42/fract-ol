#include "/home/doge/fract-ol/mlx/mlx.h"
#include "/home/doge/fract-ol/libft/libft.h"
#include "fractol.h"
#include <X11/keysym.h>
#include <math.h>

int destroy_event(f_data *data)
{
    mlx_destroy_display(data->mlx_ptr);
    mlx_destroy_window(data->mlx_ptr,data->win_ptr);
    free(data->mlx_ptr);
    exit(0);
}

int mouse_hook_event(int key, int x, int y, f_data *data)
{
    double prev_cx = (x - WIDTH / 2.0) / data->zoom + data->offset_x;
    double prev_cy = (y - HEIGHT / 2.0) /data->zoom + data->offset_y;

    if (key == WHEEL_UP)
        data->zoom *= 1.1111; // Zoom in
    else if (key == WHEEL_DOWN)
        data->zoom /= 1.1111; // Zoom out

    double new_cx = (x - WIDTH / 2.0) / data->zoom + data->offset_x;
    double new_cy = (y - HEIGHT / 2.0) / data->zoom + data->offset_y;

    // Adjust offsets to center the zoom on the mouse position
    data->offset_x += prev_cx - new_cx;
    data->offset_y += prev_cy - new_cy;

    cycle_and_apply(data);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
    return 0;
}

int handle_input(int keycode, f_data *data)
{
    if (keycode == XK_Escape)
        destroy_event(data);
    return 0;
}



int main() 
{
    f_data data;
    data.zoom = 1.0;
    // Initialize the connection to the X server
    data.mlx_ptr = mlx_init();
    if(!data.mlx_ptr)
        return 1;

    // Create window
    data.win_ptr = mlx_new_window(data.mlx_ptr,WIDTH,HEIGHT,"FRACTOL");

    //Img creation
    data.img = mlx_new_image(data.mlx_ptr,WIDTH,HEIGHT);

    data.img_addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_lenght, &data.endian);


    mlx_mouse_hook(data.win_ptr,mouse_hook_event,&data);

    //Clean exit
    mlx_key_hook(data.win_ptr,handle_input,&data);
    
    // To keep the window alive we've t use mix_loop.
    mlx_loop(data.mlx_ptr);

    return 0;
}
