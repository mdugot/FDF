/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 16:47:57 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/14 10:59:21 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		find_sign(double a, double b, double c)
{
	if (a >= 0 && b >= 0 && c >= 0)
		return (1);
	if (a >= 0 && b < 0 && c < 0)
		return (1);
	if (a < 0 && b < 0 && c >= 0)
		return (1);
	if (a < 0 && b >= 0 && c < 0)
		return (1);
	return (-1);
}

void	project_point(t_point *point, t_window *win)
{
	int sign;

	sign = find_sign(point->x, win->map->depth_screen, point->z);
	point->pixel.x = (int)(point->x * win->map->depth_screen / point->z);
	point->pixel.x += win->center_x;
	if (SIGN(point->pixel.x) != sign && ABS(point->pixel.x) > win->center_x)
	{
		if (sign == 1)
			point->pixel.x = 0x7FFFFFFF;
		else
			point->pixel.x = 0xFFFFFFFF;
	}
	sign = find_sign(point->y, win->map->depth_screen, point->z);
	point->pixel.y = (int)(point->y * win->map->depth_screen / point->z);
	point->pixel.y += win->center_y;
	if (SIGN(point->pixel.y) != sign && ABS(point->pixel.y) > win->center_y)
	{
		if (sign == 1)
			point->pixel.y = 0x7FFFFFFF;
		else
			point->pixel.y = 0xFFFFFFFF;
	}
}

void	project_map(t_map *map, t_window *win)
{
	int i;
	int j;

	message("Project points...");
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->height)
		{
			project_point(&(map->point[i][j]), win);
			j++;
		}
		i++;
	}
}
