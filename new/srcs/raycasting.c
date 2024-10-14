/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:20:02 by ashirzad          #+#    #+#             */
/*   Updated: 2024/10/14 18:20:32 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += SQAURE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += SQAURE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	get_h_inter(t_data *data, float angle)
{
	float	x_step;
	float	y_step;
	float	h_x;
	float	h_y;
	int		pixel;

	y_step = SQAURE_SIZE;
	x_step = SQAURE_SIZE / tan(angle);
	h_y = floor(data->ply->plyr_y / SQAURE_SIZE) * SQAURE_SIZE;
	h_x = data->ply->plyr_x + (h_y - data->ply->plyr_y) / tan(angle);
	pixel = inter_check(angle, &h_y, &y_step, 1);
	return (0);
}

int	get_v_inter(t_data *data, float angle)
{
	float	x_step;
	float	y_step;
	float	h_x;
	float	h_y;
	int		pixel;

	y_step = SQAURE_SIZE;
	x_step = SQAURE_SIZE / tan(angle);
	h_y = floor(data->ply->plyr_y / SQAURE_SIZE) * SQAURE_SIZE;
	h_x = data->ply->plyr_x + (h_y - data->ply->plyr_y) / tan(angle);
	pixel = inter_check(angle, &h_y, &y_step, 1);
	return (0);
}

void	cast_rays(t_data *data)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	data->ray = malloc(sizeof(t_ray));
	while (ray < data->map->res_x)
	{
		data->ray->flag = 0;
		h_inter = get_h_inter(data, nor_angle(data->ray->ray_ngl));
		v_inter = get_v_inter(data, nor_angle(data->ray->ray_ngl));
		if (v_inter <= h_inter)
			data->ray->distance = v_inter;
		else
		{
			data->ray->distance = h_inter;
			data->ray->flag = 1;
		}
		ray++;
	}
}
