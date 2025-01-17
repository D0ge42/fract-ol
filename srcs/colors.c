/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:49:28 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/16 17:49:30 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_gradient_color(double t, unsigned int start_color,
		unsigned int end_color)
{
	unsigned char	start[3];
	unsigned char	end[3];
	unsigned char	final[3];

	start[0] = (start_color >> 16) & 0xFF;
	start[1] = (start_color >> 8) & 0xFF;
	start[2] = start_color & 0xFF;
	end[0] = (end_color >> 16) & 0xFF;
	end[1] = (end_color >> 8) & 0xFF;
	end[2] = end_color & 0xFF;
	final[0] = (unsigned char)(start[0] + (end[0] - start[0]) * t);
	final[1] = (unsigned char)(start[1] + (end[1] - start[1]) * t);
	final[2] = (unsigned char)(start[2] + (end[2] - start[2]) * t);
	return ((final[0] << 16) | (final[1] << 8) | final[2]);
}

static void	initialize_inf_colors(unsigned int inf_colors[15])
{
	inf_colors[0] = 0xFFFFFF00;
	inf_colors[1] = 0xFF00FF00;
	inf_colors[2] = 0x00FFFF00;
	inf_colors[3] = 0x00FFCCFF;
	inf_colors[4] = 0x00FF6600;
	inf_colors[5] = 0x00FF3399;
	inf_colors[6] = 0x00FF3333;
	inf_colors[7] = 0xFFFF0033;
	inf_colors[8] = 0xFFFF00FF;
	inf_colors[9] = 0xFF6600FF;
	inf_colors[10] = 0xFF0033CC;
	inf_colors[11] = 0xFFFF0000;
	inf_colors[12] = 0xFF3399FF;
	inf_colors[13] = 0xFF6600FF;
	inf_colors[14] = 0x00000000;
}

static void	initialize_fin_colors(unsigned int fin_colors[15])
{
	fin_colors[0] = 0x00000000;
	fin_colors[1] = 0x00121212;
	fin_colors[2] = 0x00171717;
	fin_colors[3] = 0x001C1C1C;
	fin_colors[4] = 0x00212121;
	fin_colors[5] = 0x00262626;
	fin_colors[6] = 0x002B2B2B;
	fin_colors[7] = 0x00303030;
	fin_colors[8] = 0x00353535;
	fin_colors[9] = 0x003A3A3A;
	fin_colors[10] = 0x003F3F3F;
	fin_colors[11] = 0x00444444;
	fin_colors[12] = 0x00494949;
	fin_colors[13] = 0x004E4E4E;
	fin_colors[14] = 0x00525252;
}

void	cycle_colors(t_data *data)
{
	static int		i;
	unsigned int	inf_colors[15];
	unsigned int	fin_colors[15];

	initialize_fin_colors(inf_colors);
	initialize_inf_colors(fin_colors);
	if (i == 15)
		i = 0;
	i += 1;
	data->inf_color = inf_colors[i];
	data->fin_color = fin_colors[i];
}

int	get_color(double *t, t_data *data, int *depth)
{
	int	color;

	color = 0;
	if (*depth != MAX_ITERATIONS)
	{
		*t = (double)*depth / MAX_ITERATIONS;
		*t = pow(*t, 0.3);
		color = get_gradient_color(*t, data->inf_color, data->fin_color);
	}
	else
	{
		*t = (double)*depth / MAX_ITERATIONS;
		*t = pow(*t, 0.5);
		color = get_gradient_color(*t, data->fin_color, 0x00000000);
	}
	return (color);
}
