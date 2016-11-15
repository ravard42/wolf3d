/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 20:13:53 by ravard            #+#    #+#             */
/*   Updated: 2016/11/06 22:07:03 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>
# include "libft.h"

# include "redbrick.xpm"
# define MUR1 redbrick
# include "eagle.xpm"
# define PASSAGE1 eagle
# include "bluestone.xpm"
# define MUR2 bluestone
# include "space.xpm"
# define PASSAGE2 space
# include "circle_weave.xpm"
# define SYMBOL circle_weave_xpm
# include "wood.xpm"
# define SOL wood
# include "greystone.xpm"
# define PLAFOND greystone
# include "tnt.xpm"
# define TNT tnt

/*
**# define SPRINT 65505
**# define AVANCER 119
**# define AVANCER2 65236
**# define RECULER 115
**# define RECULER2 65364
**# define DROITE 101
**# define GAUCHE 113
**# define ROT_D 100
**# define ROT_D2 65363
**# define ROT_G 97
**# define ROT_G2 65361
**# define MAP2D 109
**# define BOOM 32
**# define EXIT 65307
*/

# define SPRINT 257
# define AVANCER 13
# define AVANCER2 126
# define RECULER 1
# define RECULER2 125
# define DROITE 14
# define GAUCHE 12
# define ROT_D 2
# define ROT_D2 124
# define ROT_G 0
# define ROT_G2 123
# define MAP2D 46
# define BOOM 49
# define EXIT 53

# define SPEED 2
# define ROT_SPEED M_PI / 42
# define MS 640
# define SQR 10

# define DIM_MUR MS / SQR

# define DEP 10
# define LSREP DEP / cos(M_PI / 6)

typedef struct			s_texture
{
	int				size;
	int				ncolors;
	int				chars_per_pixel;
	char			**ascii;
	int				*hexa;
	char			*datas;
}						t_texture;

typedef struct			s_pos
{
	float			*proj;
	float			t;
	float			*rd;
	float			*rg;
}						t_pos;

typedef	struct			s_move
{
	int				sprint;
	int				avant;
	int				arriere;
	int				droite;
	int				gauche;
	int				rot_d;
	int				rot_g;
}						t_move;

typedef struct			s_env
{
	char			**map;
	int				map_origin;
	t_pos			*p;
	t_move			*move;
	int				speed;
	void			*ptr;
	void			*win;
	int				*num_colonne_in_texture;
	char			*wall_type;
	float			**fc_vect;
	float			*fc_dist;
	float			*fc_dist2;
	int				*fc_numb_pix;

	t_texture		**t;
	void			**texture_img;
	char			**data_texture_img;

	void			*map3d_img;
	char			*data_map3d_img;
	void			*map2d_img;
	char			*data_map2d_img;
	char			map2d;
}						t_env;

void					is_wolf3d_valid_file(char *arg);
char					**load_map(int fd);

void					init_env(int fd, t_env *e);

int						is_wall(float *inter, char type, t_env *e);
void					ft_wall_type(int numb_rayon, float *d, float **inter,
							t_env *e);

void					load_textures(t_env *e);
void					ft_init_textures(t_env *e);
void					ft_get_texture_img_addrs(t_env *e);
void					ft_fill_img_with_textures(t_env *e);
void					init_texture_struct(t_texture *t, char **xpm,
							int image_magick);
void					fill_img_with_texture(t_texture *t, char *data_img);

void					draw_2d_pos(t_env *e);
void					expose_walls_in_map2d(t_env *e);
void					refresh_map2d(t_env *e);

void					expose(t_env *e);
int						expose_hook(t_env *e);
int						key_hook(int keycode, t_env *e);
int						key_hook_release(int keycode, t_env *e);
int						loop_hook(t_env *e);
void					ft_move(t_env *e);

int						check_pos(float *tmp, t_env *e);

void					img_draw_line(float *first, float *second,
							t_env *e, int ecran);
int						vertical_intersection(float x_const, float y,
							float *tmp);
int						horizontal_intersection(float x, float y_const,
							float *tmp);
int						apex_intersection(int *params, char *wall,
							float *tmp);
float					distance(float *a, float *b);

float					dist_rayon_mur(int numb_rayon, t_env *e);
float					*dist_rayons_tab(t_env *e);
float					*wall_projections(float *dist_rayons_tab);
void					write_3d_img(float *wall_projection_tab, t_env *e);

void					h_ray_cast(t_env *e);
void					write_sol_plafond(int numb_rayon, t_env *e);

void					free_env(t_env *e);
void					ft_free_textures(t_env *e);
int						ft_exit(int keycode, t_env *e);

#endif
