/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:22:22 by yunseo            #+#    #+#             */
/*   Updated: 2025/04/07 17:22:24 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_texture(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (TRUE);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (TRUE);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (TRUE);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (TRUE);
	return (FALSE);
}

void	read_texture(char *line, t_info *map, t_vars *vars)
{
	char	**token;

	token = ft_split(line, ' ');
	if (token == NULL || get_token_length(token) != 2)
		error_exit("invalid format in read_texture", vars);
	token[1][ft_strlen(token[1]) - 1] = '\0';
	if (ft_strncmp(token[0], "NO", 3) == 0)
		map->north_path = ft_strdup(token[1]);
	else if (ft_strncmp(token[0], "SO", 3) == 0)
		map->south_path = ft_strdup(token[1]);
	else if (ft_strncmp(token[0], "WE", 3) == 0)
		map->west_path = ft_strdup(token[1]);
	else if (ft_strncmp(token[0], "EA", 3) == 0)
		map->east_path = ft_strdup(token[1]);
	else
	{
		token_free(token);
		error_exit("duplicated Input", vars);
	}
	token_free(token);
}

void	load_texture(t_vars *vars)
{
	int		i;
	t_image	*img;
	int		w;
	int		h;

	i = 0;
	vars->textures[NORTH].img = mlx_xpm_file_to_image \
	(vars->mlx, vars->info->north_path, &w, &h);
	vars->textures[SOUTH].img = mlx_xpm_file_to_image \
	(vars->mlx, vars->info->south_path, &w, &h);
	vars->textures[WEST].img = mlx_xpm_file_to_image \
	(vars->mlx, vars->info->west_path, &w, &h);
	vars->textures[EAST].img = mlx_xpm_file_to_image \
	(vars->mlx, vars->info->east_path, &w, &h);
	while (i < 4)
	{
		img = &vars->textures[i];
		img->data = (int *)mlx_get_data_addr \
		(img->img, &img->bpp, &img->line_size, &img->endian);
		i++;
	}
}

void	textures_free(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (vars->textures[i].img != NULL)
		{
			mlx_destroy_image(vars->mlx, vars->textures[i].img);
		}
		i++;
	}
}
