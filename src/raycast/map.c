/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruslannartdinov <ruslannartdinov@student.4 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:42:09 by ruslannartdinov   #+#    #+#             */
/*   Updated: 2024/10/22 20:07:25 by ruslannartdinov  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	set_player_position(t_data *data, int x, int y, char c)
{
	data->px = x * TEX_WIDTH + TEX_WIDTH / 2;
	data->py = y * TEX_HEIGHT + TEX_HEIGHT / 2;
	data->pa = get_angle_from_direction(c);
	data->pdx = cos(deg_to_rad(data->pa));
	data->pdy = -sin(deg_to_rad(data->pa));
	data->plane_x = -data->pdy * 0.66;
	data->plane_y = data->pdx * 0.66;
	data->cube->map->map[y][x] = '0';
}

static void	process_map_cell(t_data *data, int x, int y, int *found_player)
{
	char	c;

	c = data->cube->map->map[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (*found_player)
		{
			printf("Error: Multiple player positions in map\n");
			exit(1);
		}
		set_player_position(data, x, y, c);
		*found_player = 1;
	}
}

void	parse_map_ray(t_data *data)
{
	int	x;
	int	y;
	int	found_player;

	found_player = 0;
	y = 0;
	while (y < data->cube->map->height)
	{
		x = 0;
		while (x < data->cube->map->width)
		{
			process_map_cell(data, x, y, &found_player);
			x++;
		}
		y++;
	}
	if (!found_player)
	{
		printf("Error: Player position not found in map\n");
		exit(1);
	}
}
