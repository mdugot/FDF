/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 16:18:44 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/14 10:59:51 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_list	*read_file(int fd)
{
	t_list	*list;
	t_list	*elem;
	char	*line;
	char	**split;
	int		r;

	line = NULL;
	list = NULL;
	while ((r = get_next_line(fd, &line)) > 0)
	{
		split = ft_strsplit(line, ' ');
		if (split == NULL)
			error(0);
		elem = safe_malloc(sizeof(t_list));
		elem->content = split;
		elem->content_size = ft_strsplit_size(split);
		elem->next = NULL;
		ft_lstadd_end(&list, elem);
		if (MAX > 0 && (ft_lstmaxsize(list) > MAX || ft_lstsize(list) > MAX))
			error(2);
	}
	ft_strdel(&line);
	if (r == -1)
		error(0);
	return (list);
}

t_map	*new_void_map(t_list *list)
{
	double	size_factor;
	t_map	*map;

	message("Create new map...");
	map = safe_malloc(sizeof(t_map));
	map->width = ft_lstmaxsize(list);
	map->height = ft_lstsize(list);
	if (map->width <= 0 || map->height <= 0)
		error(1);
	if (MAX > 0 && (map->width > MAX || map->height > MAX))
		error(1);
	size_factor = 1.0 * (100.0 / ((double)map->width * (double)map->height));
	map->unit_x = sqrt(ABS(UNIT_X) * size_factor) * SIGN(UNIT_X);
	map->unit_y = sqrt(ABS(UNIT_Y) * size_factor) * SIGN(UNIT_Y);
	map->unit_z = sqrt(ABS(UNIT_Z) * size_factor) * SIGN(UNIT_Z);
	map->center_map_x = ((map->width - 1) * map->unit_x) / 2;
	map->center_map_z = ((map->height - 1) * map->unit_z) / 2;
	map->min_height = 0;
	map->max_height = 0;
	map->color_min = JAUNE;
	map->color_max = RED;
	map->color_line_min = MAGENTA;
	map->color_line_max = BLUE;
	map->color_screen = BLACK;
	return (map);
}

void	calculate_map_depth(t_map *map)
{
	double	max_distance;
	double	tmp;
	int		i;
	int		j;
	t_point	center;

	i = 0;
	max_distance = 0;
	center.x = map->center_map_x;
	center.z = map->center_map_z;
	center.y = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->height)
		{
			tmp = distance_point(POINT[i][j], center);
			if (tmp > max_distance)
				max_distance = tmp;
			j++;
		}
		i++;
	}
	map->depth_screen = DEPTH_SCREEN + max_distance;
	map->depth_map = DEPTH_MAP + max_distance;
}

void	read_line(int j, t_map *map, t_list *elem)
{
	char	**tmp;
	int		i;
	double	y;

	i = 0;
	tmp = (char**)elem->content;
	while (i < map->width)
	{
		POINT[i][j].x = (map->unit_x * (double)i) - map->center_map_x;
		POINT[i][j].z = (map->unit_z * (double)j) - map->center_map_z;
		y = 0;
		if (i < (int)elem->content_size)
			y = (double)ft_atoi(tmp[i]);
		POINT[i][j].y = map->unit_y * y;
		if (MAX > 0 && ABS(y) > MAX)
			error(2);
		POINT[i][j].pixel.height = POINT[i][j].y;
		if (POINT[i][j].y < map->min_height)
			map->min_height = POINT[i][j].y;
		if (POINT[i][j].y > map->max_height)
			map->max_height = POINT[i][j].y;
		i++;
	}
}

t_map	*read_map(int fd)
{
	t_list	*list;
	t_list	*tmp;
	int		i;
	t_map	*map;

	list = read_file(fd);
	if (list == NULL)
		error(1);
	map = new_void_map(list);
	i = -1;
	POINT = safe_malloc(sizeof(t_point*) * map->width);
	while (++i < map->width)
		POINT[i] = safe_malloc(sizeof(t_point) * map->height);
	i = 0;
	tmp = list;
	while (tmp != NULL)
	{
		read_line(i, map, tmp);
		tmp = tmp->next;
		i++;
	}
	calculate_map_depth(map);
	move_map(map, 0, 0, map->depth_map);
	ft_lstdel(&list, ft_deltab);
	return (map);
}
