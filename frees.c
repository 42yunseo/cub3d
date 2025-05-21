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

void	free_info(t_info *info)
{
	free(info->north_path);
	free(info->south_path);
	free(info->west_path);
	free(info->east_path);
	token_free(info->map);
	free(info);
}

void	free_vars(t_vars *vars)
{
	free(vars->player);
	if (vars->info != NULL)
		free_info(vars->info);
	mlx_destroy_window(vars->mlx, vars->win);
	free(vars->mlx);
}
