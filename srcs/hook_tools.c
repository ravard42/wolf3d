/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 21:07:33 by ravard            #+#    #+#             */
/*   Updated: 2016/10/24 13:55:38 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		avancer(t_env *e)
{
	int		ok;
	float	tmp[2];

	tmp[0] = e->p->proj[0] + e->speed * cos(e->p->t);
	tmp[1] = e->p->proj[1] + e->speed * sin(e->p->t);
	ok = (check_pos(tmp, e)) ? 1 : 0;
	if (!ok)
	{
		tmp[0] = e->p->proj[0] + e->speed * cos(e->p->t);
		tmp[1] = e->p->proj[1];
		ok = (check_pos(tmp, e)) ? 1 : 0;
	}
	if (!ok)
	{
		tmp[0] = e->p->proj[0];
		tmp[1] = e->p->proj[1] + e->speed * sin(e->p->t);
		ok = (check_pos(tmp, e)) ? 1 : 0;
	}
	if (ok)
	{
		e->p->proj[0] = tmp[0];
		e->p->proj[1] = tmp[1];
	}
}

static void		reculer(t_env *e)
{
	int		ok;
	float	tmp[2];

	tmp[0] = e->p->proj[0] - e->speed * cos(e->p->t);
	tmp[1] = e->p->proj[1] - e->speed * sin(e->p->t);
	ok = (check_pos(tmp, e)) ? 1 : 0;
	if (!ok)
	{
		tmp[0] = e->p->proj[0] - e->speed * cos(e->p->t);
		tmp[1] = e->p->proj[1];
		ok = (check_pos(tmp, e)) ? 1 : 0;
	}
	if (!ok)
	{
		tmp[0] = e->p->proj[0];
		tmp[1] = e->p->proj[1] - e->speed * sin(e->p->t);
		ok = (check_pos(tmp, e)) ? 1 : 0;
	}
	if (ok)
	{
		e->p->proj[0] = tmp[0];
		e->p->proj[1] = tmp[1];
	}
}

static void		droite(t_env *e)
{
	int		ok;
	float	tmp[2];

	tmp[0] = e->p->proj[0] + e->speed * cos(e->p->t + M_PI / 2);
	tmp[1] = e->p->proj[1] + e->speed * sin(e->p->t + M_PI / 2);
	ok = (check_pos(tmp, e)) ? 1 : 0;
	if (!ok)
	{
		tmp[0] = e->p->proj[0] + e->speed * cos(e->p->t + M_PI / 2);
		tmp[1] = e->p->proj[1];
		ok = (check_pos(tmp, e)) ? 1 : 0;
	}
	if (!ok)
	{
		tmp[0] = e->p->proj[0];
		tmp[1] = e->p->proj[1] + e->speed * sin(e->p->t + M_PI / 2);
		ok = (check_pos(tmp, e)) ? 1 : 0;
	}
	if (ok)
	{
		e->p->proj[0] = tmp[0];
		e->p->proj[1] = tmp[1];
	}
}

static void		gauche(t_env *e)
{
	int		ok;
	float	tmp[2];

	tmp[0] = e->p->proj[0] - e->speed * cos(e->p->t + M_PI / 2);
	tmp[1] = e->p->proj[1] - e->speed * sin(e->p->t + M_PI / 2);
	ok = (check_pos(tmp, e)) ? 1 : 0;
	if (!ok)
	{
		tmp[0] = e->p->proj[0] - e->speed * cos(e->p->t + M_PI / 2);
		tmp[1] = e->p->proj[1];
		ok = (check_pos(tmp, e)) ? 1 : 0;
	}
	if (!ok)
	{
		tmp[0] = e->p->proj[0];
		tmp[1] = e->p->proj[1] - e->speed * sin(e->p->t + M_PI / 2);
		ok = (check_pos(tmp, e)) ? 1 : 0;
	}
	if (ok)
	{
		e->p->proj[0] = tmp[0];
		e->p->proj[1] = tmp[1];
	}
}

void			ft_move(t_env *e)
{
	e->speed = (e->move->sprint == 1) ? 3 * SPEED : SPEED;
	if (e->move->avant == 1)
		avancer(e);
	if (e->move->arriere == 1)
		reculer(e);
	if (e->move->droite == 1)
		droite(e);
	if (e->move->gauche == 1)
		gauche(e);
	if (e->move->rot_d == 1)
		e->p->t += ROT_SPEED;
	if (e->move->rot_g == 1)
		e->p->t -= ROT_SPEED;
}
