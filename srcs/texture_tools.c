/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 13:52:38 by ravard            #+#    #+#             */
/*   Updated: 2016/11/06 21:57:52 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		ft_hex_atoi(char *str)
{
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	while (++i < 6)
	{
		if (str[i] >= 'A' && str[i] <= 'F')
			ret += (10 + str[i] - 'A') * ft_power(16, i);
		else if (str[i] >= 'a' && str[i] <= 'f')
			ret += (10 + str[i] - 'a') * ft_power(16, i);
		else
			ret += (str[i] - '0') * ft_power(16, i);
	}
	return (ret);
}

static void		load_xpm_bijection(t_texture *t, char **xpm, int image_magick)
{
	int		i;
	int		k;
	char	**split;
	char	*rev;

	t->ascii = (char **)malloc(sizeof(char *) * t->ncolors);
	i = -1;
	while (++i < t->ncolors)
		t->ascii[i] = (char *)malloc(sizeof(char) * (t->chars_per_pixel + 1));
	t->hexa = (int *)malloc(sizeof(int) * t->ncolors);
	i = -1;
	while (++i < t->ncolors)
	{
		ft_strncpy(t->ascii[i], xpm[i + 1], t->chars_per_pixel);
		t->ascii[i][t->chars_per_pixel] = '\0';
		split = ft_strsplit(xpm[i + 1], ' ');
		rev = (i == 0) ? ft_revstr(split[2 - image_magick]) :
			ft_revstr(split[2]);
		t->hexa[i] = ft_hex_atoi(rev);
		k = -1;
		while (split[++k])
			free(split[k]);
		free(split);
	}
}

void			init_texture_struct(t_texture *t, char **xpm, int image_magick)
{
	int		i;
	char	**split;

	split = ft_strsplit(xpm[0], ' ');
	t->size = ft_atoi(split[0]);
	t->ncolors = ft_atoi(split[2]);
	t->chars_per_pixel = ft_atoi(split[3]);
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
	load_xpm_bijection(t, xpm, image_magick);
	t->datas = (char *)malloc(sizeof(char) * (t->size * t->size + 1));
	t->datas[0] = '\0';
	i = 0;
	while (++i <= t->size)
		ft_strcat(t->datas, xpm[t->ncolors + i]);
}

static int		comparison(char *datas, char *ascii, int numb_char)
{
	int	j;

	j = -1;
	while (++j < numb_char)
		if (datas[j] != ascii[j])
			return (0);
	return (1);
}

void			fill_img_with_texture(t_texture *t, char *data_img)
{
	int var[2];
	int	color;

	var[0] = 0;
	while (var[0] < t->size * t->size)
	{
		var[1] = -1;
		while (++var[1] < t->ncolors)
		{
			if (comparison(t->datas + var[0], t->ascii[var[1]],
						t->chars_per_pixel))
			{
				color = t->hexa[var[1]];
				break ;
			}
		}
		*((int *)data_img + var[0]) = color;
		var[0] += t->chars_per_pixel;
	}
	var[0] = -1;
	while (++var[0] < t->ncolors)
		free(t->ascii[var[0]]);
	free(t->ascii);
	free(t->hexa);
	free(t->datas);
}
