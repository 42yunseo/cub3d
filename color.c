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

void	read_color(char *line, t_info *info, t_vars *vars)
{
	char	**token;
	int		*target;

	token = ft_split(line, ' ');
	free(line);
	if (token == NULL || get_token_length(token) != 2)
	{
		token_free(token);
		error_exit("invalid format", vars);
	}
	if (ft_strncmp(token[0], "F", 2) == 0)
		target = &info->floor;
	if (ft_strncmp(token[0], "C", 2) == 0)
		target = &info->ceiling;
	if (set_color(token[1], target) == FAILURE)
	{
		token_free(token);
		error_exit("Parsing Error in Color", vars);
	}
	token_free(token);
}

int	set_color(char *color, int *target)
{
	char	**token;
	int		rgb[3];

	token = ft_split(color, ',');
	if (token == NULL || get_token_length(token) != 3)
	{
		token_free(token);
		return (FAILURE);
	}
	rgb[0] = ft_atoi(token[0]);
	rgb[1] = ft_atoi(token[1]);
	rgb[2] = ft_atoi(token[2]);
	*target = (0x00 << 24) | (rgb[0] << 16) | (rgb[1] << 8) | rgb[0];
	token_free(token);
	return (SUCCESS);
}
