/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:15:58 by lodemetz          #+#    #+#             */
/*   Updated: 2024/01/30 16:39:48 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define M_PI 3.14159265358979323846
# define WIDTH 51
# define HEIGHT 51

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "MLX42/MLX42.h"
# include "get_next_line.h"
# include "libft.h"

typedef struct line_s
{
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	int				dx;
	int				sx;
	int				dy;
	int				sy;
	int				err;
	int				e;
	int				e2;
	int				step;
	unsigned int	col0;
	unsigned int	col1;
}	t_line;

typedef struct points_s
{
	double	*x;
	double	*y;
	double	*z;
}	t_points;

typedef struct map_s
{
	int				x_len;
	int				y_len;
	int				total_points;
	int				z_min;
	int				z_max;
	int				z_range;
	int				pixels_max;
	t_points		*model_pts;
	t_points		*view_pts;
	unsigned int	*colors;
}	t_map;

typedef struct view_s
{
	double	x_shift;
	double	y_shift;
	double	angle;
	double	zoom;
	double	scale;
}	t_view;

typedef struct env_s
{
	mlx_t		*window;
	mlx_image_t	*img;
	t_map		*map;
	t_view		*user_view;
}	t_env;

// main.c
void			throw_error(t_env *env);
int				main(int argc, char **argv);
void			hook(void *param);

// plot_line.c
t_line			*init_line(unsigned int *colors, t_points *pts, int i0, int i1);
void			init_bresenham(t_line *line);
void			plot_bresenham_line(t_line *line, mlx_image_t *img);
int				plot_line(mlx_image_t *img, t_map *map, int i0, int i1);
int				point_is_in_frame(mlx_image_t *img, int x, int y);

// load_map.c
void			process_metadata(char **color_split, t_points *pts, \
															t_map *map, int i);
void			process_line(char *nextline, t_map *map, t_points *pts, int y);
int				load_map(t_env *env, char *filename);
int				load_points(t_map *map, t_points *pts, int fd);
int				get_map_size(t_map *map, int fd);

// transform.c
void			update_series(double *series, int total_points, double value);
void			make_pts_positive(t_points *pts, int total_points);
int				plot_map(t_env *env);

// input.c
void			translate_x(t_env *env, double pixels);
void			translate_y(t_env *env, double pixels);
void			zoom(t_env *env, double factor);
void			rotate(t_env *env, double angle);

// apply.c
void			apply_translations(t_points *pts, t_view *user_view, \
															int total_points);
void			apply_zoom(t_points *pts, t_view *user_view, int total_points);
void			apply_rotation(t_points *pts, t_view *user_view, \
															int total_points);

// scale.c
double			find_min(double *series, int total_points);
double			find_max(double *series, int total_points);
void			scale_pts(t_view *user_view, t_points *pts, int total_points, \
															int pixels_max);
void			zoom_pts(t_points *pts, double factor, int total_points);

// plot_map.c
int				plot_right_and_down(t_env *env, int x, int y, int i);
int				plot_points(t_env *env);
int				plot_map(t_env *env);

// init.c
int				init_color_array(t_map *map);
int				init_map(t_env *env, char *filename);
t_points		*init_points(t_map *map);
t_env			*init_env(mlx_t *window, mlx_image_t *img);
int				init_user_view(t_env *env);

// colors.c
unsigned int	interpolate_color(unsigned int col0, unsigned int col1, \
														int step, int range);
int				color_defined(unsigned int *colors, int total_points);
void			calc_colors(t_map *map, t_points *pts, unsigned int *colors, \
															int total_points);
void			fill_default(unsigned int *colors, int total_points);
int				init_colors(t_map *map, t_points *pts, int total_points);

// utils.c
void			free_points(t_points *pts);
void			free_split(char **arr);
void			free_env(t_env *env);
void			calc_max_pixels(t_map *map);

// utils2.c
int				get_split_len(char **split);
void			put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, \
															uint32_t color);
void			copy_points(t_points *src, t_points *dst, int total_points);

// xtoi.c
int				find_xindex(char c);
unsigned int	ft_xtoi(const char *nptr);
#endif
