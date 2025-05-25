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
	token_free(info->map);
	free(info);
}

void	free_vars(t_vars *vars)
{
	if (vars->player != NULL)
		free(vars->player);
	if (vars->img.img != NULL)
		mlx_destroy_image(vars->mlx, vars->img.img);
	textures_free(vars);
	if (vars->info != NULL)
		free_info(vars->info);
	if (vars->mlx != NULL && vars->win != NULL)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx != NULL)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	free(vars);
}
