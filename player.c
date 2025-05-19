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

void	set_direction(t_player *player, char dir)
{
	if (dir == 'N')
		player->dir_y = 1;
	if (dir == 'S')
		player->dir_y = -1;
	if (dir == 'E')
		player->dir_x = 1;
	if (dir == 'W')
		player->dir_x = -1;
}

void	func1(t_vars *vars, t_player *player)
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
				player->pos_x = w;
				player->pos_y = h;
				set_direction(player, map[h][w]);
			}
			w++;
		}
		h++;
	}
}

t_player	*player_init(t_vars *vars)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (player == NULL)
		exit_game(vars);
	ft_memset(player, 0, sizeof(t_player));
	func1(vars, player);
	player->plane_x = 1;
	player->plane_y = 0;
	return (player);
}
