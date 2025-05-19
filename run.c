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

void    run(t_vars *vars)
{
    t_player    *p;

    int w = 1920;
    int h = 1080;
    p = vars->player;

    for (int x = 0; x < w; x++)
    {
        double camera_x = 2 * x / (double)w - 1; //x-coordinate in camera space
        double raydir_x = p->dir_x + p->plane_x * camera_x;
        double raydir_y = p->dir_y + p->plane_y * camera_x;
        //which box of the map we're in
      int map_x = p->pos_x;
      int map_y = p->pos_y;

      //length of ray from current position to next x or y-side
      double sideDist_x;
      double sideDist_y;

       //length of ray from one x or y-side to next x or y-side
      double deltaDist_x = fabs(1 / raydir_x);
      double deltaDist_y = fabs(1 / raydir_y);
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int step_x;
      int step_y;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

        //calculate step and initial sideDist
        if (raydir_x < 0)
        {
            step_x = -1;
            sideDist_x = (p->pos_x - map_x) * deltaDist_x;
        }
        else
        {
            step_x = 1;
            sideDist_x = (map_x + 1.0 - p->pos_x) * deltaDist_x;
        }
        if (raydir_y < 0)
        {
            step_y = -1;
            sideDist_y = (p->pos_y - map_y) * deltaDist_y;
        }
        else
        {
            step_y = 1;
            sideDist_y = (map_y + 1.0 - p->pos_y) * deltaDist_y;
        }
        //perform DDA
        while (hit == 0)
        {
            //jump to next map square, OR in x-direction, OR in y-direction
            if (sideDist_x < sideDist_y)
            {
                sideDist_x += deltaDist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                sideDist_y += deltaDist_y;
                map_y += step_y;
                side = 1;
            }
            //Check if ray has hit a wall
            if (vars->info->map[map_y][map_x] != '0')
                hit = 1;
        }
        //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
        if (side == 0)
            perpWallDist = (map_x - p->pos_x + (1 - step_x) / 2) / raydir_x;
        else
            perpWallDist = (map_y - p->pos_y + (1 - step_y) / 2) / raydir_y;
        //Calculate height of line to draw on screen
        int lineHeight = (int)(h / perpWallDist);

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + h / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + h / 2;
        if (drawEnd >= h)
            drawEnd = h - 1;

        for (int i = 0; i < drawStart; i++)
            mlx_pixel_put(vars->mlx, vars->win, x, i, *(int *)(&vars->info->ceiling));
        for (int y = drawStart; y < drawEnd; y++)
            mlx_pixel_put(vars->mlx, vars->win, x, y, 0xFF00FF00);
        for (int i = drawEnd; i < h; i++)
            mlx_pixel_put(vars->mlx, vars->win, x, i, *(int *)(&vars->info->floor));
    }
}
