/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_parcer_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:49:24 by hyounsi           #+#    #+#             */
/*   Updated: 2023/06/21 17:49:25 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_floor_c(t_vars *vs, t_var *v)
{
	if (ft_strcmp(vs->texture[v->i][0], "F") == 0)
	{
		v->arr = ft_split(vs->texture[v->i][1], ',');
		if (ft_strlen2d(v->arr) != 3)
		{
			if (v->arr)
			{
				free2d(v->arr);
				free(v->arr);
			}
			return (-1);
		}
		vs->color_floor = create_trgb(0, ft_atoi(v->arr[0]), ft_atoi(v->arr[1]),
				ft_atoi(v->arr[2]));
		if (v->arr)
		{
			free2d(v->arr);
			free(v->arr);
		}
	}
	return (0);
}

int	get_ceil_c(t_vars *vs, t_var *v)
{
	if (ft_strcmp(vs->texture[v->i][0], "C") == 0)
	{
		v->j = 0;
		v->arr = ft_split(vs->texture[v->i][1], ',');
		if (ft_strlen2d(v->arr) != 3)
		{
			if (v->arr)
			{
				free2d(v->arr);
				free(v->arr);
			}
			return (-1);
		}
		vs->color_ceil = create_trgb(0, ft_atoi(v->arr[0]), ft_atoi(v->arr[1]),
				ft_atoi(v->arr[2]));
		if (v->arr)
		{
			free2d(v->arr);
			free(v->arr);
		}
	}
	return (0);
}
