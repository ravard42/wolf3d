/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 13:56:54 by ravard            #+#    #+#             */
/*   Updated: 2016/11/06 21:19:04 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void			free_maps_img(t_env *e)
{
	free(e->data_map2d_img);
	free(e->map2d_img);
	free(e->data_map3d_img);
	free(e->map3d_img);
}

void				free_env(t_env *e)
{
	int		i;

	i = -1;
	while (++i < SQR)
		free(e->map[i]);
	free(e->map);
	free(e->p->proj);
	free(e->p->rd);
	free(e->p->rg);
	free(e->p);
	free(e->move);
	free(e->num_colonne_in_texture);
	i = -1;
	while (++i < MS)
		free(e->fc_vect[i]);
	free(e->fc_vect);
	free(e->fc_dist);
	free(e->fc_dist2);
	free(e->fc_numb_pix);
	free(e->wall_type);
	free_maps_img(e);
	free(e->win);
	free(e->ptr);
	free(e);
}
