/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 17:44:41 by ravard            #+#    #+#             */
/*   Updated: 2016/11/06 22:00:57 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		is_h_wall(float *inter, t_env *e)
{
	if (inter[1] == 0 || inter[1] == MS)
		return (1);
	if ((int)inter[0] == 0 || (int)inter[0] == MS)
		return (0);
	if (e->map[(int)inter[1] / (DIM_MUR)][(int)inter[0] / (DIM_MUR)]
			!= '0' || e->map[(int)inter[1] / (DIM_MUR) - 1][(int)inter[0] /
			(DIM_MUR)] != '0')
		return (1);
	else
		return (0);
}

static int		is_v_wall(float *inter, t_env *e)
{
	if (inter[0] == 0 || inter[0] == MS)
		return (1);
	if ((int)inter[1] == 0 || (int)inter[1] == MS)
		return (0);
	if (e->map[(int)inter[1] / (DIM_MUR)][(int)inter[0] / (DIM_MUR)]
			!= '0' || e->map[(int)inter[1] / (DIM_MUR)][(int)inter[0] /
			(DIM_MUR) - 1] != '0')
		return (1);
	else
		return (0);
}

int				is_wall(float *inter, char type, t_env *e)
{
	if (type == 'V')
		return (is_v_wall(inter, e));
	else
		return (is_h_wall(inter, e));
}

static char		wall_type(char v_or_h, float *m, float sens, t_env *e)
{
	char	ret;
	int		y;
	int		x;

	x = (int)m[0] / (DIM_MUR);
	y = (int)m[1] / (DIM_MUR);
	if (v_or_h == 'v')
	{
		if (sens > 0)
			ret = (y >= 0 && y < SQR && x >= 0 && x < SQR) ?
				e->map[y][x] : '1';
		else
			ret = (y >= 0 && y < SQR && x >= 1 && x <= SQR) ?
				e->map[y][x - 1] : '1';
	}
	else
	{
		if (sens > 0)
			ret = (y >= 0 && y < SQR && x >= 0 && x < SQR) ?
				e->map[y][x] : '1';
		else
			ret = (y >= 1 && y <= SQR && x >= 0 && x < SQR) ?
				e->map[y - 1][x] : '1';
	}
	return (ret);
}

void			ft_wall_type(int numb_rayon, float *d, float **inter, t_env *e)
{
	e->wall_type[numb_rayon] = (d[2] == d[1]) ? wall_type('v', inter[1],
			e->fc_vect[numb_rayon][0], e) : wall_type('h', inter[0],
				e->fc_vect[numb_rayon][1], e);
	e->wall_type[numb_rayon] = (e->wall_type[numb_rayon] == '9' &&
			e->fc_vect[numb_rayon][1] > 0) ? '5' : e->wall_type[numb_rayon];
	e->wall_type[numb_rayon] = (e->wall_type[numb_rayon] == '9' &&
			e->fc_vect[numb_rayon][1] < 0) ? '8' : e->wall_type[numb_rayon];
}
