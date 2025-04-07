/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:36:24 by yunseo            #+#    #+#             */
/*   Updated: 2025/04/07 20:36:25 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*fetch_map(int fd, t_info *info, t_vars *vars)
{
	t_list	*list;
	t_list	*tmp;
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (*line == '\n')
			error_exit("fetch_map error", vars);
		tmp = ft_lstnew(ft_substr(line, 0, ft_strchr(line, '\n')));
		ft_lstadd_back(&list, tmp);
		free(line);
	}
}

int	read_map(int fd, t_info *info, t_vars *vars)
{
	t_list	*list;

	list = fetch_map(fd, info, vars);
}
