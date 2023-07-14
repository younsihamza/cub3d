/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:12:44 by hyounsi           #+#    #+#             */
/*   Updated: 2023/07/14 08:05:46 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_callback(int x, int y, t_vars *param)
{
	if (x >= 0 && x <= param->width_window
		&& y >= 0 && y <= param->height_window)
	{
		if (x - param->old_x_mouse < 0)
			param->deriction -= 0.05;
		else if (x - param->old_x_mouse > 0)
			param->deriction += 0.05;
	}
	param->old_x_mouse = x;
	return (0);
}

void	init_angle_p(t_vars *vars)
{
	t_var	v;

	v.i = 0;
	while (vars->store_map[v.i])
	{
		v.j = 0;
		while (vars->store_map[v.i][v.j])
		{
			if (ft_strchr("NSWE", vars->store_map[v.i][v.j]) != NULL)
			{
				vars->player_x = (int)(v.j * vars->size + vars->size / 2);
				vars->player_y = (int)(v.i * vars->size + vars->size / 2);
				if (vars->store_map[v.i][v.j] == 'N')
					vars->deriction = (3 * M_PI) / 2;
				else if (vars->store_map[v.i][v.j] == 'S')
					vars->deriction = (M_PI) / 2;
				else if (vars->store_map[v.i][v.j] == 'E')
					vars->deriction = 0;
				else if (vars->store_map[v.i][v.j] == 'W')
					vars->deriction = M_PI;
			}
			v.j++;
		}
		v.i++;
	}
}

void	help(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->texture)
	{
		while (vars->texture[i])
		{
			free2d(vars->texture[i]);
			free(vars->texture[i]);
			i++;
		}
		free(vars->texture);
	}
	init_angle_p(vars);
	if (init_image(vars) == -1)
	{
		if (vars->store_map)
		{
			free2d(vars->store_map);
			free(vars->store_map);
		}
		exit(0);
	}
}

void	get_addr(t_vars *vars)
{
	vars->door_open.addr = mlx_get_data_addr(vars->iam[11],
			&vars->door_open.bits_per_pixel,
			&vars->door_open.line_length, &vars->door_open.endian);
	vars->door_close.addr = mlx_get_data_addr(vars->iam[12],
			&vars->door_close.bits_per_pixel,
			&vars->door_close.line_length, &vars->door_close.endian);
}

int	main(int argc, char **argv)
{
	int		i;
	t_vars	vars;

	i = 0;
	vars.position = -10;
	vars.move_p = 0;
	if (argc != 2)
		return (write(2, "ERROR :you must enter one argument\n", 35));
	init_var(&vars);
	check_file_name(argv[1]);
	if (parcer_map(&vars, argv[1]) == 0)
		help_exit(&vars);
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, vars.width_window,
			vars.height_window, "cub3d");
	take_image(&vars);
	get_addr(&vars);
	help(&vars);
	mlx_hook(vars.mlx_win, 2, 1L << 0, key_hook, &vars);
	mlx_hook(vars.mlx_win, 3, 1L << 1, kk, &vars);
	mlx_hook(vars.mlx_win, 17, 1L << 17, red_cross, &vars);
	mlx_hook(vars.mlx_win, 6, 0, mouse_callback, &vars);
	mlx_loop_hook(vars.mlx, move, &vars);
	mlx_loop(vars.mlx);
}
