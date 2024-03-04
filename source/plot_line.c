/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:09:26 by lodemetz          #+#    #+#             */
/*   Updated: 2024/01/26 15:52:49 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_line	*init_line(unsigned int *colors, t_points *pts, int i0, int i1)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	if (!line)
		return (0);
	line->x0 = (int)round(pts->x[i0]);
	line->y0 = (int)round(pts->y[i0]);
	line->x1 = (int)round(pts->x[i1]);
	line->y1 = (int)round(pts->y[i1]);
	line->col0 = colors[i0];
	line->col1 = colors[i1];
	return (line);
}

void	init_bresenham(t_line *line)
{
	line->dx = abs(line->x1 - line->x0);
	if (line->x0 < line->x1)
		line->sx = 1;
	else
		line->sx = -1;
	line->dy = -abs(line->y1 - line->y0);
	if (line->y0 < line->y1)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx + line->dy;
	if (abs(line->dx) > abs(line->dy))
		line->step = abs(line->dx);
	else
		line->step = abs(line->dy);
}

int	point_is_in_frame(mlx_image_t *img, int x, int y)
{
	if ((x > 0 && x < (int)img->width) && (y > 0 && y < (int)img->height))
		return (1);
	return (0);
}

void	plot_bresenham_line(t_line *line, mlx_image_t *img)
{
	int				i;
	unsigned int	color;

	i = 0;
	while (1)
	{
		color = interpolate_color(line->col0, line->col1, i++, line->step);
		if (point_is_in_frame(img, line->x0, line->y0))
			put_pixel(img, line->x0, line->y0, color);
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
		line->e2 = 2 * line->err;
		if (line->e2 >= line->dy)
		{
			line->err += line->dy;
			line->x0 += line->sx;
		}
		if (line->e2 <= line->dx)
		{
			line->err += line->dx;
			line->y0 += line->sy;
		}
	}
}

int	plot_line(mlx_image_t *img, t_map *map, int i0, int i1)
{
	t_line	*line;

	line = init_line(map->colors, map->view_pts, i0, i1);
	if (!line)
		return (0);
	init_bresenham(line);
	plot_bresenham_line(line, img);
	free(line);
	return (1);
}
