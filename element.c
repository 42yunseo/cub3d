/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:52:02 by yunseo            #+#    #+#             */
/*   Updated: 2025/03/31 21:52:02 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parsing_element(char *line, t_info *info, t_vars *vars)
{
	if (is_texture(line) == TRUE)
		read_texture(line, vars);
	else
		read_color(line, info, vars);
}

int	read_element(int fd, t_info *info, t_vars *vars)
{
	char	*line;
	int		cnt;

	cnt = 0;
	while (cnt < 6)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (FAILURE);
		if (*line == '\n')
		{
			free(line);
			continue ;
		}
		else if (is_texture(line) == TRUE || is_color(line) == TRUE)
			parsing_element(line, info, vars);
		else
		{
			free(line);
			error_exit("Invalid Format in read_element", vars);
		}
		cnt++;
	}
	return (SUCCESS);
}
