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

int	check_space(t_info *info, int width, int height)
{
	const int	dx[4] = {1, 0, -1, 0};
	const int	dy[4] = {0, 1, 0, -1};
	int			i;
	int			xx;
	int			yy;

	i = 0;
	while (i < 4)
	{
		xx = width + dx[i];
		yy = height + dy[i];
		if (xx < 0 || xx >= info->height || yy < 0 || yy >= info->width)
		{
			i++;
			continue ;
		}
		if (!(info->map[xx][yy] == ' ' || info->map[xx][yy] == '1'))
			return (0);
		i++;
	}
	return (1);
}

int	check_zero(t_info *info, int width, int height)
{
	const int	dx[4] = {1, 0, -1, 0};
	const int	dy[4] = {0, 1, 0, -1};
	int			i;
	int			xx;
	int			yy;

	i = 0;
	while (i < 4)
	{
		xx = width + dx[i];
		yy = height + dy[i];
		if (xx < 0 || xx >= info->height || yy < 0 || yy >= info->width)
			return (0);
		if (info->map[xx][yy] == ' ' || info->map[xx][yy] == '\0')
			return (0);
		i++;
	}
	return (1);
}

int	map_unit_check(t_info *info, int i, int j, int *cnt)
{
	if (info->map[i][j] == ' ')
	{
		if (!check_space(info, i, j))
			return (0);
	}
	else if (info->map[i][j] == '0')
	{
		if (!check_zero(info, i, j))
			return (0);
	}
	else if (info->map[i][j] != '1' && ++(*cnt) > 1)
		return (0);
	return (1);
}

int	map_check(t_info *info)
{
	int	cnt;
	int	i;
	int	j;

	cnt = 0;
	i = 0;
	while (i < info->height)
	{
		j = 0;
		while (j < info->width && info->map[i][j])
		{
			if (!map_unit_check(info, i, j, &cnt))
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
	map = map_allocate(info->width, info->height);
	list_to_array_map(list, map, info->width, info->height);
	ft_lstclear(&list, free);
	info->map = map;
	if (!map_check(info))
	{
		printf("map fail!!\n");
		return (0);
	}
	printf("map success!!\n");
	return (1);
}
