/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:47:03 by lodemetz          #+#    #+#             */
/*   Updated: 2024/01/26 15:20:17 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_series(double *series, int total_points, double value)
{
	int	i;

	i = 0;
	while (i < total_points)
		series[i++] += value;
}

void	make_pts_positive(t_points *pts, int total_points)
{
	int		i;
	double	min;

	i = 0;
	min = find_min(pts->x, total_points);
	if (min < 0)
		update_series(pts->x, total_points, fabs(min));
	min = find_min(pts->y, total_points);
	if (min < 0)
		update_series(pts->y, total_points, fabs(min));
	min = find_min(pts->z, total_points);
	if (min < 0)
		update_series(pts->z, total_points, fabs(min));
}

int	plot_right_and_down(t_env *env, int x, int y, int i)
{
	if (x < env->map->x_len - 1)
	{
		if (!plot_line(env->img, env->map, i, i + 1))
			return (0);
	}
	if (y < env->map->y_len - 1)
	{
		if (!plot_line(env->img, env->map, i, i + env->map->x_len))
			return (0);
	}
	return (1);
}

int	plot_points(t_env *env)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	y = 0;
	while (y < env->map->y_len)
	{
		x = 0;
		while (x < env->map->x_len)
		{
			if (!plot_right_and_down(env, x, y, i))
				return (0);
			x++;
			i++;
		}
		y++;
	}
	return (1);
}

int	plot_map(t_env *env)
{
	t_map	*map;

	map = env->map;
	copy_points(map->model_pts, map->view_pts, map->total_points);
	apply_rotation(map->view_pts, env->user_view, map->total_points);
	make_pts_positive(map->view_pts, map->total_points);
	scale_pts(env->user_view, map->view_pts, map->total_points, \
															map->pixels_max);
	apply_zoom(env->map->view_pts, env->user_view, env->map->total_points);
	apply_translations(env->map->view_pts, env->user_view, \
													env->map->total_points);
	ft_memset(env->img->pixels, 0, env->img->width * \
										env->img->height * sizeof(int32_t));
	return (plot_points(env));
}
