/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:41:07 by hyounsi           #+#    #+#             */
/*   Updated: 2023/06/22 22:41:07 by hyounsi          ###   ########.fr       */
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
	create_image(vars);
	while (vars->store_map[v.i] != NULL)
	{
		v.j = 0;
		while (vars->store_map[v.i][v.j])
		{
			print_2d_map(vars, v.i, v.j);
			if (v.j == (int)vars->player_x / (vars->size)
				&& v.i == (int)vars->player_y / (vars->size))
			{
				print_player(vars);
				simple_draw(vars, &v);
			}
			v.j++;
		}
		v.i++;
	}
	put_destroy_image(vars);
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
void  sprite_move(t_vars *vars)
{
	if (vars->fire == 1)
	{
		while(vars->n < 9)
		{
			mlx_put_image_to_window(vars->mlx,vars->mlx_win,vars->iam[vars->n],-320,-180);
			vars->n++;
		}
		if(vars->n == 9)
		{
			vars->position += 1;
				mlx_put_image_to_window(vars->mlx,vars->mlx_win,vars->iam[8],-320 ,- 180 + vars->position);
				mlx_put_image_to_window(vars->mlx,vars->mlx_win,vars->iam[9 + abs(vars->position)%2],vars->width_window/2 -40 ,vars->height_window/2 + vars->position);
			if(vars->position == 10)
					vars->position = -10;	
		}
	}
	else if(vars->scop == 1)
	{
		while(vars->n < 9)
			{
				mlx_put_image_to_window(vars->mlx,vars->mlx_win,vars->iam[vars->n],-320,-180);
				vars->n++;
			}
			if(vars->n == 9)
					mlx_put_image_to_window(vars->mlx,vars->mlx_win,vars->iam[8],-320 ,- 180 );
	}
	else
	{
		vars->position = -10;
		vars->n = 0;
		if(vars->move_p > 4)
			vars->move_p = 0;
		mlx_put_image_to_window(vars->mlx,vars->mlx_win,vars->iam[vars->move_p],-200,-20);
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
	sprite_move(vars);
	return (0);
}
