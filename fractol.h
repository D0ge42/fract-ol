# ifndef FRACTOL_H
#define FRACTOL_H


#define MAX_ITERATIONS 1000
#define WHEEL_UP 4
#define WHEEL_DOWN 5
#define WIDTH 400
#define HEIGHT 400
typedef struct s_mlx_data
{
    //Window pointer, mlx pointer and zoom.
    void *mlx_ptr;
    void *win_ptr;
    double zoom;
    double offset_x;
    double offset_y;

    double min_re;
    double max_re;
    double max_im;
    double min_im;

    //Image variables.
    void *img;
    char *img_addr;
    int bits_per_pixel;
    int line_lenght;
    int endian;

    //Complex number x and y.
    double cx;
    double cy;

    //Complex number z.
    double zx;
    double zy;
    double z;
}   f_data;


void my_mlx_pixel_put(f_data *data, int x, int y, int color);
void cycle_and_apply(f_data *data);
int is_diverge(f_data *data, int x, int y);
double map(double unscaled_num, double new_min, double new_max, double old_min, double old_max);

#endif