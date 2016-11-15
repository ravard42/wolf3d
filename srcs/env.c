/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 20:02:27 by ravard            #+#    #+#             */
/*   Updated: 2016/11/06 21:06:07 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void			init_pos(t_pos *p, char **map)
{
	int	i;
	int	j;

	p->proj = (float *)malloc(sizeof(float) * 2);
	i = -1;
	while (++i < SQR)
	{
		j = -1;
		while (++j < SQR)
			if (map[i][j] == '0')
				break ;
		if (map[i][j] == '0')
			break ;
	}
	p->proj[0] = j * (DIM_MUR) + (DIM_MUR) / 2;
	p->proj[1] = i * (DIM_MUR) + (DIM_MUR) / 2;
	p->t = M_PI / 2;
	p->rd = (float *)malloc(sizeof(float) * 2);
	p->rg = (float *)malloc(sizeof(float) * 2);
}

static void			init_move(t_move *move)
{
	move->sprint = 0;
	move->avant = 0;
	move->arriere = 0;
	move->droite = 0;
	move->gauche = 0;
	move->rot_d = 0;
	move->rot_g = 0;
}

static void			init_maps_img(t_env *e)
{
	int		info[3];

	e->map2d_img = mlx_new_image(e->ptr, MS, MS);
	e->data_map2d_img = mlx_get_data_addr(e->map2d_img, info,
			info + 1, info + 2);
	e->map3d_img = mlx_new_image(e->ptr, MS, MS);
	e->data_map3d_img = mlx_get_data_addr(e->map3d_img, info,
			info + 1, info + 2);
}

void				init_env(int fd, t_env *e)
{
	int	i;

	e->map = load_map(fd);
	e->p = (t_pos *)malloc(sizeof(t_pos));
	init_pos(e->p, e->map);
	e->move = (t_move *)malloc(sizeof(t_move));
	init_move(e->move);
	e->num_colonne_in_texture = (int *)malloc(sizeof(int) * MS);
	e->ptr = mlx_init();
	e->win = mlx_new_window(e->ptr, MS, MS, "Wolf3d");
	e->fc_vect = (float **)malloc(sizeof(float *) * MS);
	i = -1;
	while (++i < MS)
		e->fc_vect[i] = (float *)malloc(sizeof(float) * 2);
	e->fc_dist = (float *)malloc(sizeof(float) * MS);
	e->fc_dist2 = (float *)malloc(sizeof(float) * MS / 2);
	h_ray_cast(e);
	e->fc_numb_pix = (int *)malloc(sizeof(int) * MS);
	e->wall_type = (char *)malloc(sizeof(char) * MS);
	load_textures(e);
	e->map2d = 0;
	init_maps_img(e);
	expose_walls_in_map2d(e);
}
