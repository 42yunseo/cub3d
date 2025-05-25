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

	list = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (*line == '\n' && list == NULL)
		{
			free(line);
			continue;
		}
		if (*line == '\n')
			error_exit("fetch_map error", vars);
		tmp = ft_lstnew(ft_substr(line, 0, ft_strchr(line, '\n') - line));
		if ((int)ft_strlen(tmp->content) > info->width)
			info->width = ft_strlen(tmp->content);
		ft_lstadd_back(&list, tmp);
		free(line);
		line = get_next_line(fd);
	}
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
