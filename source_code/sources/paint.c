/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/02 18:22:47 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/14 11:17:59 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_color	decompose_color(unsigned int value)
{
	unsigned int	tmp;
	t_color			color;

	tmp = value << 24;
	tmp = tmp >> 24;
	color.b = (char)tmp;
	tmp = value << 16;
	tmp = tmp >> 24;
	color.g = (char)tmp;
	tmp = value << 8;
	tmp = tmp >> 24;
	color.r = (char)tmp;
	return (color);
}

int		compose_color(t_color color)
{
	unsigned int value;

	value = color.r;
	value = value << 8;
	value += color.g;
	value = value << 8;
	value += color.b;
	return (value);
}

t_color		find_color(t_map *map, double h, int color_min, int color_max)
{
	t_color result;
	t_color min;
	t_color	max;
	double	factor;

	if (map->min_height == map->max_height)
		return (decompose_color(color_min));
	min = decompose_color(color_min);
	max = decompose_color(color_max);
	factor = ABS(h - map->min_height) / (map->max_height - map->min_height);
	result.r = (double)min.r + (double)(max.r - min.r) * factor;
	result.g = (double)min.g + (double)(max.g - min.g) * factor;
	result.b = (double)min.b + (double)(max.b - min.b) * factor;
	return (result);
}

t_color		mix_color_line(t_window *win, t_segment s, t_pixel x, t_mode mode)
{
	double	ax;
	double	bx;
	double	l;
	double	h;
	t_map	*map;

	map = win->map;
	ax = calculate_lenght(s.point_a, x);
	bx = calculate_lenght(s.point_b, x);
	l = ax + bx;
	h = s.point_a.height + (s.point_b.height - s.point_a.height) * (ax / l);
	if (mode == FDF)
		return (find_color(map, h, map->color_line_min, map->color_line_max));
	else if (mode == COLOR)
		return (find_color(map, h, map->color_min, map->color_max));
	else
		return (decompose_color(0xFFFFFF));
}

t_color		mix_color_triangle(t_window *win, t_triangle triangle, t_pixel x)
{
	double	fpa;
	double	fpb;
	double	fpc;
	double	h;
	t_map	*map;

	map = win->map;
	fpa = 1 - (triangle.area - area(PC, x, PB)) / triangle.area;
	fpb = 1 - (triangle.area - area(PC, x, PA)) / triangle.area;
	fpc = 1 - (triangle.area - area(PA, x, PB)) / triangle.area;
	h = PA.height * fpa + PB.height * fpb + PC.height * fpc;
	return (find_color(win->map, h, map->color_min, map->color_max));
}
