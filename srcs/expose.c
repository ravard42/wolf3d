/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 17:29:30 by ravard            #+#    #+#             */
/*   Updated: 2016/10/14 00:20:50 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	ft_exit_cross(t_env *e)
{
	ft_free_textures(e);
	free_env(e);
	exit(0);
}

int			ft_exit(int keycode, t_env *e)
{
	(void)keycode;
	ft_free_textures(e);
	free_env(e);
	exit(0);
}

void		expose(t_env *e)
{
	mlx_expose_hook(e->win, &expose_hook, e);
	mlx_hook(e->win, 2, 1L << 0, &key_hook, e);
	mlx_hook(e->win, 3, 1L << 1, &key_hook_release, e);
	mlx_hook(e->win, 17, 1L << 17, &ft_exit_cross, e);
	mlx_loop_hook(e->ptr, &loop_hook, e);
	mlx_loop(e->ptr);
}
