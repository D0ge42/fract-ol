# ifndef FRACTOL_H
#define FRACTOL_H


#define MAX_ITERATIONS 600
#define WHEEL_UP 4
#define WHEEL_DOWN 5
#define WIDTH 400
#define HEIGHT 400
#define MANDELBROT 1
#define JULIA 2
#define BURNINGSHIPS 3

typedef struct s_mlx_data
{
    //Window pointer, mlx pointer and zoom.
    void *mlx_ptr;
    void *win_ptr;
    double zoom;
    double offset_x;
    double offset_y;

    //Fractal type
    int fractal_type;
    unsigned int inf_color;
    unsigned int fin_color;

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
}   f_data;


void my_mlx_pixel_put(f_data *data, int x, int y, unsigned int color);
void cycle_and_apply(f_data *data,int fractal_type);
int apply_mandelbrot(f_data *data, int x, int y);
int apply_julia(f_data *data, int x, int y);
double map(double unscaled_num, double new_min, double new_max, double old_min, double old_max);
double ft_atof(const char *str);
int get_gradient_color(double t, unsigned int start_color, unsigned int end_color);

#endif