/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 13:44:03 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/14 11:17:13 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		rotate_map(t_map *map)
{
	int		i;
	int		j;
	t_point **new;
	int		tmp;

	if (map->width <= 1 || map->height <= 1)
		return (0);
	if (POINT[0][0].z >= POINT[MW][0].z && POINT[0][0].z >= POINT[0][MH].z)
		return (0);
	new = safe_malloc(sizeof(t_point*) * map->height);
	j = -1;
	while (++j < map->height)
	{
		i = -1;
		new[MH - j] = safe_malloc(sizeof(t_point) * map->width);
		while (++i < map->width)
			new[MH - j][i] = POINT[i][j];
	}
	free_point(map);
	tmp = map->width;
	map->width = map->height;
	map->height = tmp;
	map->point = new;
	return (1);
}

void	draw_map_by_column(t_window *win, t_map *map)
{
	int		i;
	int		j;

	i = -1;
	while (++i < map->width)
	{
		j = -1;
		while (++j < map->height)
			if (POINT[i][j].z > 0)
			{
				if (win->mode == COLOR && i < map->width - 1
					&& j < map->height - 1)
					color(win, map, i, j);
				if (i < map->width - 1 && POINT[i + 1][j].z > 0)
					draw_line(win, COIN_A, COIN_B, FDF);
				if (j < map->height - 1 && POINT[i][j + 1].z > 0)
					draw_line(win, COIN_A, COIN_D, FDF);
			}
	}
}

void	draw_map_by_line(t_window *win, t_map *map)
{
	int		i;
	int		j;

	j = -1;
	while (++j < map->height)
	{
		i = -1;
		while (++i < map->width)
			if (POINT[i][j].z > 0)
			{
				if (win->mode == COLOR && i < map->width - 1
					&& j < map->height - 1)
					color(win, map, i, j);
				if (i < map->width - 1 && POINT[i + 1][j].z > 0)
					draw_line(win, COIN_A, COIN_B, FDF);
				if (j < map->height - 1 && POINT[i][j + 1].z > 0)
					draw_line(win, COIN_A, COIN_D, FDF);
			}
	}
}

void	draw_flat_map(t_window *win, t_map *map)
{
	int i;
	int j;

	if (map->width <= 1 && map->height <= 1)
	{
		i = 0;
		j = 0;
		draw_line(win, COIN_A, COIN_A, FDF);
		return ;
	}
	i = -1;
	j = 0;
	while (++i < map->width)
		if (POINT[i][j].z > 0)
			if (i < map->width - 1 && POINT[i + 1][j].z > 0)
				draw_line(win, COIN_A, COIN_B, FDF);
	j = -1;
	i = 0;
	while (++j < map->height)
		if (POINT[i][j].z > 0)
			if (j < map->height - 1 && POINT[i][j + 1].z > 0)
				draw_line(win, COIN_A, COIN_D, FDF);
}

int		draw_screen(t_window *win)
{
	int		i;
	int		j;
	t_map	*map;

	message("Draw...");
	i = -1;
	while (++i < win->width)
	{
		j = -1;
		while (++j < win->height)
			draw_pixel(win, CIP(i, j), decompose_color(0));
	}
	map = win->map;
	while (rotate_map(map))
		;
	if (win->map->width <= 1 || win->map->height <= 1)
		draw_flat_map(win, map);
	else if (POINT[0][0].z - POINT[MW][0].z > POINT[0][0].z - POINT[0][MH].z)
		draw_map_by_column(win, map);
	else
		draw_map_by_line(win, map);
	mlx_put_image_to_window(win->mlx, win->window, win->image, 0, 0);
	message("Finish.");
	return (0);
}
