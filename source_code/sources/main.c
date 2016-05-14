/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/12 14:41:05 by mdugot            #+#    #+#             */
/*   Updated: 2016/02/17 15:36:49 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_window	*new_window(int width, int height, char *name, t_map *map)
{
	t_window	*win;

	win = safe_malloc(sizeof(t_window));
	win->mlx = mlx_init();
	win->window = mlx_new_window(win->mlx, width, height, name);
	win->image = mlx_new_image(win->mlx, width, height);
	win->map = map;
	win->width = width;
	win->height = height;
	win->center_x = width / 2;
	win->center_y = height / 2;
	win->mode = FDF;
	win->ad = mlx_get_data_addr(win->image, &win->bpp, &win->line, &win->endian);
	return (win);
}

void		first_orientation(t_window *win)
{
	t_map	*map;
	double	square_size;

	map = win->map;
	rotation_z(win->map, 135);
	rotation_y(win->map, 45);
	square_size = map->depth_screen / sqrt(map->height * map->width);
	if (square_size < 4)
		while (square_size < 4)
		{
			map->depth_screen *= EVENT_ZOOM;
			square_size = map->depth_screen / sqrt(map->height * map->width);
		}
	else if (square_size > 150)
		while (square_size > 150)
		{
			map->depth_screen /= EVENT_ZOOM;
			square_size = map->depth_screen / sqrt(map->height * map->width);
		}
	project_map(win->map, win);
}

int			main(int argc, char **argv)
{
	t_window	*win;
	t_map		*map;
	int			fd;

	if (argc <= 1)
	{
		ft_putendl("Write your own map :");
		map = read_map(0);
	}
	else
	{
		message("Load map...");
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			error(0);
		map = read_map(fd);
		close(fd);
	}
	win = new_window(SCREEN_WIDTH, SCREEN_HEIGHT, "FdF", map);
	first_orientation(win);
	mlx_expose_hook(win->window, draw_screen, win);
	mlx_key_hook(win->window, key_event, win);
	mlx_loop(win->mlx);
	return (0);
}
