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

void	read_texture(char *line, t_vars *vars)
{
	char	**token;

	token = ft_split(line, ' ');
	free(line);
	if (token == NULL || get_token_length(token) != 2)
	{
		token_free(token);
		error_exit("Invalid Direction Format", vars);
	}
	token[1][ft_strlen(token[1]) - 1] = '\0';
	if (ft_strncmp(token[0], "NO", 3) == 0)
		load_texture(vars, NORTH, token[1], token);
	else if (ft_strncmp(token[0], "SO", 3) == 0)
		load_texture(vars, SOUTH, token[1], token);
	else if (ft_strncmp(token[0], "WE", 3) == 0)
		load_texture(vars, WEST, token[1], token);
	else if (ft_strncmp(token[0], "EA", 3) == 0)
		load_texture(vars, EAST, token[1], token);
	else
	{
		token_free(token);
		error_exit("Invalid Direction", vars);
	}
	token_free(token);
}

void	load_texture(t_vars *vars, int dir, char *path, char **token)
{
	t_image	*img;
	int		w;
	int		h;

	if (vars->textures[dir].img != NULL)
	{
		token_free(token);
		error_exit("Duplicated Direction", vars);
	}
	vars->textures[dir].img = mlx_xpm_file_to_image \
	(vars->mlx, path, &w, &h);
	if (vars->textures[dir].img == NULL)
	{
		token_free(token);
		error_exit("Invalid Direction File", vars);
	}
	img = &vars->textures[dir];
	img->data = (int *)mlx_get_data_addr \
	(img->img, &img->bpp, &img->line_size, &img->endian);
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
