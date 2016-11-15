/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturer_sol_plafond.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 17:47:25 by ravard            #+#    #+#             */
/*   Updated: 2016/11/06 21:53:17 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		h_ray_cast(t_env *e)
{
	int	k;

	k = -1;
	while (++k < MS / 2)
		e->fc_dist2[k] = (DIM_MUR / 2) * tan(M_PI / 3 +
				k * ((float)(M_PI / 6) / (MS / 2)));
}

void		write_sol_plafond(int num_col, t_env *e)
{
	float		coef_correction;
	int			i;
	float		pos[2];
	int			tex[2];

	if (e->fc_numb_pix[num_col] > 0)
	{
		coef_correction = 232.0 / 330.443604;
		i = 0;
		while (++i <= e->fc_numb_pix[num_col])
		{
			pos[0] = e->p->proj[0] +
				(e->fc_dist2[i - 1] * coef_correction /
				e->fc_dist[num_col]) * e->fc_vect[num_col][0];
			pos[1] = e->p->proj[1] +
				(e->fc_dist2[i - 1] * coef_correction /
				e->fc_dist[num_col]) * e->fc_vect[num_col][1];
			tex[0] = ((int)pos[0] % (DIM_MUR));
			tex[1] = ((int)pos[1] % (DIM_MUR));
			*((int *)e->data_map3d_img + (MS - i) * MS + num_col) = *((int *)
					e->data_texture_img[6] + tex[1] * e->t[6]->size + tex[0]);
			*((int *)e->data_map3d_img + (i - 1) * MS + num_col) = *((int *)
					e->data_texture_img[7] + tex[1] * e->t[7]->size + tex[0]);
		}
	}
}
