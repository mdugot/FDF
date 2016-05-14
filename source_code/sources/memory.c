/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 17:42:40 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/05 13:33:17 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_point(t_map *map)
{
	int i;

	i = 0;
	while (i < map->width)
	{
		ft_memdel((void**)&(map->point[i]));
		i++;
	}
	ft_memdel((void**)&(map->point));
}

void	*safe_malloc(size_t size)
{
	void	*result;

	result = ft_memalloc(size);
	if (result == NULL)
		error(0);
	return (result);
}

void	free_all(t_window *win)
{
	free_point(win->map);
	ft_memdel((void**)&(win->map));
	mlx_destroy_window(win->mlx, win->window);
	ft_memdel((void**)&win);
}
