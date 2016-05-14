/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 14:42:26 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/05 13:32:00 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	color_triangle(t_window *win, t_triangle triangle)
{
	t_line_move	lm1;
	t_line_move	lm2;
	t_triangle	t;
	t_pixel		tmp1;
	t_pixel		tmp2;

	sort_triangle(triangle, &t);
	tmp1 = t.point_a;
	tmp2 = t.point_a;
	lm1 = initialize_line_move(tmp1, t.point_b);
	lm2 = initialize_line_move(tmp2, t.point_c);
	while (next_pixel_in_line(&tmp1, t.point_b, &lm1))
	{
		while (!end_angle(tmp1, tmp2, t))
			next_in_angle(&tmp2, t.point_c, t.point_b, &lm2);
		draw_straight(win, tmp1, tmp2, triangle);
	}
}

int		color_crossed_square(t_window *win, t_map *map, int i, int j)
{
	t_pixel cross;

	if (find_intersection(CIS(COIN_A, COIN_B), CIS(COIN_C, COIN_D), &cross))
	{
		color_triangle(win, CIT(cross, COIN_A, COIN_D));
		color_triangle(win, CIT(cross, COIN_C, COIN_B));
		return (1);
	}
	if (find_intersection(CIS(COIN_A, COIN_D), CIS(COIN_C, COIN_B), &cross))
	{
		color_triangle(win, CIT(cross, COIN_A, COIN_B));
		color_triangle(win, CIT(cross, COIN_C, COIN_D));
		return (1);
	}
	return (0);
}

int		intersection(t_map *map, int i, int j)
{
	if (COIN_A.x > COIN_B.x && COIN_D.x < COIN_C.x)
		return (1);
	if (COIN_A.x < COIN_B.x && COIN_D.x > COIN_C.x)
		return (1);
	if (COIN_A.y > COIN_D.y && COIN_B.y < COIN_C.y)
		return (1);
	if (COIN_A.y < COIN_D.y && COIN_B.y > COIN_C.y)
		return (1);
	return (0);
}

void	color(t_window *win, t_map *map, int i, int j)
{
	t_triangle abc;
	t_triangle adc;
	t_triangle bad;
	t_triangle bcd;

	if (!in_screen(win, map, i, j))
		return ;
	if (intersection(map, i, j) && color_crossed_square(win, map, i, j))
		return ;
	abc = CIT(COIN_A, COIN_B, COIN_C);
	adc = CIT(COIN_A, COIN_D, COIN_C);
	bad = CIT(COIN_B, COIN_A, COIN_D);
	bcd = CIT(COIN_B, COIN_C, COIN_D);
	if (abc.area + adc.area < bad.area + bcd.area)
	{
		color_triangle(win, abc);
		color_triangle(win, adc);
		draw_line(win, COIN_A, COIN_C, COLOR);
	}
	else
	{
		color_triangle(win, bad);
		color_triangle(win, bcd);
		draw_line(win, COIN_B, COIN_D, COLOR);
	}
}
