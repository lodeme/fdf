/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:04:22 by lodemetz          #+#    #+#             */
/*   Updated: 2024/01/26 15:20:17 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate_x(t_env *env, double pixels)
{
	env->user_view->x_shift += pixels;
	if (!plot_map(env))
		free_env(env);
}

void	translate_y(t_env *env, double pixels)
{
	env->user_view->y_shift += pixels;
	if (!plot_map(env))
		free_env(env);
}

void	zoom(t_env *env, double factor)
{
	env->user_view->zoom += factor;
	if (!plot_map(env))
		free_env(env);
}

void	rotate(t_env *env, double angle)
{
	if (env->user_view->angle + angle > 0 && \
		env->user_view->angle + angle < 0.8)
		env->user_view->angle += angle;
	if (!plot_map(env))
		free_env(env);
}
