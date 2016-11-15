/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 17:50:24 by ravard            #+#    #+#             */
/*   Updated: 2016/11/06 21:04:11 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_map_origin(t_env *e)
{
	if (e->p->proj[0] > 320 && e->p->proj[0] < 370 &&
			e->p->proj[1] > 64 && e->p->proj[1] < 128)
	{
		e->p->proj[0] = 504;
		e->p->proj[1] = 544;
	}
	if (e->p->proj[0] > 526 && e->p->proj[0] < 576 &&
			e->p->proj[1] > 512 && e->p->proj[1] < 576)
	{
		e->p->proj[0] = 392;
		e->p->proj[1] = 96;
	}
}

int			expose_hook(t_env *e)
{
	int	i;

	i = -1;
	ft_move(e);
	if (e->map_origin == 1)
		ft_map_origin(e);
	if (e->map2d == 0)
	{
		while (++i < MS * MS)
			*((int *)e->data_map3d_img + i) = 0x0;
		write_3d_img(wall_projections(dist_rayons_tab(e)), e);
	}
	else
	{
		while (++i < MS * MS)
		{
			if (*((int *)e->data_map2d_img + i) != 0xFFFFFF)
				*((int *)e->data_map2d_img + i) = 0x0;
		}
		draw_2d_pos(e);
		mlx_put_image_to_window(e->ptr, e->win, e->map2d_img, 0, 0);
	}
	return (0);
}

int			key_hook(int keycode, t_env *e)
{
	if (keycode == SPRINT)
		e->move->sprint = 1;
	else if (keycode == AVANCER || keycode == AVANCER2)
		e->move->avant = 1;
	else if (keycode == RECULER || keycode == RECULER2)
		e->move->arriere = 1;
	else if (keycode == DROITE)
		e->move->droite = 1;
	else if (keycode == GAUCHE)
		e->move->gauche = 1;
	else if (keycode == ROT_D || keycode == ROT_D2)
		e->move->rot_d = 1;
	else if (keycode == ROT_G || keycode == ROT_G2)
		e->move->rot_g = 1;
	else if (keycode == MAP2D)
		e->map2d = (e->map2d == 1) ? 0 : 1;
	else if (e->map_origin == 1 && keycode == BOOM && e->p->proj[0] > 192 &&
			e->p->proj[0] < 256 && e->p->proj[1] > 448 && e->p->proj[1] < 500)
	{
		e->map[6][3] = '0';
		refresh_map2d(e);
	}
	else if (keycode == EXIT)
		ft_exit(keycode, e);
	return (0);
}

int			key_hook_release(int keycode, t_env *e)
{
	if (keycode == SPRINT)
		e->move->sprint = 0;
	else if (keycode == AVANCER || keycode == AVANCER2)
		e->move->avant = 0;
	else if (keycode == RECULER || keycode == RECULER2)
		e->move->arriere = 0;
	else if (keycode == DROITE)
		e->move->droite = 0;
	else if (keycode == GAUCHE)
		e->move->gauche = 0;
	else if (keycode == ROT_D || keycode == ROT_D2)
		e->move->rot_d = 0;
	else if (keycode == ROT_G || keycode == ROT_G2)
		e->move->rot_g = 0;
	return (0);
}

int			loop_hook(t_env *e)
{
	expose_hook(e);
	return (0);
}
