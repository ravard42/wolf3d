/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3d_funct_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 17:31:04 by ravard            #+#    #+#             */
/*   Updated: 2016/11/06 22:04:33 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

float			*dist_rayons_tab(t_env *e)
{
	int		i;
	float	*ret;

	ret = (float *)malloc(sizeof(float) * MS);
	i = -1;
	while (++i < MS)
		ret[i] = dist_rayon_mur(i, e);
	return (ret);
}

float			*wall_projections(float *dist_rayons_tab)
{
	int		i;
	float	*ret;

	ret = (float *)malloc(sizeof(float) * MS);
	i = -1;
	while (++i < MS)
		ret[i] = DIM_MUR * DEP / dist_rayons_tab[i];
	free(dist_rayons_tab);
	return (ret);
}

static void		write_mur(int nb_col, float hauteur, t_env *e)
{
	int	i;
	int	how_much_pixel;

	how_much_pixel = hauteur / 15 * MS;
	e->fc_numb_pix[nb_col] = (MS - how_much_pixel) / 2;
	e->wall_type[nb_col] = (e->wall_type[nb_col] == '0') ?
		'1' : e->wall_type[nb_col];
	i = -1;
	while (++i < how_much_pixel)
	{
		if ((e->fc_numb_pix[nb_col] + i) * MS + nb_col > 0
				&& ((e->fc_numb_pix[nb_col] + i) * MS + nb_col
				< MS * MS))
			*((int *)e->data_map3d_img + (e->fc_numb_pix[nb_col] + i) * MS +
				nb_col) = *((int *)e->data_texture_img[e->wall_type[nb_col]
				- '0'] + (int)(i * ((float)DIM_MUR / how_much_pixel)) *
				DIM_MUR + e->num_colonne_in_texture[nb_col]);
	}
}

void			write_3d_img(float *wall_projection_tab, t_env *e)
{
	int	j;

	j = -1;
	while (++j < MS)
	{
		write_mur(j, wall_projection_tab[j], e);
		write_sol_plafond(j, e);
	}
	free(wall_projection_tab);
	mlx_put_image_to_window(e->ptr, e->win, e->map3d_img, 0, 0);
}
