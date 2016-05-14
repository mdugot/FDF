/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 13:50:00 by mdugot            #+#    #+#             */
/*   Updated: 2016/02/17 15:36:48 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		error(int n)
{
	if (n == 1)
		ft_putendl_fd("An error occured : Empty map", 2);
	else if (n == 2)
		ft_putendl_fd("An error occured : Map too big", 2);
	else
		perror("An error occured ");
	exit(1);
}

void		draw_pixel(t_window *win, t_pixel p, t_color c)
{
	if (p.x < 0 || p.x >= win->width || p.y < 0 || p.y >= win->height)
		return ;
	if (win->endian != 0)
	{
		win->ad[p.y * win->line + p.x * (win->bpp/8)] = mlx_get_color_value(win->mlx, c.r);
		win->ad[p.y * win->line + p.x * (win->bpp/8) + 1] = mlx_get_color_value(win->mlx, c.g);
		win->ad[p.y * win->line + p.x * (win->bpp/8) + 2] = mlx_get_color_value(win->mlx, c.b);
	}
	else
	{
		win->ad[p.y * win->line + p.x * (win->bpp/8)] = mlx_get_color_value(win->mlx, c.b);
		win->ad[p.y * win->line + p.x * (win->bpp/8) + 1] = mlx_get_color_value(win->mlx, c.g);
		win->ad[p.y * win->line + p.x * (win->bpp/8) + 2] = mlx_get_color_value(win->mlx, c.r);
	}
}

t_pixel		convert_in_pixel(int x, int y)
{
	t_pixel result;

	result.x = x;
	result.y = y;
	return (result);
}

t_segment	convert_in_segment(t_pixel a, t_pixel b)
{
	t_segment result;

	result.point_a = a;
	result.point_b = b;
	return (result);
}

t_triangle	convert_in_triangle(t_pixel a, t_pixel b, t_pixel c)
{
	t_triangle	triangle;
	int			tab_x[3];
	int			tab_y[3];

	triangle.point_a = a;
	triangle.point_b = b;
	triangle.point_c = c;
	tab_x[0] = a.x;
	tab_x[1] = b.x;
	tab_x[2] = c.x;
	tab_y[0] = a.y;
	tab_y[1] = b.y;
	tab_y[2] = c.y;
	triangle.x = min_of(3, tab_x);
	triangle.y = min_of(3, tab_y);
	triangle.end_x = max_of(3, tab_x);
	triangle.end_y = max_of(3, tab_y);
	triangle.area = area(a, b, c);
	return (triangle);
}
