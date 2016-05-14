/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 14:12:16 by mdugot            #+#    #+#             */
/*   Updated: 2016/02/17 15:36:51 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define UNIT_X -100.0
# define UNIT_Y -10.0
# define UNIT_Z 100.0
# define MAX 1000
# define DEPTH_SCREEN 100.0
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 800
# define DEPTH_MAP 200.0
# define EVENT_MOVE 10.0
# define EVENT_ROTATION 10.0
# define EVENT_DEPTH 10.0
# define EVENT_ZOOM 1.5
# define POINT map->point
# define MH (map->height - 1)
# define MW (map->width - 1)
# define COIN_A map->point[i][j].pixel
# define COIN_B map->point[i + 1][j].pixel
# define COIN_C map->point[i + 1][j + 1].pixel
# define COIN_D map->point[i][j + 1].pixel
# define PA triangle.point_a
# define PB triangle.point_b
# define PC triangle.point_c
# define CIT convert_in_triangle
# define CIP convert_in_pixel
# define CIS convert_in_segment
# define BLUE 0xFF
# define RED 0xFF0000
# define GREEN 0xFF00
# define MAGENTA 0xFF00FF
# define JAUNE 0xFFFF00
# define CYAN 0x00FFFF
# define BLACK 0x0
# define WHITE 0xFEFEFE
# define MESSAGE 0
# define U_C unsigned char

# include "libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct	s_color
{
	U_C			r;
	U_C			g;
	U_C			b;
}				t_color;

typedef struct	s_pixel
{
	int			x;
	int			y;
	double		height;
}				t_pixel;

typedef struct	s_segment
{
	t_pixel		point_a;
	t_pixel		point_b;
}				t_segment;

typedef struct	s_triangle
{
	t_pixel		point_a;
	t_pixel		point_b;
	t_pixel		point_c;
	int			x;
	int			y;
	int			end_x;
	int			end_y;
	double		area;
	double		perimeter;
}				t_triangle;

typedef struct	s_line_move
{
	t_pixel		v;
	t_pixel		s;
	int			err;
	int			e2;
	char		step;
}				t_line_move;

typedef struct	s_point
{
	double		x;
	double		y;
	double		z;
	t_pixel		pixel;
}				t_point;

typedef struct	s_map
{
	t_point		**point;
	int			height;
	int			width;
	double		depth_screen;
	double		depth_map;
	double		unit_x;
	double		unit_z;
	double		unit_y;
	double		center_map_x;
	double		center_map_z;
	double		move_x;
	double		move_y;
	double		move_z;
	double		min_height;
	double		max_height;
	int			color_min;
	int			color_max;
	int			color_line_min;
	int			color_line_max;
	int			color_screen;
}				t_map;

typedef enum	e_mode
{
	FDF, COLOR, CALCUL
}				t_mode;

typedef struct	s_window
{
	void		*window;
	void		*image;
	void		*mlx;
	int			line;
	int			endian;
	int			bpp;
	char		*ad;
	int			width;
	int			height;
	int			center_x;
	int			center_y;
	t_map		*map;
	t_mode		mode;
}				t_window;

int				draw_screen(t_window *win);
void			rotation_x(t_map *map, double vector);
void			rotation_y(t_map *map, double vector);
void			rotation_z(t_map *map, double vector);
void			project_map(t_map *map, t_window *win);
int				key_event(int keycode, void *param);
t_triangle		convert_in_triangle(t_pixel a, t_pixel b, t_pixel c);
t_pixel			convert_in_pixel(int x, int y);
t_segment		convert_in_segment(t_pixel a, t_pixel b);
void			color_triangle(t_window *win, t_triangle triangle);
void			draw_line(t_window *win, t_pixel p1, t_pixel p2, t_mode m);
void			draw_pixel(t_window *win, t_pixel p, t_color color);
void			color(t_window *win, t_map *map, int i, int j);
int				find_intersection(t_segment s1, t_segment s2, t_pixel *r);
double			perimeter(t_pixel a, t_pixel b, t_pixel c);
double			area(t_pixel a, t_pixel b, t_pixel c);
double			calculate_lenght(t_pixel a, t_pixel b);
void			free_point(t_map *map);
void			*safe_malloc(size_t size);
void			error(int n);
double			distance_point(t_point a, t_point b);
t_map			*read_map(int fd);
t_color			mix_color_line(t_window *w, t_segment s, t_pixel p, t_mode m);
t_color			mix_color_triangle(t_window *w, t_triangle t, t_pixel p);
int				change_color(int color);
int				next_pixel_in_line(t_pixel *ap, t_pixel p, t_line_move *lm);
t_line_move		initialize_line_move(t_pixel p1, t_pixel p2);
int				calculate_lenght_pixel(t_pixel a, t_pixel b);
void			draw_straight(t_window *w, t_pixel a, t_pixel b, t_triangle t);
int				in_x(t_pixel x, t_pixel a, t_pixel b);
int				in_y(t_pixel x, t_pixel a, t_pixel b);
void			sort_triangle(t_triangle t, t_triangle *result);
int				next_in_angle(t_pixel *p, t_pixel a, t_pixel b, t_line_move *l);
int				end_angle(t_pixel a, t_pixel b, t_triangle t);
int				in_screen(t_window *win, t_map *map, int i, int j);
void			free_all(t_window *win);
void			move_map(t_map *map, double vx, double vy, double vz);
void			move_map_center(t_map *map, double a, double b, double c);
t_color			decompose_color(unsigned int value);
void			message(char *str);

#endif
