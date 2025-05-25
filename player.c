/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:01:49 by yunseo            #+#    #+#             */
/*   Updated: 2025/05/20 04:01:49 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	real_move(t_vars *vars, t_player *p, double dx, double dy)
{
	char	**map = vars->info->map;

	if (map[(int)(p->pos_y)][(int)(p->pos_x + dx)] != '1')
		p->pos_x += dx;

	if (map[(int)(p->pos_y + dy)][(int)(p->pos_x)] != '1')
		p->pos_y += dy;
	printf("(pos x,y) : (%f, %f)\n", p->pos_x, p->pos_y);
	printf("dir (x,y) : (%f, %f)\n", p->dir_x, p->dir_y);
}

void	move_func(t_vars *vars, t_player *p, int direction)
{
	double		dx = 0;
	double		dy = 0;

	if (direction == FORWARD)
	{
		dx = p->dir_x * MV_SPEED;
		dy = p->dir_y * MV_SPEED;
	}
	else if (direction == BACKWARD)
	{
		dx = -p->dir_x * MV_SPEED;
		dy = -p->dir_y * MV_SPEED;
	}
	else if (direction == LEFT)
	{
		dx = -p->dir_y * MV_SPEED;
		dy = p->dir_x * MV_SPEED;
	}
	else if (direction == RIGHT)
	{
		dx = p->dir_y * MV_SPEED;
		dy = -p->dir_x * MV_SPEED;
	}

	real_move(vars, p, dx, dy);
	render(vars);
}

// void	move(t_vars *vars, int direction)
// {
// 	char		**map;
// 	t_player	*p;

// 	map = vars->info->map;
// 	p = vars->player;
// 	if (direction == FORWARD)
// 	{
// 		if (map[(int)p->pos_y][(int)(p->pos_x + p->dir_x * MV_SPEED)] != '1' \
// 		&& map[(int)(p->pos_y + p->dir_y * MV_SPEED)][(int)p->pos_x] != '1')
// 		{
// 			p->pos_x += p->dir_x * MV_SPEED;
// 			p->pos_y += p->dir_y * MV_SPEED;
// 		}
// 	}
// 	if (direction == BACKWARD)
// 	{
// 		if (map[(int)p->pos_y][(int)(p->pos_x - p->dir_x * MV_SPEED)] != '1' \
// 		&& map[(int)(p->pos_y - p->dir_y * MV_SPEED)][(int)p->pos_x] != '1')
// 		{
// 			p->pos_x -= p->dir_x * MV_SPEED;
// 			p->pos_y -= p->dir_y * MV_SPEED;
// 		}
// 	}
// 	render(vars);
// }

// void	move2(t_vars *vars, int direction)
// {
// 	char		**map;
// 	t_player	*p;

// 	map = vars->info->map;
// 	p = vars->player;
// 	if (direction == LEFT)
// 	{
// 		if (map[(int)p->pos_y][(int)(p->pos_x - p->dir_y * MV_SPEED)] != '1' \
// 		&& map[(int)(p->pos_y + p->dir_x * MV_SPEED)][(int)p->pos_x] != '1')
// 		{
// 			p->pos_x -= p->dir_y * MV_SPEED;
// 			p->pos_y += p->dir_x * MV_SPEED;
// 		}
// 	}
// 	if (direction == RIGHT)
// 	{
// 		if (map[(int)p->pos_y][(int)(p->pos_x + p->dir_y * MV_SPEED)] != '1' \
// 		&& map[(int)(p->pos_y - p->dir_x * MV_SPEED)][(int)p->pos_x] != '1')
// 		{
// 			p->pos_x += p->dir_y * MV_SPEED;
// 			p->pos_y -= p->dir_x * MV_SPEED;
// 		}
// 	}
// 	render(vars);
// }

void	set_direction(t_player *p, char dir)
{
	if (dir == 'N')
	{
		p->dir_y = 1.0;
		p->plane_x = 0.66;
	}
	if (dir == 'S')
	{
		p->dir_y = -1.0;
		p->plane_x = -0.66;
	}
	if (dir == 'E')
	{
		p->dir_x = 1.0;
		p->plane_y = -0.66;
	}
	if (dir == 'W')
	{
		p->dir_x = -1.0;
		p->plane_y = 0.66;
	}
}

void	set_position(t_vars *vars, t_player *player)
{
	char	**map;
	int		w;
	int		h;

	h = 0;
	map = vars->info->map;
	while (h < vars->info->height)
	{
		w = 0;
		while (map[h][w] != '\0')
		{
			if (ft_strchr("NESW", map[h][w]) != 0)
			{
				player->pos_x = w + 0.5;
				player->pos_y = h + 0.5;
				set_direction(player, map[h][w]);
			}
			w++;
		}
		h++;
	}
}

t_player	*player_init(t_vars *vars)
{
	t_player	*p;

	p = (t_player *)malloc(sizeof(t_player));
	if (p == NULL)
		exit_game(vars);
	ft_memset(p, 0, sizeof(t_player));
	set_position(vars, p);
	return (p);
}
