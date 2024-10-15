/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:10:15 by mrusu             #+#    #+#             */
/*   Updated: 2024/10/15 15:03:45 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	leaks()
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_map	map;

	(void)ac;
	init_default(&map);
	read_map(av[1], &map);
	execution(&map);
	clean_map(&map);
	// atexit(leaks);
	return (0);
}
