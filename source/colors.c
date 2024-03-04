/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:19:30 by lodemetz          #+#    #+#             */
/*   Updated: 2024/01/26 15:19:58 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	interpolate_color(unsigned int col0, unsigned int col1, \
														int step, int range)
{
	int		r;
	int		g;
	int		b;
	int		a;
	double	ratio;

	if (range == 0)
		ratio = 0;
	else
		ratio = (double)step / range;
	r = ((col0 >> 24) & 0xFF) * (1 - ratio) + ((col1 >> 24) & 0xFF) * ratio;
	g = ((col0 >> 16) & 0xFF) * (1 - ratio) + ((col1 >> 16) & 0xFF) * ratio;
	b = ((col0 >> 8) & 0xFF) * (1 - ratio) + ((col1 >> 8) & 0xFF) * ratio;
	a = (col0 & 0xFF) * (1 - ratio) + (col1 & 0xFF) * ratio;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

int	color_defined(unsigned int *colors, int total_points)
{
	int	i;

	i = 0;
	while (i < total_points)
	{
		if (colors[i])
			return (1);
		i++;
	}
	return (0);
}

void	calc_colors(t_map *map, t_points *pts, unsigned int *colors, \
															int total_points)
{
	int	i;
	int	z_min;
	int	z_range;
	int	step;

	z_min = map->z_min;
	z_range = map->z_range;
	i = 0;
	while (i < total_points)
	{
		step = pts->z[i] - z_min;
		colors[i] = interpolate_color(0x4cffc6, 0xC64B8CFF, step, z_range);
		i++;
	}
}

void	fill_default(unsigned int *colors, int total_points)
{
	int	i;

	i = 0;
	while (i < total_points)
	{
		if (colors[i] == 0)
			colors[i] = 0xA3A3A3FF;
		i++;
	}
}

int	init_colors(t_map *map, t_points *pts, int total_points)
{
	if (!color_defined(map->colors, total_points))
		calc_colors(map, pts, map->colors, total_points);
	else
		fill_default(map->colors, total_points);
	return (1);
}
