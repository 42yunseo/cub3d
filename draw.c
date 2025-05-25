/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 01:17:18 by yunseo            #+#    #+#             */
/*   Updated: 2025/05/25 01:17:19 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_texture_x(t_vars *vars, t_raycast *raycast)
{
	double	wall_x;
	int		texture_x;

	if (raycast->side == 0)
	{
		wall_x = vars->player->pos_y + \
		raycast->perp_wall_dist * raycast->ray_dir_y;
	}
	else
	{
		wall_x = vars->player->pos_x + \
		raycast->perp_wall_dist * raycast->ray_dir_x;
	}
	wall_x -= floor(wall_x);
	texture_x = (int)(wall_x * (double)TEXTURE_SIZE);
	if (raycast->side == 0 && raycast->ray_dir_x > 0)
		texture_x = TEXTURE_SIZE - texture_x - 1;
	if (raycast->side == 1 && raycast->ray_dir_y < 0)
		texture_x = TEXTURE_SIZE - texture_x - 1;
	raycast->texture_x = texture_x;
}

void	draw(t_vars *vars, t_raycast *raycast, int x)
{
	int	y;
	int	color;

	calc_line_height(vars, vars->player, raycast);
	raycast->dir = calc_wall_direction(raycast);
	calc_texture_x(vars, raycast);
	raycast->step = (double)(1.0 * TEXTURE_SIZE) / (double)raycast->line_height;
	raycast->texture_pos = \
	(raycast->draw_start - vars->h / 2 + raycast->line_height / 2) \
	* raycast->step;
	y = raycast->draw_start;
	while (y < raycast->draw_end)
	{
		raycast->texture_y = (int)raycast->texture_pos & (TEXTURE_SIZE - 1);
		raycast->texture_pos += raycast->step;
		color = vars->textures[raycast->dir] \
		.data[TEXTURE_SIZE * raycast->texture_y + raycast->texture_x];
		vars->img.data[vars->w * y + x] = color;
		y++;
	}
}

void	calc_line_height(t_vars *vars, t_player *p, t_raycast *raycast)
{
	double	perp_wall_dist;

	if (raycast->side == 0)
		perp_wall_dist = \
		(raycast->map_x - p->pos_x + (1 - raycast->step_x) / 2) \
		/ raycast->ray_dir_x;
	else
		perp_wall_dist = \
		(raycast->map_y - p->pos_y + (1 - raycast->step_y) / 2) \
		/ raycast->ray_dir_y;
	raycast->perp_wall_dist = perp_wall_dist;
	raycast->line_height = (int)(vars->h / perp_wall_dist);
	raycast->draw_start = -raycast->line_height / 2 + vars->h / 2;
	if (raycast->draw_start < 0)
		raycast->draw_start = 0;
	raycast->draw_end = raycast->line_height / 2 + vars->h / 2;
	if (raycast->draw_end >= vars->h)
		raycast->draw_end = vars->h - 1;
}

int	calc_wall_direction(t_raycast *raycast)
{
	if (raycast->side == 0)
	{
		if (raycast->ray_dir_x >= 0)
			return (EAST);
		return (WEST);
	}
	else
	{
		if (raycast->ray_dir_y >= 0)
			return (NORTH);
		return (SOUTH);
	}
}
