/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 21:10:34 by ravard            #+#    #+#             */
/*   Updated: 2016/11/06 21:55:49 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		not_valid(void)
{
	ft_putstr("ce fichier n'est pas valide\n");
	exit(0);
}

static int		is_wolf3d_file(char *arg)
{
	char	*rev;
	int		ret;
	char	tmp;

	rev = ft_revstr(arg);
	tmp = rev[7];
	rev[7] = '\0';
	ret = !ft_strcmp("d3flow.", rev) ? 1 : 0;
	rev[7] = tmp;
	ft_revstr(arg);
	return (ret);
}

void			is_wolf3d_valid_file(char *arg)
{
	int		i[4];
	char	*buf;

	if (is_wolf3d_file(arg) == 0)
		not_valid();
	if ((i[0] = open(arg, O_RDONLY)) == -1)
		ft_putstr("erreur lors de l'ouverture du fichier");
	buf = (char *)malloc(sizeof(char) * (SQR + 1));
	i[2] = -1;
	while (++i[2] < SQR)
	{
		if ((i[1] = read(i[0], buf, SQR + 1)) != SQR + 1)
			not_valid();
		i[3] = -1;
		while (++i[3] < SQR)
			if (!((buf[i[3]] >= '0' && buf[i[3]] <= '5') || buf[i[3]] == '9'))
				not_valid();
		if (buf[i[3]] != '\n')
			not_valid();
	}
	if ((i[1] = read(i[0], buf, 1)) != 0)
		not_valid();
	free(buf);
	close(i[0]);
}

static char		**init_map(void)
{
	int		i;
	char	**map;

	map = (char **)malloc(sizeof(char *) * SQR);
	i = -1;
	while (++i < SQR)
		map[i] = (char *)malloc(sizeof(char) * SQR);
	return (map);
}

char			**load_map(int fd)
{
	int			i;
	int			j;
	int			ret;
	char		**ptr;
	char		**map;

	map = init_map();
	ptr = (char **)malloc(sizeof(char *));
	i = -1;
	while ((ret = get_next_line(fd, ptr)) != 0)
	{
		if (ret == -1)
		{
			ft_putstr("gnl renvoit -1\n");
			exit(0);
		}
		++i;
		j = -1;
		while (++j < SQR)
			map[i][j] = ptr[0][j];
		free(*ptr);
	}
	free(*ptr);
	free(ptr);
	return (map);
}
