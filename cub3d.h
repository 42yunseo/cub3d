/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 19:45:54 by yunseo            #+#    #+#             */
/*   Updated: 2025/03/31 19:45:55 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define TRUE	0
# define FALSE	1

# define SUCCESS	0
# define FAILURE	1

# define KEY_ESC	65307

# define KEY_W	119
# define KEY_A	97
# define KEY_S	115
# define KEY_D	100

# define KEY_UP		65362
# define KEY_LEFT	65361
# define KEY_DOWN	65364
# define KEY_RIGHT	65363

# define FORWARD	0
# define BACKWARD	1
# define LEFT		2
# define RIGHT		3

# define NORTH		0
# define SOUTH		1
# define WEST		2
# define EAST		3

# define MV_SPEED	0.131
# define ROT_SPEED	0.2
# define TEXTURE_SIZE	64
# define BTN_EXIT 17

typedef struct s_raycast
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	perp_wall_dist;
	int		dir;
	int		texture_x;
	int		texture_y;
	double	texture_pos;
	double	step;
}	t_raycast;

typedef struct s_info
{
	char	**map;
	int		width;
	int		height;
	int		floor;
	int		ceiling;
}	t_info;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_img
{
	void	*img;
	int		*data;
	int		bpp;
	int		line_size;
	int		endian;
}	t_img;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		textures[4];
	int			w;
	int			h;
	t_info		*info;
	t_player	*player;
}	t_vars;

// info.c
void		info_init(char *filename, t_vars *vars);

// element.c
int			read_element(int fd, t_info *map, t_vars *vars);
void		parsing_element(char *line, t_info *map, t_vars *vars);

// texture.c
int			is_texture(char *line);
void		read_texture(char *line, t_vars *vars);
void		load_texture(t_vars *vars, int dir, char *path, char **token);
void		textures_free(t_vars *vars);

// color.c
int			is_color(char *line);
void		read_color(char *ine, t_info *map, t_vars *vars);
int			set_color(char *color, int *target);

// map_allocate.c
t_list		*fetch_map(int fd, t_info *info, t_vars *vars);
void		list_to_array_map(t_list *list, char **map, int x, int y);
char		**map_allocate(int x, int y);

// map.c
int			read_map(int fd, t_info *info, t_vars *vars);

// player.c
t_player	*player_init(t_vars *vars);
// void		move(t_vars *vars, int direction);
// void		move2(t_vars *vars, int direction);
void		move_func(t_vars *vars, t_player *p, int direction);
void		real_move(t_vars *vars, t_player *p, double nx, double ny);

// utils.c
void		error_exit(char *msg, t_vars *vars);
void		exit_game(t_vars *vars);
void		token_free(char **token);
int			get_token_length(char **token);

// render.c
void		render(t_vars *vars);
void		init_raycast(t_vars *vars, t_player *p, t_raycast *raycast, int x);
void		set_step_sidedist(t_player *p, t_raycast *raycast);
void		dda(t_vars *vars, t_raycast *raycast);

// draw.c
void		draw(t_vars *vars, t_raycast *raycast, int x);
void		calc_line_height(t_vars *vars, t_player *p, t_raycast *raycast);
int			calc_wall_direction(t_raycast *raycast);

// frees.c
void		free_vars(t_vars *vars);

#endif /* CUB3D_H */