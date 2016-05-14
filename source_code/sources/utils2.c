/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 14:29:14 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/05 14:29:10 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		change_color(int color)
{
	if (color == BLUE)
		return (RED);
	if (color == RED)
		return (GREEN);
	if (color == GREEN)
		return (MAGENTA);
	if (color == MAGENTA)
		return (JAUNE);
	if (color == JAUNE)
		return (CYAN);
	if (color == CYAN)
		return (BLACK);
	if (color == BLACK)
		return (WHITE);
	return (BLUE);
}

void	sort_triangle(t_triangle t, t_triangle *result)
{
	int l_ab;
	int l_ac;
	int l_bc;

	l_ab = calculate_lenght_pixel(t.point_a, t.point_b);
	l_ac = calculate_lenght_pixel(t.point_a, t.point_c);
	l_bc = calculate_lenght_pixel(t.point_b, t.point_c);
	if (l_ab >= l_ac && l_ab >= l_bc)
	{
		result->point_a = t.point_a;
		result->point_b = t.point_b;
		result->point_c = t.point_c;
	}
	else if (l_ac >= l_ab && l_ac >= l_bc)
	{
		result->point_a = t.point_a;
		result->point_b = t.point_c;
		result->point_c = t.point_b;
	}
	else
	{
		result->point_a = t.point_b;
		result->point_b = t.point_c;
		result->point_c = t.point_a;
	}
}

int		next_in_angle(t_pixel *x, t_pixel a, t_pixel b, t_line_move *lm)
{
	int r;

	if (lm->step == 0)
	{
		r = next_pixel_in_line(x, a, lm);
		if (!r)
		{
			*lm = initialize_line_move(a, b);
			*x = a;
			lm->step = 1;
		}
		return (1);
	}
	else
		return (next_pixel_in_line(x, b, lm));
}

int		end_angle(t_pixel a, t_pixel b, t_triangle t)
{
	if (!in_y(t.point_c, t.point_a, t.point_b))
	{
		if (a.x == b.x)
			return (1);
	}
	else
	{
		if (a.y == b.y)
			return (1);
	}
	return (0);
}

int		in_screen(t_window *win, t_map *map, int i, int j)
{
	if (COIN_A.x >= 0 && COIN_A.x <= win->width
		&& COIN_A.y >= 0 && COIN_A.y <= win->height)
		return (1);
	if (COIN_B.x >= 0 && COIN_B.x <= win->width
		&& COIN_B.y >= 0 && COIN_B.y <= win->height)
		return (1);
	if (COIN_C.x >= 0 && COIN_C.x <= win->width
		&& COIN_C.y >= 0 && COIN_C.y <= win->height)
		return (1);
	if (COIN_D.x >= 0 && COIN_D.x <= win->width
		&& COIN_D.y >= 0 && COIN_D.y <= win->height)
		return (1);
	return (0);
}
