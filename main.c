/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 19:45:50 by yunseo            #+#    #+#             */
/*   Updated: 2025/03/31 19:45:50 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
		exit_game(vars);
	return (0);
}

t_vars	*vars_init(char *filename)
{
	t_vars	*vars;

	vars = (t_vars *)malloc(sizeof(t_vars));
	ft_memset(vars, 0, sizeof(t_vars));
	vars->mlx = mlx_init();
	vars->info = info_init(filename, vars);
	if (vars->info == NULL)
		exit_game(vars);
	vars->win = mlx_new_window(vars->mlx, \
		vars->info->x, vars->info->y, "cub3d");
	return (vars);
}

int	main(int argc, char **argv)
{
	t_vars	*vars;

	if (argc != 2)
	{
		error_exit("Invalid Argument", NULL);
		return (1);
	}
	vars = vars_init(argv[1]);
	if (vars == NULL)
		return (1);
	mlx_key_hook(vars->win, &key_press, vars->mlx);
	mlx_hook(vars->win, BTN_EXIT, 1L << 0, mlx_loop_end, vars->mlx);
	mlx_loop(vars->mlx);
	//run();
	exit_game(vars);
}
