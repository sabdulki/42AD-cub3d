/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbrs_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:15:24 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/27 19:18:31 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int get_nbr_value(t_map *map_strct, int y, int x)
{
	char **map;
	
	map = map_strct->map;
	if (y >= map_strct->height || x >= map_strct->width \
		|| y < 0 || x < 0  \
		|| map[y][x] == ' ' || map[y][x] == '\0')
		return (printf("the error occured on coordinate y: %d, x: %d\n", y, x), 1);
	return (0);
}

int check_neighbours(t_map *map, int y, int x)
{
	if (get_nbr_value(map, y, x + 1) \
		|| get_nbr_value(map, y, x - 1) \
		|| get_nbr_value(map, y + 1, x) \
		|| get_nbr_value(map, y - 1, x) \
		|| get_nbr_value(map, y + 1, x + 1) \
		|| get_nbr_value(map, y + 1, x - 1) \
		|| get_nbr_value(map, y - 1, x + 1) \
		|| get_nbr_value(map, y - 1, x - 1))
		return (1);
	return (0);
}

char **allocate_2d_map(int height, int width)
{
	char **map;
	int i;

	i = 0;
	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	while (i < height)
	{
		map[i] = malloc(sizeof(char) * (width + 1));
		if (!map[i])
			return (free_split(map), NULL); //free
		map[i][width] = '\0';
		i++;
	}
	map[height] = NULL;
	printf("succesfully allocated map structure!\n");
	return (map);
}

