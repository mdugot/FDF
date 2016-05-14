/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 16:47:42 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/05 14:30:44 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotation(double *x, double *y, double degree)
{
	double tmp_x;
	double tmp_y;
	double radian;
	double radius;
	double angle;

	if (*x == 0 && *y == 0)
		return ;
	radian = degree * M_PI / 180;
	radius = sqrt(pow(*x, 2) + pow(*y, 2));
	angle = atan(*y / *x);
	tmp_x = radius * cos(angle + radian);
	tmp_y = radius * sin(angle + radian);
	if (*x < 0)
	{
		tmp_x *= -1;
		tmp_y *= -1;
	}
	*x = tmp_x;
	*y = tmp_y;
}

void	rotation_z(t_map *map, double degree)
{
	int i;
	int j;

	move_map_center(map, -(map->move_x), -(map->move_y), -(map->move_z));
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->height)
		{
			rotation(&(POINT[i][j].z), &(POINT[i][j].x), degree);
			j++;
		}
		i++;
	}
	move_map_center(map, map->move_x, map->move_y, map->move_z);
}

void	rotation_y(t_map *map, double degree)
{
	int i;
	int j;

	move_map_center(map, -(map->move_x), -(map->move_y), -(map->move_z));
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->height)
		{
			rotation(&(POINT[i][j].y), &(POINT[i][j].z), degree);
			j++;
		}
		i++;
	}
	move_map_center(map, map->move_x, map->move_y, map->move_z);
}

void	rotation_x(t_map *map, double degree)
{
	int i;
	int j;

	move_map_center(map, -(map->move_x), -(map->move_y), -(map->move_z));
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->height)
		{
			rotation(&(POINT[i][j].x), &(POINT[i][j].y), degree);
			j++;
		}
		i++;
	}
	move_map_center(map, map->move_x, map->move_y, map->move_z);
}
