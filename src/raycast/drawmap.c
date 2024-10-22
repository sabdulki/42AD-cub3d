/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruslannartdinov <ruslannartdinov@student.4 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:41:51 by ruslannartdinov   #+#    #+#             */
/*   Updated: 2024/10/22 19:48:44 by ruslannartdinov  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"
#include <stdlib.h>

void	draw_square(t_data *data, t_point position, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_pixel_put(data->mlx, data->win,
				position.x + i, position.y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_map_2d_ray(t_data *data, t_map *map)
{
	int		x;
	int		y;
	int		color;
	t_point	position;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == '1')
				color = 0xFFFFFF;
			else
				color = 0x000000;
			position.x = x * map->width + 1;
			position.y = y * map->height + 1;
			draw_square(data, position, map->width - 2, color);
			x++;
		}
		y++;
	}
}
