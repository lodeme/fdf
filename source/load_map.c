/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:49:41 by lodemetz          #+#    #+#             */
/*   Updated: 2024/01/26 16:32:00 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_map_size(t_map *map, int fd)
{
	char	*nextline;
	char	**split_line;

	map->x_len = 0;
	map->y_len = 0;
	while (1)
	{
		nextline = get_next_line(fd);
		if (!nextline)
			break ;
		if (nextline[ft_strlen(nextline) - 1] == '\n')
			nextline[ft_strlen(nextline) - 1] = 0;
		if (!map->x_len)
		{
			split_line = ft_split(nextline, ' ');
			while (split_line[map->x_len])
				map->x_len++;
			free_split(split_line);
		}
		free(nextline);
		map->y_len++;
	}
	map->total_points = map->x_len * map->y_len;
	return (1);
}

void	process_metadata(char **color_split, t_points *pts, t_map *map, int i)
{
	if (get_split_len(color_split) > 1)
		map->colors[i] = ft_xtoi(color_split[1]);
	else
		map->colors[i] = 0;
	if (pts->z[i] > map->z_max)
		map->z_max = pts->z[i];
	if (pts->z[i] < map->z_min)
		map->z_min = pts->z[i];
}

void	process_line(char *nextline, t_map *map, t_points *pts, int y)
{
	char	**point_split;
	char	**color_split;
	int		x;
	int		i;

	i = y * map->x_len;
	x = 0;
	if (nextline[ft_strlen(nextline) - 1] == '\n')
		nextline[ft_strlen(nextline) - 1] = 0;
	point_split = ft_split(nextline, ' ');
	while (point_split[x])
	{
		color_split = ft_split(point_split[x], ',');
		pts->x[i] = x;
		pts->y[i] = y;
		pts->z[i] = ft_atoi(color_split[0]);
		process_metadata(color_split, pts, map, i);
		free_split(color_split);
		x++;
		i++;
	}
	free_split(point_split);
}

int	load_points(t_map *map, t_points *pts, int fd)
{
	char	*nextline;
	int		y;

	y = 0;
	while (y < map->y_len)
	{
		nextline = get_next_line(fd);
		if (!nextline)
			break ;
		process_line(nextline, map, pts, y);
		free(nextline);
		y++;
	}
	map->z_range = map->z_max - map->z_min;
	return (1);
}

int	load_map(t_env *env, char *filename)
{
	int		fd;

	if (!init_map(env, filename))
		return (0);
	env->map->model_pts = init_points(env->map);
	if (!env->map->model_pts)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		return (0);
	if (!load_points(env->map, env->map->model_pts, fd))
		return (0);
	close(fd);
	if (!init_colors(env->map, env->map->model_pts, env->map->total_points))
		return (0);
	env->map->view_pts = init_points(env->map);
	if (!env->map->view_pts)
		return (0);
	return (1);
}
