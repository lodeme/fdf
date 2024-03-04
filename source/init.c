/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:39:08 by lodemetz          #+#    #+#             */
/*   Updated: 2024/01/26 16:40:28 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_color_array(t_map *map)
{
	map->colors = (unsigned int *)malloc(sizeof(unsigned int) * \
															map->total_points);
	if (!map->colors)
		return (0);
	return (1);
}

int	init_map(t_env *env, char *filename)
{
	int	fd;

	env->map = (t_map *)malloc(sizeof(t_map));
	if (!env->map)
		return (0);
	env->map->model_pts = 0;
	env->map->view_pts = 0;
	env->map->colors = 0;
	env->map->z_min = INT_MAX;
	env->map->z_max = INT_MIN;
	calc_max_pixels(env->map);
	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		return (0);
	if (!get_map_size(env->map, fd))
		return (0);
	close(fd);
	return (init_color_array(env->map));
}

t_points	*init_points(t_map *map)
{
	t_points	*pts;
	int			i;

	i = 0;
	pts = (t_points *)malloc(sizeof(t_points));
	if (!pts)
		return (0);
	pts->x = (double *)malloc(sizeof(double) * map->total_points);
	pts->y = (double *)malloc(sizeof(double) * map->total_points);
	pts->z = (double *)malloc(sizeof(double) * map->total_points);
	if (!pts->x || !pts->y || !pts->z)
		return (0);
	return (pts);
}

int	init_user_view(t_env *env)
{
	env->user_view = (t_view *)malloc(sizeof(t_view));
	if (!env->user_view)
		return (0);
	env->user_view->x_shift = 0;
	env->user_view->y_shift = 0;
	env->user_view->angle = 0.463647;
	env->user_view->zoom = 0;
	env->user_view->scale = 0;
	return (1);
}

t_env	*init_env(mlx_t *window, mlx_image_t *img)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (0);
	env->window = window;
	env->img = img;
	if (!init_user_view(env))
		return (0);
	return (env);
}
