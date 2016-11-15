/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 13:52:54 by ravard            #+#    #+#             */
/*   Updated: 2016/11/06 21:57:30 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_init_textures(t_env *e)
{
	int	i;

	e->t = (t_texture **)malloc(sizeof(t_texture *) * 9);
	i = 0;
	while (++i < 9)
		e->t[i] = (t_texture *)malloc(sizeof(t_texture));
	init_texture_struct(e->t[1], MUR1, 1);
	init_texture_struct(e->t[2], PASSAGE1, 1);
	init_texture_struct(e->t[3], MUR2, 1);
	init_texture_struct(e->t[4], PASSAGE2, 1);
	init_texture_struct(e->t[5], SYMBOL, 0);
	init_texture_struct(e->t[6], SOL, 1);
	init_texture_struct(e->t[7], PLAFOND, 1);
	init_texture_struct(e->t[8], TNT, 1);
	e->texture_img = (void **)malloc(sizeof(void *) * 9);
	e->texture_img[1] = mlx_new_image(e->ptr, 64, 64);
	e->texture_img[2] = mlx_new_image(e->ptr, 64, 64);
	e->texture_img[3] = mlx_new_image(e->ptr, 64, 64);
	e->texture_img[4] = mlx_new_image(e->ptr, 64, 64);
	e->texture_img[5] = mlx_new_image(e->ptr, 64, 64);
	e->texture_img[6] = mlx_new_image(e->ptr, 64, 64);
	e->texture_img[7] = mlx_new_image(e->ptr, 64, 64);
	e->texture_img[8] = mlx_new_image(e->ptr, 64, 64);
}

void		ft_get_texture_img_addrs(t_env *e)
{
	int	info[3];

	e->data_texture_img = (char **)malloc(sizeof(char *) * 9);
	e->data_texture_img[1] = mlx_get_data_addr(e->texture_img[1],
			info, info + 1, info + 2);
	e->data_texture_img[2] = mlx_get_data_addr(e->texture_img[2],
			info, info + 1, info + 2);
	e->data_texture_img[3] = mlx_get_data_addr(e->texture_img[3],
			info, info + 1, info + 2);
	e->data_texture_img[4] = mlx_get_data_addr(e->texture_img[4],
			info, info + 1, info + 2);
	e->data_texture_img[5] = mlx_get_data_addr(e->texture_img[5],
			info, info + 1, info + 2);
	e->data_texture_img[6] = mlx_get_data_addr(e->texture_img[6],
			info, info + 1, info + 2);
	e->data_texture_img[7] = mlx_get_data_addr(e->texture_img[7],
			info, info + 1, info + 2);
	e->data_texture_img[8] = mlx_get_data_addr(e->texture_img[8],
			info, info + 1, info + 2);
}

void		ft_fill_img_with_textures(t_env *e)
{
	fill_img_with_texture(e->t[1], e->data_texture_img[1]);
	fill_img_with_texture(e->t[2], e->data_texture_img[2]);
	fill_img_with_texture(e->t[3], e->data_texture_img[3]);
	fill_img_with_texture(e->t[4], e->data_texture_img[4]);
	fill_img_with_texture(e->t[5], e->data_texture_img[5]);
	fill_img_with_texture(e->t[6], e->data_texture_img[6]);
	fill_img_with_texture(e->t[7], e->data_texture_img[7]);
	fill_img_with_texture(e->t[8], e->data_texture_img[8]);
}

void		load_textures(t_env *e)
{
	ft_init_textures(e);
	ft_get_texture_img_addrs(e);
	ft_fill_img_with_textures(e);
}

void		ft_free_textures(t_env *e)
{
	int		i;

	i = 0;
	while (++i < 9)
	{
		free(e->data_texture_img[i]);
		free(e->texture_img[i]);
		free(e->t[i]);
	}
	free(e->data_texture_img);
	free(e->texture_img);
	free(e->t);
}
