/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:01:33 by lodemetz          #+#    #+#             */
/*   Updated: 2024/01/26 15:37:22 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	find_min(double *series, int total_points)
{
	int		i;
	double	min;

	i = 0;
	min = series[0];
	while (i < total_points)
	{
		if (series[i] < min)
			min = series[i];
		i++;
	}
	return (min);
}

double	find_max(double *series, int total_points)
{
	int		i;
	double	max;

	i = 0;
	max = series[0];
	while (i < total_points)
	{
		if (series[i] > max)
			max = series[i];
		i++;
	}
	return (max);
}

void	scale_pts(t_view *user_view, t_points *pts, int total_points, \
																int pixels_max)
{
	double	x_max;
	double	y_max;
	double	big_max;

	if (!user_view->scale)
	{
		x_max = find_max(pts->x, total_points);
		y_max = find_max(pts->y, total_points);
		if (x_max < y_max)
			big_max = y_max;
		else
			big_max = x_max;
		user_view->scale = pixels_max / big_max;
	}
	zoom_pts(pts, user_view->scale, total_points);
}

void	zoom_pts(t_points *pts, double factor, int total_points)
{
	int		i;

	i = 0;
	while (i < total_points)
	{
		pts->x[i] = pts->x[i] * factor;
		pts->y[i] = pts->y[i] * factor;
		i++;
	}
}
