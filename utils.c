/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:38:44 by yunseo            #+#    #+#             */
/*   Updated: 2025/03/31 20:38:45 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit(char *msg, t_vars *vars)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	exit_game(vars);
}

void	exit_game(t_vars *vars)
{
	//free(vars);
	free_all(vars);
	exit(EXIT_SUCCESS);
}

void	token_free(char **token)
{
	int	i;

	i = 0;
	if (token == NULL)
		return ;
	while (token[i] != NULL)
		free(token[i++]);
	free(token);
}

int	get_token_length(char **token)
{
	int	i;

	i = 0;
	if (token == NULL)
		return (0);
	while (token[i] != NULL)
		i++;
	return (i);
}
