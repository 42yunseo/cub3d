/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:20:46 by yunseo            #+#    #+#             */
/*   Updated: 2025/05/20 04:20:53 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_vars *vars)
{
	t_player	*p;
	t_raycast	raycast;
	int			x;

	x = 0;
	p = vars->player;
	while (x < vars->w)
	{
		init_raycast(vars, p, &raycast, x);
		set_step_sidedist(p, &raycast);
		dda(vars, &raycast);
		calc_line_height(vars, p, &raycast);
		draw_line(vars, x, raycast.line_height);
		x++;
	}
}

void	init_raycast(t_vars *vars, t_player *p, t_raycast *raycast, int x)
{
	double	camera_x;

	ft_memset(raycast, sizeof(t_raycast), 0);
	camera_x = 2 * x / (double)vars->w - 1;
	raycast->ray_dir_x = p->dir_x + p->plane_x * camera_x;
	raycast->ray_dir_y = p->dir_y + p->plane_y * camera_x;
	raycast->map_x = p->pos_x;
	raycast->map_y = p->pos_y;
	raycast->delta_dist_x = fabs(1 / raycast->ray_dir_x);
	raycast->delta_dist_y = fabs(1 / raycast->ray_dir_y);
}

void	set_step_sidedist(t_player *p, t_raycast *raycast)
{
	if (raycast->ray_dir_x < 0)
	{
		raycast->step_x = -1;
		raycast->side_dist_x = \
		(p->pos_x - raycast->map_x) * raycast->delta_dist_x;
	}
	else
	{
		raycast->step_x = 1;
		raycast->side_dist_x = \
		(raycast->map_x + 1.0 - p->pos_x) * raycast->delta_dist_x;
	}
	if (raycast->ray_dir_y < 0)
	{
		raycast->step_y = -1;
		raycast->side_dist_y = \
		(p->pos_y - raycast->map_y) * raycast->delta_dist_y;
	}
	else
	{
		raycast->step_y = 1;
		raycast->side_dist_y = \
		(raycast->map_y + 1.0 - p->pos_y) * raycast->delta_dist_y;
	}
}

void	dda(t_vars *vars, t_raycast *raycast)
{
	int	hit;
	int	side;

	hit = 0;
	while (hit == 0)
	{
		if (raycast->side_dist_x < raycast->side_dist_y)
		{
			raycast->side_dist_x += raycast->delta_dist_x;
			raycast->map_x += raycast->step_x;
			side = 0;
		}
		else
		{
			raycast->side_dist_y += raycast->delta_dist_y;
			raycast->map_y += raycast->step_y;
			side = 1;
		}
		if (vars->info->map[raycast->map_y][raycast->map_x] != '0')
			hit = 1;
	}
	raycast->side = side;
}

void	calc_line_height(t_vars *vars, t_player *p, t_raycast *raycast)
{
	double	perp_walldist;

	if (raycast->side == 0)
		perp_walldist = \
		(raycast->map_x - p->pos_x + (1 - raycast->step_x) / 2) \
		/ raycast->ray_dir_x;
	else
		perp_walldist = \
		(raycast->map_y - p->pos_y + (1 - raycast->step_y) / 2) \
		/ raycast->ray_dir_y;
	raycast->line_height = (int)(vars->h / perp_walldist);
}

void	draw_line(t_vars *vars, int x, int line_height)
{
	int	y;
	int	draw_start;
	int	draw_end;

	y = 0;
	draw_start = -line_height / 2 + vars->h / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + vars->h / 2;
	if (draw_end >= vars->h)
		draw_end = vars->h - 1;
	while (y < draw_start)
		mlx_pixel_put(vars->mlx, vars->win, x, y++, vars->info->ceiling);
	while (y < draw_end)
		mlx_pixel_put(vars->mlx, vars->win, x, y++, 0x0000ff00);
	while (y < 1080)
		mlx_pixel_put(vars->mlx, vars->win, x, y++, vars->info->floor);
}
