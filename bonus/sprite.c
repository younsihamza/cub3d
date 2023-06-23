/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:43:07 by hyounsi           #+#    #+#             */
/*   Updated: 2023/06/23 18:43:20 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_aim_image(void)
{
	int	fd[11];
	int	i;

	i = 0;
	fd[0] = open("aim/AnyConv.com__hk53_aim.1.xpm", O_RDONLY);
	fd[1] = open("aim/AnyConv.com__hk53_aim.2.xpm", O_RDONLY);
	fd[2] = open("aim/AnyConv.com__hk53_aim.3.xpm", O_RDONLY);
	fd[3] = open("aim/AnyConv.com__hk53_aim.4.xpm", O_RDONLY);
	fd[4] = open("aim/AnyConv.com__hk53_aim.5.xpm", O_RDONLY);
	fd[5] = open("aim/AnyConv.com__hk53_aim.6.xpm", O_RDONLY);
	fd[6] = open("aim/AnyConv.com__hk53_aim.7.xpm", O_RDONLY);
	fd[7] = open("aim/AnyConv.com__hk53_aim.9.xpm", O_RDONLY);
	fd[8] = open("aim/AnyConv.com__hk53_aim.11.xpm", O_RDONLY);
	fd[9] = open("aim/fire.xpm", O_RDONLY);
	fd[10] = open("aim/fire1.xpm", O_RDONLY);
	while (i < 11)
	{
		if (fd[i] < 0)
			exit(0);
		close(fd[i]);
		i++;
	}
}

void	help_take_image(t_vars *vars)
{
	vars->iam[0] = mlx_xpm_file_to_image(vars->mlx,
			"aim/AnyConv.com__hk53_aim.1.xpm", &vars->weapen.width,
			&vars->n_image.height);
	vars->iam[1] = mlx_xpm_file_to_image(vars->mlx,
			"aim/AnyConv.com__hk53_aim.2.xpm", &vars->weapen.width,
			&vars->n_image.height);
	vars->iam[2] = mlx_xpm_file_to_image(vars->mlx,
			"aim/AnyConv.com__hk53_aim.3.xpm", &vars->weapen.width,
			&vars->n_image.height);
	vars->iam[3] = mlx_xpm_file_to_image(vars->mlx,
			"aim/AnyConv.com__hk53_aim.4.xpm", &vars->weapen.width,
			&vars->n_image.height);
	vars->iam[4] = mlx_xpm_file_to_image(vars->mlx,
			"aim/AnyConv.com__hk53_aim.5.xpm", &vars->weapen.width,
			&vars->n_image.height);
	vars->iam[5] = mlx_xpm_file_to_image(vars->mlx,
			"aim/AnyConv.com__hk53_aim.6.xpm", &vars->weapen.width,
			&vars->n_image.height);
	vars->iam[6] = mlx_xpm_file_to_image(vars->mlx,
			"aim/AnyConv.com__hk53_aim.7.xpm", &vars->weapen.width,
			&vars->n_image.height);
}

void	take_image(t_vars *vars)
{
	int	i;

	i = 0;
	check_aim_image();
	vars->iam = ft_calloc(sizeof(void *), 11);
	help_take_image(vars);
	vars->iam[7] = mlx_xpm_file_to_image(vars->mlx,
			"aim/AnyConv.com__hk53_aim.9.xpm", &vars->weapen.width,
			&vars->n_image.height);
	vars->iam[8] = mlx_xpm_file_to_image(vars->mlx,
			"aim/AnyConv.com__hk53_aim.11.xpm", &vars->weapen.width,
			&vars->n_image.height);
	vars->iam[9] = mlx_xpm_file_to_image(vars->mlx, "aim/fire.xpm",
			&vars->weapen.width, &vars->n_image.height);
	vars->iam[10] = mlx_xpm_file_to_image(vars->mlx, "aim/fire1.xpm",
			&vars->weapen.width, &vars->n_image.height);
	while (i < 11)
	{
		if (vars->iam[i] == NULL)
		{
			free(vars->iam);
			exit(0);
		}
		i++;
	}
}
