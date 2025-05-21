/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjeong <chjeong@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:31:40 by chjeong           #+#    #+#             */
/*   Updated: 2025/05/21 02:31:41 by chjeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    free_vars(t_vars *vars)
{
    free(vars->player);
    free(vars->win);
    free(vars->mlx);
    free(vars->info->north_path);
    free(vars->info->south_path);
    free(vars->info->west_path);
    free(vars->info->east_path);
    free_map(vars->info->map, vars->h);
    free(vars->info);
}
