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

void	draw_line(t_vars *vars, int x, int line_height);

void	render(t_vars *vars)
{
	t_player	*p;

	int	x = 0;
	p = vars->player;

	while (x < vars->w)
	{
		double camera_x = 2 * x / (double)vars->w - 1; //x-coordinate in camera space
		double raydir_x = p->dir_x + p->plane_x * camera_x;
		double raydir_y = p->dir_y + p->plane_y * camera_x;
		//which box of the map we're in
		int map_x = p->pos_x;
		int map_y = p->pos_y;

		//length of ray from current position to next x or y-side
		double sidedist_x;
		double sidedist_y;

		//length of ray from one x or y-side to next x or y-side
		double deltadist_x = fabs(1 / raydir_x);
		double deltadist_y = fabs(1 / raydir_y);
		double perp_walldist;

		//what direction to step in x or y-direction (either +1 or -1)
		int step_x;
		int step_y;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (raydir_x < 0)
		{
			step_x = -1;
			sidedist_x = (p->pos_x - map_x) * deltadist_x;
		}
		else
		{
			step_x = 1;
			sidedist_x = (map_x + 1.0 - p->pos_x) * deltadist_x;
		}
		if (raydir_y < 0)
		{
			step_y = -1;
			sidedist_y = (p->pos_y - map_y) * deltadist_y;
		}
		else
		{
			step_y = 1;
			sidedist_y = (map_y + 1.0 - p->pos_y) * deltadist_y;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sidedist_x < sidedist_y)
			{
				sidedist_x += deltadist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				sidedist_y += deltadist_y;
				map_y += step_y;
				side = 1;
			}
			//Check if ray has hit a wall
			if (vars->info->map[map_y][map_x] != '0')
				hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0)
			perp_walldist = (map_x - p->pos_x + (1 - step_x) / 2) / raydir_x;
		else
			perp_walldist = (map_y - p->pos_y + (1 - step_y) / 2) / raydir_y;
		//Calculate height of line to draw on screen
		int line_height = (int)(vars->h / perp_walldist);
		draw_line(vars, x, line_height);
		x++;
	}
}

// int	dda(t_vars *vars, )
// {
// 	int	hit;
// 	int	side;

// 	hit = 0;
// 	while (hit == 0)
// 	{
// 		//jump to next map square, OR in x-direction, OR in y-direction
// 		if (sidedist_x < sidedist_y)
// 		{
// 			sidedist_x += deltadist_x;
// 			map_x += step_x;
// 			side = 0;
// 		}
// 		else
// 		{
// 			sidedist_y += deltadist_y;
// 			map_y += step_y;
// 			side = 1;
// 		}
// 		//Check if ray has hit a wall
// 		if (vars->info->map[map_y][map_x] != '0')
// 			hit = 1;
// 	}
// 	return (side);
// }

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
