/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3d_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 21:28:32 by ravard            #+#    #+#             */
/*   Updated: 2016/11/06 21:55:33 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

float				*first_inter(float dir_rayon, char type, t_env *e)
{
	float		tmp[3];
	float		*ret;

	tmp[2] = 0;
	if (type == 'H' && sin(dir_rayon) != 0)
	{
		tmp[1] = (sin(dir_rayon) > 0) ? ((int)e->p->proj[1] + (DIM_MUR)) /
			(DIM_MUR) * (DIM_MUR) : (int)e->p->proj[1] / (DIM_MUR) * (DIM_MUR);
		if ((tmp[0] = e->p->proj[0] + (tmp[1] -
			e->p->proj[1]) / tan(dir_rayon)) <= MS && tmp[0] >= 0)
			tmp[2] = 1;
	}
	else if (type == 'V' && cos(dir_rayon) != 0)
	{
		tmp[0] = (cos(dir_rayon) > 0) ? ((int)e->p->proj[0] + (DIM_MUR)) /
			(DIM_MUR) * (DIM_MUR) : (int)e->p->proj[0] / (DIM_MUR) * (DIM_MUR);
		if ((tmp[1] = e->p->proj[1] + (tmp[0] -
			e->p->proj[0]) * tan(dir_rayon)) <= MS && tmp[1] >= 0)
			tmp[2] = 1;
	}
	ret = tmp[2] == 1 ? (float *)malloc(sizeof(float) * 2) : NULL;
	if (ret)
		ft_memcpy(ret, tmp, sizeof(float) * 2);
	return (ret);
}

static float		*first_hor_inter_rayon_wall(int numb_rayon, t_env *e)
{
	float	dir_rayon;
	float	*ret;

	dir_rayon = e->p->t - M_PI / 6 + (float)numb_rayon * (M_PI / 3) / MS;
	if ((ret = first_inter(dir_rayon, 'H', e)) == NULL)
		return (NULL);
	else
	{
		while (!is_wall(ret, 'H', e))
		{
			ret[1] = (sin(dir_rayon) > 0) ? ret[1] + DIM_MUR :
				ret[1] - DIM_MUR;
			ret[0] = (sin(dir_rayon) >= 0) ? ret[0] + (DIM_MUR)
				/ tan(dir_rayon) : ret[0] - DIM_MUR / tan(dir_rayon);
			if ((int)ret[0] < 0 || (int)ret[0] > MS)
			{
				free(ret);
				return (NULL);
			}
		}
		return (ret);
	}
}

static float		*first_ver_inter_rayon_wall(int numb_rayon, t_env *e)
{
	float	dir_rayon;
	float	*ret;

	dir_rayon = e->p->t - M_PI / 6 + (float)numb_rayon * (M_PI / 3) / MS;
	if ((ret = first_inter(dir_rayon, 'V', e)) == NULL)
		return (NULL);
	else
	{
		while (!is_wall(ret, 'V', e))
		{
			ret[0] = (cos(dir_rayon) > 0) ? ret[0] + DIM_MUR :
				ret[0] - DIM_MUR;
			ret[1] = (cos(dir_rayon) >= 0) ? ret[1] + (DIM_MUR)
				* tan(dir_rayon) : ret[1] - DIM_MUR * tan(dir_rayon);
			if ((int)ret[1] < 0 || (int)ret[1] > MS)
			{
				free(ret);
				return (NULL);
			}
		}
		return (ret);
	}
}

static int			numero_colonne(float *m, char h_or_v)
{
	int	ret;

	if (h_or_v == 'h')
		ret = (int)(m[0] - ((int)m[0] / (DIM_MUR)) * DIM_MUR);
	else
		ret = (int)(m[1] - ((int)m[1] / (DIM_MUR)) * DIM_MUR);
	return (ret);
}

float				dist_rayon_mur(int numb_rayon, t_env *e)
{
	float	*inter[2];
	float	d[3];

	inter[0] = first_hor_inter_rayon_wall(numb_rayon, e);
	inter[1] = first_ver_inter_rayon_wall(numb_rayon, e);
	d[0] = inter[0] ? distance(e->p->proj, inter[0]) : 0;
	d[1] = inter[1] ? distance(e->p->proj, inter[1]) : 0;
	if (d[0] && d[1])
		d[2] = (d[0] <= d[1]) ? d[0] : d[1];
	else
		d[2] = (!d[0]) ? d[1] : d[0];
	e->num_colonne_in_texture[numb_rayon] = (d[2] == d[1]) ?
		numero_colonne(inter[1], 'v') : numero_colonne(inter[0], 'h');
	e->fc_dist[numb_rayon] = d[2];
	e->fc_vect[numb_rayon][0] = (d[2] == d[1]) ? inter[1][0] - e->p->proj[0] :
		inter[0][0] - e->p->proj[0];
	e->fc_vect[numb_rayon][1] = (d[2] == d[1]) ? inter[1][1] - e->p->proj[1] :
		inter[0][1] - e->p->proj[1];
	ft_wall_type(numb_rayon, d, inter, e);
	if (inter[0])
		free(inter[0]);
	if (inter[1])
		free(inter[1]);
	return (d[2]);
}
