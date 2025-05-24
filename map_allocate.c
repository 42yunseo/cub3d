/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_allocate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjeong <chjeong@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 01:50:38 by chjeong           #+#    #+#             */
/*   Updated: 2025/05/21 01:50:40 by chjeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*fetch_map(int fd, t_info *info, t_vars *vars)
{
	t_list	*list;
	t_list	*tmp;
	char	*line;
	int		max_width;
	int		line_width;

	list = NULL;
	max_width = -1;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (*line == '\n')
			error_exit("fetch_map error", vars);
		tmp = ft_lstnew(ft_substr(line, 0, ft_strchr(line, '\n') - line));
		line_width = ft_strlen(tmp->content);
		if (line_width > max_width)
			max_width = line_width;
		if (list != NULL)
			ft_lstadd_back(&list, tmp);
		else
			list = tmp;
		free(line);
	}
	info->width = max_width;
	info->height = ft_lstsize(list);
	return (list);
}

void	list_to_array_map(t_list *list, char **map, int x, int y)
{
	int		i;
	int		j;
	char	*list_line;
	t_list	*tmp_list;

	i = 0;
	tmp_list = list;
	while (i < y)
	{
		j = 0;
		list_line = tmp_list->content;
		while (j < x && list_line[j])
		{
			map[i][j] = list_line[j];
			j++;
		}
		map[i][j] = '\0';
		tmp_list = tmp_list->next;
		i++;
	}
}

char	**map_allocate(int x, int y)
{
	int		i;
	char	**ret;

	ret = (char **)malloc(sizeof(char *) * (y + 1));
	if (ret == NULL)
	{
		free(ret);
		return (0);
	}
	i = 0;
	while (i < y)
	{
		ret[i] = (char *)malloc(x + 1);
		if (ret[i] == NULL)
		{
			token_free(ret);
			return (0);
		}
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
