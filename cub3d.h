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

# define BTN_EXIT 17

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_info
{
	char	**map;
	int		x;
	int		y;
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	t_rgb	floor;
	t_rgb	ceiling;
}	t_info;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_info	*info;
}	t_vars;

// info.c
t_info	*info_init(char *filename, t_vars *vars);

// element.c
int		read_element(int fd, t_info *map, t_vars *vars);
void	parsing_element(char *line, t_info *map, t_vars *vars);

// texture.c
int		is_texture(char *line);
void	read_texture(char *line, t_info *map, t_vars *vars);

// color.c
int		is_color(char *line);
void	read_color(char *ine, t_info *map, t_vars *vars);
int		set_color(char *color, t_rgb *target);

// map.c
int		read_map(int fd, t_info *info, t_vars *vars);

// utils.c
void	error_exit(char *msg, t_vars *vars);
void	exit_game(t_vars *vars);
void	token_free(char **token);
int		get_token_length(char **token);

#endif /* CUB3D_H */