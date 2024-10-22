/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:16:09 by sabdulki          #+#    #+#             */
/*   Updated: 2024/10/22 17:45:33 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int fill_player_info(t_map *map, int y, int x)
{
	if (!nsew(map->map[y][x]))
		return (0);
	if (map->player_direction != 0)
		return (printf("cannot be more than 1 player. y: %d, x: %d\n", y, x), 1);
	map->player_direction = map->map[y][x];
	map->player_position = malloc(sizeof(int) * 2);
	if (!map->player_position)
		return (1);
	map->player_position[0] = y;
	map->player_position[1] = x;
	printf("the player direction is: %c\n", map->player_direction);
	printf("the player position is: y: %d, x: %d\n", map->player_position[0], map->player_position[1]);
	return (0);
}

char **fill_2d_map(t_file *map_start, t_map *map, char **map_2d)
{
	int y;
	int x;
	
	if (!map_2d)
		return (NULL);
	y = 0;
    while (map_start && y < map->height) 
	{
        x = 0;
        while (x < map->width && map_start->str[x] != '\0')
		{
			if (invalid_char(map_start->str[x]))
				return (printf("invalid char in map\n"), free_split(map_2d), NULL);
            map_2d[y][x] = map_start->str[x];
            x++;
        }
        while (x < map->width) 
		{
			map_2d[y][x] = ' ';
            x++;
        }
        map_start = map_start->next;
        y++;
    }
	// printf("succesfully filled 2d map!\n");
	return map_2d;
}

t_map *fill_map(t_file *file)
{
	t_map *map;
	t_file *map_start;

	map_start = get_start(file);
	map = init_def_map();
	if (!map)
		return (NULL);
	map->height = calculate_height(map_start);
	map->width = calculate_width(map_start);
	map->map = fill_2d_map(map_start, map, allocate_2d_map(map->height, map->width));
	if (!map->map)
		return (free_map(map), NULL);
	return (map);
}

int parse_map(t_map *map)
{
	int x;
	int y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] != '1' && map->map[y][x] != ' ' && map->map[y][x] != '\0') //for now only 0 and NEWS
			{
				// printf("the char: %c. y: %d, x: %d\n", map->map[y][x], y, x);
				if (check_neighbours(map, y, x)) //returned 1
					return (printf("invalid map\n"), 1);
				if (fill_player_info(map, y, x))
					return (1);
			}
			x++;
		}
		y++;
	}
	if (map->player_direction == 0)
		return (1);
	printf("the map is purely valid!\n");
	return (0);
}

t_map *do_map(t_file *file)
{
	t_map *map;

	if (where_map(file))
		return (NULL);
	map = fill_map(file);
	if (!map)
		return (NULL);
	print_map(map);
	if (parse_map(map))
		return (free_map(map), NULL);
	return (map);
}
