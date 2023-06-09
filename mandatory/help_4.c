/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:41:07 by hyounsi           #+#    #+#             */
/*   Updated: 2023/07/12 10:55:54 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	h_plane(t_vars *vars, t_var *v)
{
	vars->plane_des_h = vars->plane_des_h * cos(v->angle * (M_PI / 180));
	vars->plane_height = (vars->size / vars->plane_des_h) * v->p_d;
	vars->xi = v->r;
	vars->yi = ((vars->height_window) / 2 - (vars->plane_height) / 2);
	vars->xf = v->r;
	vars->yf = (vars->height_window) / 2 + (vars->plane_height) / 2;
	if (sin(vars->deriction + v->angle * (M_PI / 180)) < 0)
	{
		v->offset = (int)((fmod(vars->plane_x_h, vars->size)
					/ vars->size) * vars->n_image.width);
		ber(vars, v->offset, &vars->n_image);
	}
	else
	{
		v->offset = (int)((1 - (fmod(vars->plane_x_h, vars->size) / vars->size))
				* vars->s_image.width);
		ber(vars, v->offset, &vars->s_image);
	}
}

void	simple_draw(t_vars *vars, t_var *v)
{
	v->r = 0;
	v->p_d = ((vars->width_window) / 2) / tan(30 * (M_PI / 180));
	v->angle = -30;
	v->pas = 60.0 / vars->width_window;
	while (v->r < (vars->width_window))
	{
		ft_step_h(vars, vars->deriction + v->angle * (M_PI / 180));
		ft_steps_v(vars, vars->deriction + v->angle * (M_PI / 180));
		if (vars->plane_des_h >= vars->plane_des_v)
			v_plane(vars, v);
		else
			h_plane(vars, v);
		vars->xi = v->r;
		vars->yf = ((vars->height_window) / 2 - (vars->plane_height) / 2);
		vars->xf = v->r;
		vars->yi = 0;
		ber_floor_ceil(vars, vars->color_ceil);
		vars->xi = v->r;
		vars->yi = (vars->height_window) / 2 + (vars->plane_height) / 2;
		vars->xf = v->r;
		vars->yf = vars->height_window;
		ber_floor_ceil(vars, vars->color_floor);
		v->angle += v->pas;
		v->r++;
	}
}

int	ft_draw(t_vars *vars)
{
	t_var	v;

	v.i = 0;
	mlx_clear_window(vars->mlx, vars->mlx_win);
	vars->main_image.img = mlx_new_image(vars->mlx, vars->width_window,
			vars->height_window);
	vars->main_image.addr = mlx_get_data_addr(vars->main_image.img,
			&vars->main_image.bits_per_pixel, &vars->main_image.line_length,
			&vars->main_image.endian);
	simple_draw(vars, &v);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->main_image.img, 0,
		0);
	mlx_destroy_image(vars->mlx, vars->main_image.img);
	return (0);
}

void	help_move(t_vars *vars)
{
	if (vars->up == 1 || vars->f_up == 1)
	{
		if (check_pixel(vars, 0, cos(vars->deriction) * vars->speed) == 0)
			vars->player_x += cos(vars->deriction) * vars->speed;
		if (check_pixel(vars, sin(vars->deriction) * vars->speed, 0) == 0)
			vars->player_y += sin(vars->deriction) * vars->speed;
	}
	if ((vars->right == 1) && check_pixel(vars, sin(vars->deriction + (M_PI
					/ 2)) * vars->speed, cos(vars->deriction + (M_PI / 2))
			* vars->speed) == 0)
	{
		vars->player_x += cos(vars->deriction + (M_PI / 2)) * vars->speed;
		vars->player_y += sin(vars->deriction + (M_PI / 2)) * vars->speed;
	}
	if ((vars->left == 1) && check_pixel(vars, sin(vars->deriction - (M_PI / 2))
			* vars->speed, cos(vars->deriction - (M_PI / 2))
			* vars->speed) == 0)
	{
		vars->player_x += cos(vars->deriction - (M_PI / 2)) * vars->speed;
		vars->player_y += sin(vars->deriction - (M_PI / 2)) * vars->speed;
	}
}

int	move(t_vars *vars)
{
	if (vars->f_right == 1)
		vars->deriction += 0.08;
	if (vars->f_left == 1)
		vars->deriction -= 0.08;
	help_move(vars);
	if (vars->down == 1 || vars->f_down == 1)
	{
		if (check_pixel(vars, 0, -cos(vars->deriction) * vars->speed) == 0)
			vars->player_x -= cos(vars->deriction) * vars->speed;
		if (check_pixel(vars, -sin(vars->deriction) * vars->speed, 0) == 0)
			vars->player_y -= sin(vars->deriction) * vars->speed;
	}
	ft_draw(vars);
	return (0);
}
