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
