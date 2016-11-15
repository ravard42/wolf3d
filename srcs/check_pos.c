/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 18:20:58 by ravard            #+#    #+#             */
/*   Updated: 2016/10/10 16:06:30 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int			*line_param(float *tmp)
{
	int	*param;

	param = (int *)malloc(sizeof(int) * 4);
	param[0] = (int)tmp[0] / (DIM_MUR) * (DIM_MUR);
	param[1] = (int)tmp[1] / (DIM_MUR) * (DIM_MUR);
	param[2] = param[0] + (DIM_MUR);
	param[3] = param[1] + (DIM_MUR);
	return (param);
}

static char			*wall_or_void(int *params, t_env *e)
{
	int		sqr_pos[2];
	char	*wall;

	wall = (char *)malloc(sizeof(char) * 8);
	sqr_pos[0] = (int)params[0] / (DIM_MUR);
	sqr_pos[1] = (int)params[1] / (DIM_MUR);
	wall[0] = (sqr_pos[0] - 1 == -1) ? '1' :
		e->map[sqr_pos[1]][sqr_pos[0] - 1];
	wall[1] = (sqr_pos[1] - 1 == -1) ? '1' :
		e->map[sqr_pos[1] - 1][sqr_pos[0]];
	wall[2] = (sqr_pos[0] + 1 == SQR) ? '1' :
		e->map[sqr_pos[1]][sqr_pos[0] + 1];
	wall[3] = (sqr_pos[1] + 1 == SQR) ? '1' :
		e->map[sqr_pos[1] + 1][sqr_pos[0]];
	wall[4] = (sqr_pos[0] - 1 == -1 || sqr_pos[1] - 1 == -1) ? '1' :
		e->map[sqr_pos[1] - 1][sqr_pos[0] - 1];
	wall[5] = (sqr_pos[0] + 1 == SQR || sqr_pos[1] - 1 == -1) ? '1' :
		e->map[sqr_pos[1] - 1][sqr_pos[0] + 1];
	wall[6] = (sqr_pos[0] + 1 == SQR || sqr_pos[1] + 1 == SQR) ? '1' :
		e->map[sqr_pos[1] + 1][sqr_pos[0] + 1];
	wall[7] = (sqr_pos[0] - 1 == -1 || sqr_pos[1] + 1 == SQR) ? '1' :
		e->map[sqr_pos[1] + 1][sqr_pos[0] - 1];
	return (wall);
}

int					check_pos(float *tmp, t_env *e)
{
	int		*param;
	char	*wall;
	int		ret;

	param = line_param(tmp);
	wall = wall_or_void(param, e);
	ret = 1;
	ret = (wall[0] != '0' && vertical_intersection(param[0], param[1], tmp))
		? 0 : ret;
	ret = (wall[1] != '0' && horizontal_intersection(param[0], param[1], tmp))
		? 0 : ret;
	ret = (wall[2] != '0' && vertical_intersection(param[2], param[1], tmp))
		? 0 : ret;
	ret = (wall[3] != '0' && horizontal_intersection(param[0], param[3], tmp))
		? 0 : ret;
	ret = (apex_intersection(param, wall, tmp)) ? 0 : ret;
	free(param);
	free(wall);
	return (ret);
}
