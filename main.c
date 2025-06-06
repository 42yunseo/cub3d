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

void	rotate(t_vars *vars, int direction)
{
	double		old_dir_x;
	double		old_plane_x;
	t_player	*p;

	p = vars->player;
	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	if (direction == RIGHT)
	{
		p->dir_x = p->dir_x * cos(-ROT_SPEED) - p->dir_y * sin(-ROT_SPEED);
		p->dir_y = old_dir_x * sin(-ROT_SPEED) + p->dir_y * cos(-ROT_SPEED);
		p->plane_x = \
		p->plane_x * cos(-ROT_SPEED) - p->plane_y * sin(-ROT_SPEED);
		p->plane_y = \
		old_plane_x * sin(-ROT_SPEED) + p->plane_y * cos(-ROT_SPEED);
	}
	if (direction == LEFT)
	{
		p->dir_x = p->dir_x * cos(ROT_SPEED) - p->dir_y * sin(ROT_SPEED);
		p->dir_y = old_dir_x * sin(ROT_SPEED) + p->dir_y * cos(ROT_SPEED);
		p->plane_x = p->plane_x * cos(ROT_SPEED) - p->plane_y * sin(ROT_SPEED);
		p->plane_y = \
		old_plane_x * sin(ROT_SPEED) + p->plane_y * cos(ROT_SPEED);
	}
	render(vars);
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
		mlx_loop_end(vars->mlx);
	if (keycode == KEY_W)
		move_func(vars, vars->player, FORWARD);
	if (keycode == KEY_A)
		move_func(vars, vars->player, LEFT);
	if (keycode == KEY_S)
		move_func(vars, vars->player, BACKWARD);
	if (keycode == KEY_D)
		move_func(vars, vars->player, RIGHT);
	if (keycode == KEY_LEFT)
		rotate(vars, LEFT);
	if (keycode == KEY_RIGHT)
		rotate(vars, RIGHT);
	return (0);
}

t_vars	*vars_init(char *filename)
{
	t_vars	*vars;

	vars = (t_vars *)malloc(sizeof(t_vars));
	ft_memset(vars, 0, sizeof(t_vars));
	vars->mlx = mlx_init();
	info_init(filename, vars);
	if (vars->info == NULL)
		exit_game(vars);
	vars->w = 1920;
	vars->h = 1080;
	vars->player = player_init(vars);
	vars->img.img = mlx_new_image(vars->mlx, vars->w, vars->h);
	vars->win = mlx_new_window(vars->mlx, vars->w, vars->h, "cub3d");
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
	mlx_key_hook(vars->win, &key_press, vars);
	mlx_hook(vars->win, BTN_EXIT, 1L << 0, mlx_loop_end, vars->mlx);
	render(vars);
	mlx_loop(vars->mlx);
	exit_game(vars);
}
