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

	max_width = -1;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (*line == '\n')
			error_exit("fetch_map error", vars);
		tmp = ft_lstnew(ft_substr(line, 0, ft_strchr(line, '\n')));
		line_width = ft_strlen(tmp);
		if (line_width > max_width)
			max_width = line_width;
		ft_lstadd_back(&list, tmp);
		free(line);
	}
	vars->info->x = max_width;
	vars->info->y = ft_lstsize(list);
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
		return (FAILURE);
	}
	i = 0;
	while (i < y)
	{
		ret[i] = (char *)malloc(x);
		if (ret[i] == NULL)
		{
			free_map(ret, i);
			return (FAILURE);
		}
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
		while (j < x)
			map[i][j] = list_line[j++];
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
		
		if (xx < 0 || xx >= info->y || yy < 0 || yy >= info->y)
			continue;
		if (!(info->map[xx][yy] == ' ' || info->map[xx][yy] == '1'))
			return (FAILURE);
	}
	return (SUCCESS);
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
		
		if (xx < 0 || xx >= info->y || yy < 0 || yy >= info->y)
			return (FAILURE);
		if (info->map[xx][yy] == ' ')
			return (FAILURE);
	}
	return (SUCCESS);
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
		while (j < info->x)
		{
			if (info->map[i][j] == ' ' && !check_space(info, i, j))
				return (FAILURE);
			else if (info->map[i][j] == '0' && !check_zero(info, i, j))
				return (FAILURE);
			else if (info->map[i][j] != '1' && ++cnt > 1)
				return (FAILURE);
		}
	}
	
}

int	read_map(int fd, t_info *info, t_vars *vars)
{
	t_list	*list;
	char	**map;
	int		i;

	list = fetch_map(fd, info, vars);
	map_allocate(vars->info->x, vars->info->y);
	list_to_array_map(list, map, vars->info->x, vars->info->y);
	if (!map_check(info))
		return (FAILURE);
	return (SUCCESS);
}

/* -> 0, 1, N,S,E,W (4개 중 1개) 
	    1111111111111111111111111
	    1000000000110000000000001
	    1011000001110000000000001
	    1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
*/


/*
int	map_side_check(char **map, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < y) {
		j = 0;
		if (i == 0 || i == y - 1)
			while (j < x)
				if (map[i][j++] == 0)
					return (FAILURE);
		else
		{
			while (map[i][j] == ' ')
				j++;
			if (map[i][j] != ' ' && map[i][j] == '0')
				return (FAILURE);
			j = x - 1;
			while (map[i][j] == ' ')
				j--;
			if (map[i][j] != ' ' && map[i][j] == '0')
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
*/