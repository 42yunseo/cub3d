/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:22:33 by yunseo            #+#    #+#             */
/*   Updated: 2025/04/07 17:22:34 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_color(char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		return (TRUE);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (TRUE);
	return (FALSE);
}

void	read_color(char *line, t_info *map, t_vars *vars)
{
	char	**token;
	t_rgb	*target;

	token = ft_split(line, ' ');
	if (token == NULL || get_token_length(token) != 2)
	{
		token_free(token);
		error_exit("invalid format", vars);
	}
	if (ft_strncmp(token[0], "F", 2) == 0)
		target = &map->floor;
	if (ft_strncmp(token[0], "C", 2) == 0)
		target = &map->ceiling;
	if (set_color(token[1], target) == FAILURE)
	{
		token_free(token);
		error_exit("", vars);
	}
	token_free(token);
}

int	set_color(char *color, t_rgb *target)
{
	char	**token;

	token = ft_split(color, ',');
	if (token == NULL || get_token_length(token) != 3)
	{
		token_free(token);
		return (FAILURE);
	}
	target->r = ft_atoi(token[0]);
	target->g = ft_atoi(token[1]);
	target->b = ft_atoi(token[2]);
	return (SUCCESS);
}
