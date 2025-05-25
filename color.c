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

	line[ft_strlen(line) - 1] = '\0';
	token = ft_split(line, ' ');
	free(line);
	if (token == NULL || get_token_length(token) != 2)
	{
		token_free(token);
		error_exit("Invalid color format", vars);
	}
	if (ft_strncmp(token[0], "F", 2) == 0)
		target = &info->floor;
	if (ft_strncmp(token[0], "C", 2) == 0)
		target = &info->ceiling;
	if (set_color(token[1], target) == FAILURE)
	{
		token_free(token);
		error_exit("Invalid Color", vars);
	}
	token_free(token);
}

int	check_rgb(int rgb_int, char *rgb_str)
{
	char	*tmp;

	tmp = ft_itoa(rgb_int);
	if (ft_strncmp(rgb_str, tmp, ft_strlen(rgb_str)) != 0)
	{
		free(tmp);
		return (FAILURE);
	}
	if (rgb_int < 0 || rgb_int > 255)
	{
		free(tmp);
		return (FAILURE);
	}
	free(tmp);
	return (SUCCESS);
}

int	set_color(char *color, int *target)
{
	int		i;
	char	**token;
	int		rgb[3];

	token = ft_split(color, ',');
	if (*target != 0 || token == NULL || get_token_length(token) != 3)
	{
		token_free(token);
		return (FAILURE);
	}
	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(token[i]);
		if (check_rgb(rgb[i], token[i]) == FAILURE)
		{
			token_free(token);
			return (FAILURE);
		}
		i++;
	}
	*target = (0x00 << 24) | (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	token_free(token);
	return (SUCCESS);
}
