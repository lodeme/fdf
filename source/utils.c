/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:54:50 by lodemetz          #+#    #+#             */
/*   Updated: 2024/01/26 15:20:17 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_points(t_points *pts)
{
	if (pts->x)
		free(pts->x);
	if (pts->y)
		free(pts->y);
	if (pts->z)
		free(pts->z);
	free(pts);
}

void	free_env(t_env *env)
{
	int	i;

	i = 0;
	if (env)
	{
		if (env->user_view)
			free(env->user_view);
		if (env->map->colors)
			free(env->map->colors);
		if (env->map)
		{
			if (env->map->model_pts)
				free_points(env->map->model_pts);
			if (env->map->view_pts)
				free_points(env->map->view_pts);
			free(env->map);
		}
		if (env->img && env->window)
			mlx_delete_image(env->window, env->img);
		if (env->window)
			mlx_terminate(env->window);
		free(env);
	}
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	calc_max_pixels(t_map *map)
{
	if (HEIGHT > WIDTH)
		map->pixels_max = WIDTH;
	else
		map->pixels_max = HEIGHT;
}
