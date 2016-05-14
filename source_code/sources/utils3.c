/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 14:13:43 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/14 11:00:54 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move_map_center(t_map *map, double vx, double vy, double vz)
{
	int i;
	int j;

	i = -1;
	while (++i < map->width)
	{
		j = -1;
		while (++j < map->height)
		{
			POINT[i][j].x += vx;
			POINT[i][j].y += vy;
			POINT[i][j].z += vz;
		}
	}
}

void	move_map(t_map *map, double vx, double vy, double vz)
{
	int i;
	int j;

	i = -1;
	map->move_x += vx;
	map->move_y += vy;
	map->move_z += vz;
	while (++i < map->width)
	{
		j = -1;
		while (++j < map->height)
		{
			POINT[i][j].x += vx;
			POINT[i][j].y += vy;
			POINT[i][j].z += vz;
		}
	}
}

int		in_x(t_pixel x, t_pixel a, t_pixel b)
{
	if (x.x >= a.x && x.x <= b.x)
		return (1);
	if (x.x <= a.x && x.x >= b.x)
		return (1);
	return (0);
}

int		in_y(t_pixel x, t_pixel a, t_pixel b)
{
	if (x.y >= a.y && x.y <= b.y)
		return (1);
	if (x.y <= a.y && x.y >= b.y)
		return (1);
	return (0);
}

void	message(char *str)
{
	if (MESSAGE)
		ft_putendl(str);
}
