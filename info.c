/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:21:41 by yunseo            #+#    #+#             */
/*   Updated: 2025/04/07 14:21:42 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	print_elements(t_info *info)
{
	printf("north : %s\n", info->north_path);
	printf("sorth : %s\n", info->south_path);
	printf("west : %s\n", info->west_path);
	printf("east : %s\n", info->east_path);
	printf("floor rgb : ");
	printf("%x\n", info->floor);
	printf("ceiling rgb : ");
	printf("%x\n", info->ceiling);
}

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

t_info	*info_init(char *filename, t_vars *vars)
{
	t_info	*info;
	int		fd;

	fd = read_file(filename, vars);
	info = (t_info *)malloc(sizeof(t_info));
	ft_memset(info, 0, sizeof(t_info));
	read_element(fd, info, vars);
	print_elements(info); // for debugging
	read_map(fd, info, vars);
	// print_map(info); // for debbuing
	close(fd);
	return (info);
}
