#include "/home/doge/fractolup/libft/libft.h"
#include "fractol.h"

double	ft_atof(const char *str)
{
	double result = 0.0;
	double decimal_place = 1.0;
	int sign = 1;

	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result *= 10 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			result += (*str - '0') * (decimal_place /= 10);
			str++;
		}
	}
	return (sign * result);
}