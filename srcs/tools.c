/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 17:27:03 by ravard            #+#    #+#             */
/*   Updated: 2016/10/10 15:55:27 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			img_draw_line(float *first, float *second, t_env *e, int ecran)
{
	char			abscisse;
	float			min[2];
	int				color;

	color = ecran ? 0xFF0000 : 0x00FF00;
	min[0] = (first[0] <= second[0]) ? first[0] - 1 : second[0] - 1;
	min[1] = (first[1] <= second[1]) ? first[1] - 1 : second[1] - 1;
	abscisse = (v_abs_diff(second[0], first[0]) >=
			v_abs_diff(second[1], first[1])) ? 'x' : 'y';
	if (abscisse == 'x')
		while (min[0]++ < first[0] || min[0] < second[0])
			*((int *)e->data_map2d_img + (int)min[0] % MS
			+ (int)((second[1] - first[1]) / (second[0] - first[0]) *
			(min[0] - first[0]) + first[1]) * MS) = color;
	else if (abscisse == 'y')
		while (min[1]++ < first[1] || min[1] < second[1])
			*((int *)e->data_map2d_img + (int)((second[0]
			- first[0]) / (second[1] - first[1]) * (min[1] - first[1])
			+ first[0]) % MS + (int)min[1] * MS) = color;
}

int				vertical_intersection(float x_const, float y, float *tmp)
{
	float	y_min;

	y_min = y;
	while (y <= y_min + DIM_MUR)
	{
		if (sqrt(pow(tmp[0] - x_const, 2) +
			pow(tmp[1] - y, 2)) <= LSREP + 10)
			return (1);
		y++;
	}
	return (0);
}

int				horizontal_intersection(float x, float y_const, float *tmp)
{
	float	x_min;

	x_min = x;
	while (x <= x_min + DIM_MUR)
	{
		if (sqrt(pow(tmp[0] - x, 2) +
			pow(tmp[1] - y_const, 2)) <= LSREP + 10)
			return (1);
		x++;
	}
	return (0);
}

int				apex_intersection(int *param, char *wall, float *tmp)
{
	if (wall[4] != '0' && sqrt(pow(tmp[0] - param[0], 2) +
				pow(tmp[1] - param[1], 2)) <= LSREP + 10)
		return (1);
	if (wall[5] != '0' && sqrt(pow(tmp[0] - param[2], 2) +
				pow(tmp[1] - param[1], 2)) <= LSREP + 10)
		return (1);
	if (wall[6] != '0' && sqrt(pow(tmp[0] - param[2], 2) +
				pow(tmp[1] - param[3], 2)) <= LSREP + 10)
		return (1);
	if (wall[7] != '0' && sqrt(pow(tmp[0] - param[0], 2) +
				pow(tmp[1] - param[3], 2)) <= LSREP + 10)
		return (1);
	return (0);
}

float			distance(float *a, float *b)
{
	float	ret;

	ret = sqrt(pow(b[0] - a[0], 2) + pow(b[1] - a[1], 2));
	return (ret);
}
