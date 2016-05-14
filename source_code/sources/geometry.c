/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 14:48:11 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/06 15:00:26 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double		calculate_lenght(t_pixel a, t_pixel b)
{
	double l;

	l = sqrt((double)pow(ABS(a.x - b.x), 2) + (double)pow(ABS(a.y - b.y), 2));
	return (l);
}

int			calculate_lenght_pixel(t_pixel a, t_pixel b)
{
	int			result;
	t_line_move	lm;

	result = 0;
	lm = initialize_line_move(a, b);
	while (next_pixel_in_line(&a, b, &lm))
		result++;
	return (result);
}

double		area(t_pixel a, t_pixel b, t_pixel c)
{
	double la;
	double lb;
	double lc;
	double half;

	la = calculate_lenght(a, b);
	lb = calculate_lenght(b, c);
	lc = calculate_lenght(c, a);
	half = (la + lb + lc) / 2.0;
	return (sqrt(half * (half - la) * (half - lb) * (half - lc)));
}

double		perimeter(t_pixel a, t_pixel b, t_pixel c)
{
	double la;
	double lb;
	double lc;

	la = calculate_lenght(a, b);
	lb = calculate_lenght(b, c);
	lc = calculate_lenght(c, a);
	return (la + lb + lc);
}

double		distance_point(t_point a, t_point b)
{
	double tmp;
	double distance;

	if (a.x != b.x && a.z != b.z)
		tmp = sqrt(pow(ABS(a.x - b.x), 2) + pow(ABS(a.z - b.z), 2));
	else if (a.x == b.x && a.z == b.z)
		tmp = 0;
	else if (a.x == b.x)
		tmp = ABS(a.z - b.z);
	else
		tmp = ABS(a.x - b.x);
	if (tmp != 0 && a.y != b.y)
		distance = sqrt(pow(ABS(a.y - b.y), 2) + pow(tmp, 2));
	else if (a.y == b.y && tmp == 0)
		distance = 0;
	else if (a.y == b.y)
		distance = tmp;
	else
		distance = ABS(a.y - b.y);
	return (distance);
}
