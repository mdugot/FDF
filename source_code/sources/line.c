/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 13:57:51 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/05 17:37:40 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw_straight(t_window *win, t_pixel p1, t_pixel p2, t_triangle t)
{
	if (p1.x == p2.x)
	{
		draw_pixel(win, p1, mix_color_triangle(win, t, p1));
		while (p1.y != p2.y)
		{
			p1.y += SIGN(p2.y - p1.y);
			draw_pixel(win, p1, mix_color_triangle(win, t, p1));
		}
	}
	else if (p1.y == p2.y)
	{
		draw_pixel(win, p1, mix_color_triangle(win, t, p1));
		while (p1.x != p2.x)
		{
			p1.x += SIGN(p2.x - p1.x);
			draw_pixel(win, p1, mix_color_triangle(win, t, p1));
		}
	}
}

void		draw_line(t_window *win, t_pixel p1, t_pixel p2, t_mode mode)
{
	t_line_move	ln;
	t_pixel		origin;

	ln.v = CIP(ABS(p2.x - p1.x), ABS(p2.y - p1.y));
	ln.s = CIP(SIGN(p2.x - p1.x), SIGN(p2.y - p1.y));
	ln.err = (ln.v.x > ln.v.y ? ln.v.x : -ln.v.y) / 2;
	origin = p1;
	while (1)
	{
		draw_pixel(win, p1, mix_color_line(win, CIS(origin, p2), p1, mode));
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		ln.e2 = ln.err;
		if (ln.e2 > -ln.v.x)
		{
			ln.err -= ln.v.y;
			p1.x += ln.s.x;
		}
		if (ln.e2 < ln.v.y)
		{
			ln.err += ln.v.x;
			p1.y += ln.s.y;
		}
	}
}

t_line_move	initialize_line_move(t_pixel p1, t_pixel p2)
{
	t_line_move	r;

	r.step = 0;
	r.v = CIP(ABS(p2.x - p1.x), ABS(p2.y - p1.y));
	r.s = CIP(SIGN(p2.x - p1.x), SIGN(p2.y - p1.y));
	r.err = (r.v.x > r.v.y ? r.v.x : -r.v.y) / 2;
	return (r);
}

int			next_pixel_in_line(t_pixel *p1, t_pixel p2, t_line_move *lm)
{
	if (p1->x == p2.x && p1->y == p2.y)
		return (0);
	lm->e2 = lm->err;
	if (lm->e2 > -lm->v.x)
	{
		lm->err -= lm->v.y;
		p1->x += lm->s.x;
	}
	if (lm->e2 < lm->v.y)
	{
		lm->err += lm->v.x;
		p1->y += lm->s.y;
	}
	return (1);
}

int			find_intersection(t_segment s1, t_segment s2, t_pixel *result)
{
	t_pixel		tmp;
	t_line_move	line_move_a;
	t_line_move	line_move_b;

	line_move_a = initialize_line_move(s1.point_a, s1.point_b);
	while (next_pixel_in_line(&(s1.point_a), s1.point_b, &line_move_a))
	{
		tmp = s2.point_a;
		line_move_b = initialize_line_move(tmp, s2.point_b);
		while (next_pixel_in_line(&tmp, s2.point_b, &line_move_b))
		{
			if (ABS(tmp.x - s1.point_a.x) + ABS(tmp.y - s1.point_a.y) < 2)
			{
				result->height = s1.point_a.height + s1.point_b.height;
				result->height += s2.point_a.height + s2.point_b.height;
				result->height /= 4;
				result->x = tmp.x;
				result->y = tmp.y;
				return (1);
			}
		}
	}
	return (0);
}
