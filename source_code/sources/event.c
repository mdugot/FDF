/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 14:56:33 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/14 10:58:24 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	event_zoom(int key, t_window *win)
{
	t_map *map;

	message("Zoom in progress :");
	map = win->map;
	if (key == 32)
	{
		if (map->depth_screen / sqrt(map->height * map->width) < 4)
		{
			message("Already minimum zoom.");
			return ;
		}
		map->depth_screen /= EVENT_ZOOM;
	}
	else if (key == 31)
	{
		if (map->depth_screen / sqrt(map->height * map->width) > 150)
		{
			message("Already maximum zoom.");
			return ;
		}
		map->depth_screen *= EVENT_ZOOM;
	}
	project_map(win->map, win);
	draw_screen(win);
}

void	event_move(int key, t_window *win)
{
	message("Move in progress :");
	if (key == 38)
		move_map(win->map, -EVENT_MOVE, 0, 0);
	else if (key == 37)
		move_map(win->map, EVENT_MOVE, 0, 0);
	else if (key == 40)
		move_map(win->map, 0, EVENT_MOVE, 0);
	else if (key == 34)
		move_map(win->map, 0, -EVENT_MOVE, 0);
	else if (key == 126)
		win->center_y -= EVENT_MOVE;
	else if (key == 125)
		win->center_y += EVENT_MOVE;
	else if (key == 123)
		win->center_x -= EVENT_MOVE;
	else if (key == 124)
		win->center_x += EVENT_MOVE;
	project_map(win->map, win);
	draw_screen(win);
}

void	event_rotation(int key, t_window *win)
{
	message("Rotation in progress :");
	if (key == 13)
		rotation_y(win->map, EVENT_ROTATION);
	else if (key == 1)
		rotation_y(win->map, -EVENT_ROTATION);
	else if (key == 0)
		rotation_z(win->map, EVENT_ROTATION);
	else if (key == 2)
		rotation_z(win->map, -EVENT_ROTATION);
	else if (key == 12)
		rotation_x(win->map, EVENT_ROTATION);
	else if (key == 14)
		rotation_x(win->map, -EVENT_ROTATION);
	project_map(win->map, win);
	draw_screen(win);
}

void	event_color(int key, t_window *win)
{
	message("Change of color in progress :");
	if (key == 18)
		win->map->color_min = change_color(win->map->color_min);
	else if (key == 19)
		win->map->color_max = change_color(win->map->color_max);
	else if (key == 20)
		win->map->color_line_min = change_color(win->map->color_line_min);
	else if (key == 21)
		win->map->color_line_max = change_color(win->map->color_line_max);
	else if (key == 23)
		win->map->color_screen = change_color(win->map->color_screen);
	draw_screen(win);
}

int		key_event(int key, void *param)
{
	t_window *win;

	message("Event.");
	win = (t_window*)param;
	if (key == 53)
	{
		free_all(win);
		message("The program exited normally.");
		exit(0);
	}
	else if ((key >= 33 && key <= 40) || (key >= 123 && key <= 126))
		event_move(key, win);
	else if (key == 31 || key == 32)
		event_zoom(key, win);
	else if (key >= 0 && key <= 14)
		event_rotation(key, win);
	else if (key >= 18 && key <= 23)
		event_color(key, win);
	else if (key == 48)
	{
		message("Change of mode in progress :");
		win->mode = win->mode == FDF ? COLOR : FDF;
		draw_screen(win);
	}
	return (0);
}
