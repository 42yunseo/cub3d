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
	int		max_width;
	int		line_width;

	list = NULL;
	max_width = -1;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (*line == '\n') // 앞에서 엔터 하나 제거안하면 여기서 걸림 이전 로직에서 엔터 제거 필요
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
	info->x = max_width;
	info->y = ft_lstsize(list);
	return (list);
}

void	free_map(char **map, int max_idx)
{
	int	i;

	i = 0;
	while (i < max_idx)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

char	**map_allocate(int x, int y)
{
	int		i;
	char	**ret;


	ret = (char **)malloc(sizeof(char *) * y);
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
			free_map(ret, i);
			return (0);
		}
		i++;
	}
	return (ret);
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
		while (j < x && list_line[j]) {
			map[i][j] = list_line[j];
			j++;
		}
		map[i][j] = '\0';
		tmp_list = tmp_list->next;
		i++;
	}
}


int	check_space(t_info *info, int x, int y)
{
	const int	dx[4] = {1, 0, -1, 0};
	const int	dy[4] = {0, 1, 0, -1};
	int			i;
	int 		xx;
	int			yy;

	i = 0;
	while (i < 4)
	{
		xx = x + dx[i];
		yy = y + dy[i];
		
		if (xx < 0 || xx >= info->y || yy < 0 || yy >= info->x)
		{
			i++;
			continue;
		}
		if (!(info->map[xx][yy] == ' ' || info->map[xx][yy] == '1')) {
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_zero(t_info *info, int x, int y)
{
	const int	dx[4] = {1, 0, -1, 0};
	const int	dy[4] = {0, 1, 0, -1};
	int			i;
	int 		xx;
	int			yy;

	i = 0;
	while (i < 4)
	{
		xx = x + dx[i];
		yy = y + dy[i];
		
		if (xx < 0 || xx >= info->y || yy < 0 || yy >= info->x) {
			return (0);

		}
		if (info->map[xx][yy] == ' ')
			return (0);
		i++;
	}
	return (1);
}


int	map_check(t_info *info)
{
	// 0 상하좌우 -> 공백일 수 없음.
	// 공백 상하좌우 -> 공백 or 1
	int	cnt;
	int	i;
	int	j;

	cnt = 0;
	i = 0;
	while (i < info->y)
	{
		j = 0;
		while (j < info->x && info->map[i][j])
		{
			if (info->map[i][j] == '1') {
				j++;
				continue;

			}
			else if (info->map[i][j] == ' ')
			{
				if (!check_space(info, i, j))
					return (0);
			}
			else if (info->map[i][j] == '0')
			{
				if (!check_zero(info, i, j))
					return (0);
			}
			else if (info->map[i][j] != '1' && ++cnt > 1)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
	
}

int	read_map(int fd, t_info *info, t_vars *vars)
{
	t_list	*list;
	char	**map;

	list = fetch_map(fd, info, vars);
	map = map_allocate(info->x, info->y);
	list_to_array_map(list, map, info->x, info->y);
	info->map = map;
	if (!map_check(info)) {
		printf("map fail!!\n");
		return (0);
	}
	printf("map success!!\n");
	return (1);
}