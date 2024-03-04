/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:51:31 by lodemetz          #+#    #+#             */
/*   Updated: 2024/01/26 15:43:27 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_translations(t_points *pts, t_view *user_view, int total_points)
{
	int	i;

	i = 0;
	while (i < total_points)
	{
		pts->x[i] += user_view->x_shift;
		pts->y[i] += user_view->y_shift;
		i++;
	}
}

void	apply_zoom(t_points *pts, t_view *user_view, int total_points)
{
	zoom_pts(pts, pow(2, user_view->zoom), total_points);
}

void	apply_rotation(t_points *pts, t_view *user_view, int total_points)
{
	int	i;
	int	previous_x;
	int	previous_y;

	i = 0;
	while (i < total_points)
	{
		previous_x = pts->x[i];
		previous_y = pts->y[i];
		pts->x[i] = (previous_x - previous_y) * cos(user_view->angle);
		pts->y[i] = -pts->z[i] + (previous_x + previous_y) * \
													sin(user_view->angle);
		i++;
	}
}
