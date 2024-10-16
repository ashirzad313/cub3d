/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:26:39 by ashirzad          #+#    #+#             */
/*   Updated: 2024/10/15 15:27:37 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	find_wall(t_data *data, float x,  float y)
{
	int	x_step;
	int	y_step;

	x_step = floor(x / SQAURE_SIZE);
	y_step = floor(y / SQAURE_SIZE);

	if (data->map->map_data[y_step] && data->map->map_data[y_step][x_step])
		if (data->map->map_data[y_step][x_step] != '1')
			return (1);
	return (0);
}

float	ft_h_ray(t_data *data)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;
	int		unit_circle;

	unit_circle = 0;
	y_step = SQAURE_SIZE;
	x_step = SQAURE_SIZE / tan(data->ray->ray_ngl);
	h_y = floor(data->ply->plyr_y / SQAURE_SIZE) * SQAURE_SIZE;
	pixel = inter_check(data->ray->ray_ngl, &h_y, &y_step, 1);
	h_x = data->ply->plyr_x + (h_y - data->ply->plyr_y) / tan(data->ray->ray_ngl);
	if (data->ray->ray_ngl > (M_PI / 2) && data->ray->ray_ngl < (3 * M_PI) / 2)
		unit_circle = 1;
	if ((unit_circle && x_step > 0) || \
		(!unit_circle && x_step < 0))
		x_step *= -1;
	while (find_wall(data, h_x, h_y - pixel))
	{
		h_x += x_step;
		h_y += y_step;
	}
	data->ray->horiz_x = h_x;
	data->ray->horiz_y = h_y;
	return (sqrt(pow(h_x - data->ply->plyr_x, 2) + \
	pow(h_y - data->ply->plyr_y, 2)));
}

float	ft_v_ray(t_data *data)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;
	int		unit_circle;

	unit_circle = 0;
	y_step = SQAURE_SIZE;
	x_step = SQAURE_SIZE / tan(data->ray->ray_ngl);
	v_x = floor(data->ply->plyr_x / SQAURE_SIZE) * SQAURE_SIZE;
	pixel = inter_check(data->ray->ray_ngl, &v_x, &x_step, 0);
	v_y = data->ply->plyr_y + (v_x - data->ply->plyr_x) / tan(data->ray->ray_ngl);
	if (data->ray->ray_ngl > 0 && data->ray->ray_ngl < M_PI)
		unit_circle = 1;
	if ((unit_circle && x_step > 0) || \
		(!unit_circle && x_step < 0))
		x_step *= -1;
	while (find_wall(data, v_x - pixel, v_y))
	{
		v_x += x_step;
		v_y += y_step;
	}
	data->ray->vert_x = v_x;
	data->ray->vert_y = v_y;
	return (sqrt(pow(v_x - data->ply->plyr_x, 2) + \
	pow(v_y - data->ply->plyr_y, 2)));
}

void	cast_rays(t_data *data)
{
	double	h_ray;
	double	v_ray;
	int		ray;

	ray = 0;
	data->ray = malloc(sizeof(t_ray));
	data->ray->ray_ngl = data->ply->angle - (data->ply->fov_rd / 2);
	while (ray < data->map->res_x)
	{
		if (data->ray->ray_ngl < 0)
			data->ray->ray_ngl += 2 * M_PI;
		else if (data->ray->ray_ngl > 2 * M_PI)
			data->ray->ray_ngl -= 2 * M_PI;
		h_ray = ft_h_ray(data);
		v_ray = ft_v_ray(data);
		printf("px = %d  py = %d\n", data->ply->plyr_x / SQAURE_SIZE, data->ply->plyr_y / SQAURE_SIZE);
		printf("h_ray = %f\n", h_ray);
		printf("v_ray = %f\n", v_ray);
		if (h_ray > v_ray)
		{
			data->ray->distance = h_ray;
			data->ray->flag = 1;
		}
		else
			data->ray->distance = v_ray;
		ray++;
		data->ray->ray_ngl += (data->ply->fov_rd / data->map->res_x);
	}
}
