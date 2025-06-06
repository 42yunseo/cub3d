/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:21:41 by yunseo            #+#    #+#             */
/*   Updated: 2025/04/07 14:21:42 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_file(char *filename, t_vars *vars)
{
	int	fd;

	if (ft_strncmp(ft_strchr(filename, '.'), ".cub", 5) != 0)
		error_exit("wrong file format", vars);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit("file open failed", vars);
	return (fd);
}

void	info_init(char *filename, t_vars *vars)
{
	int		fd;

	fd = read_file(filename, vars);
	vars->info = (t_info *)malloc(sizeof(t_info));
	ft_memset(vars->info, 0, sizeof(t_info));
	read_element(fd, vars->info, vars);
	read_map(fd, vars->info, vars);
	close(fd);
}
