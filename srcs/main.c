/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 20:00:16 by ravard            #+#    #+#             */
/*   Updated: 2016/10/24 13:28:41 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			main(int argc, char **argv)
{
	int			fd;
	t_env		*e;

	if (argc == 2)
	{
		is_wolf3d_valid_file(argv[1]);
		if ((fd = open(argv[1], O_RDONLY)) != -1)
		{
			e = (t_env *)malloc(sizeof(t_env));
			init_env(fd, e);
			e->map_origin = (!ft_strcmp(argv[1], "maps/42.wolf3d") ||
					!ft_strcmp(argv[1], "./maps/42.wolf3d")) ? 1 : 0;
			expose(e);
			close(fd);
		}
		else
			ft_putstr("erreur lors de l'ouverture de fichier\n");
	}
	else
		ft_putstr("usage : ./wolf3d map_name.wolf3d\n");
	return (0);
}
