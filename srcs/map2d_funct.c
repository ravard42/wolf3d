/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 17:43:12 by ravard            #+#    #+#             */
/*   Updated: 2016/10/24 14:04:47 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		draw_2d_pos(t_env *e)
{
	e->p->rd[0] = e->p->proj[0] + LSREP * cos(e->p->t + M_PI / 6);
	e->p->rd[1] = e->p->proj[1] + LSREP * sin(e->p->t + M_PI / 6);
	e->p->rg[0] = e->p->proj[0] + LSREP * cos(e->p->t - M_PI / 6);
	e->p->rg[1] = e->p->proj[1] + LSREP * sin(e->p->t - M_PI / 6);
	img_draw_line(e->p->proj, e->p->rd, e, 0);
	img_draw_line(e->p->proj, e->p->rg, e, 0);
	img_draw_line(e->p->rd, e->p->rg, e, 1);
}

static void	pixelize_wall_in_map2d(int i, int j, t_env *e)
{
	int	x;
	int	y;

	y = -1;
	while (++y < DIM_MUR)
	{
		x = -1;
		while (++x < DIM_MUR)
			*((int *)e->data_map2d_img + (i * MS)
				* (DIM_MUR) + j * (DIM_MUR) + y * MS + x) = 0xFFFFFF;
	}
}

void		expose_walls_in_map2d(t_env *e)
{
	int	i;
	int	j;

	i = -1;
	while (++i < SQR)
	{
		j = -1;
		while (++j < SQR)
		{
			if (e->map[i][j] != '0')
				pixelize_wall_in_map2d(i, j, e);
		}
	}
}

void		refresh_map2d(t_env *e)
{
	int	i;
	int	j;

	i = -1;
	while (++i < MS)
	{
		j = -1;
		while (++j < MS)
			*((int *)e->data_map2d_img + i * MS + j) = 0x0;
	}
	expose_walls_in_map2d(e);
}
