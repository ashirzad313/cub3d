/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:42:12 by ashirzad          #+#    #+#             */
/*   Updated: 2024/10/14 18:28:13 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	game_loop(void *pointer)
{
	t_data *data = (t_data *)pointer;

	mlx_delete_image(data->mlx, data->img);
	mlx_new_image(data->mlx, data->map->res_x, data->map->res_y);
	hook(data, 0, 0);
	cast_rays(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

void	init_player(t_data *data)
{
	data->ply = malloc(sizeof(t_player));
	data->ply->rot = 0;
	data->ply->horz = 0;
	data->ply->vert = 0;
	data->ply->plyr_x = (data->map->player_x * SQAURE_SIZE) + (SQAURE_SIZE / 2);
	data->ply->plyr_y = (data->map->player_y * SQAURE_SIZE) + (SQAURE_SIZE / 2);
	data->ply->fov_rd = (FOV * M_PI) / 180;
	if (data->map->p == 'N')
		data->ply->angle = 3 * M_PI / 2;
	else if (data->map->p == 'S')
		data->ply->angle = M_PI / 2;
	else if (data->map->p == 'W')
		data->ply->angle = M_PI;
	else if (data->map->p == 'E')
		data->ply->angle = 0;
}

void	execution(t_map *map)
{
	t_data	data;

	data.map = map;
	data.mlx = mlx_init(map->res_x, map->res_y, "Wolfenstein 42", 1);
	init_player(&data);
	mlx_key_hook(data.mlx, key_hook, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
}
