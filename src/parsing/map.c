/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:16:09 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/26 17:14:48 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*
	do the basic parsing of the map:
	1) no tabs, ONLY spaces, 1, 0, NEWS.
	1) NEWS only 1
	create a node and fill it with content of string
*/

int calculate_height(t_file *start)
{
	int height;
	t_file *tmp;

	height = 0;
	tmp = start;
	while (tmp)
	{
		height++;
		tmp = tmp->next;
	}
	// printf("height: %d\n", height);
	return (height);
}

int calculate_width(t_file *start)
{
	size_t width;
	t_file *tmp;
	
	width = ft_strlen(start->str);
	tmp = start;
	while (tmp)
	{
		if (ft_strlen(tmp->str) > width)
			width = ft_strlen(tmp->str);
		tmp = tmp->next;
	}
	// printf("width: %ld\n", width);
	return (width);
}

// check corners,
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
        while (map_start->str[x] != '\0' && x < map->width) // && corners_valid()
		{
            map_2d[y][x] = map_start->str[x];
            x++;
        }
        while (x < map->width) {
            map_2d[y][x] = ' ';
            x++;
        }
        map_start = map_start->next;
        y++;
    }
	printf("succesfully filled 2d map!\n");
	return map_2d;
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

int print_map(t_map *map)
{
	int x;
	int y;

	y = 0;
	if (!map || !map->map)
		return (printf("no map!\n"), 1);
	while (map->map[y] && y < map->height) 
	{
        x = 0;
        while (x < map->width) // && corners_valid()
		{
            printf("%c", map->map[y][x]);
            x++;
        }
		printf("\n");
        y++;
    }
	return (0);
}

t_map *fill_map(t_file *map_start)
{
	t_map *map;

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

t_file *where_map(t_file *file)
{
	t_file *tmp;

	tmp = file;
	while (tmp && !tmp->txtr_end) //reach the expected start of the map
		tmp = tmp->next;
	if (!map_starts(tmp->str)) //because this line MUST be map start
		return (printf("invalid file!\n"), NULL);
	// printf("map start: '%s'\n", map_start->str);
	return (tmp);
}


//1) find the start of the map ->
	// i can use either map_starts() function or txtr_end flag 	
//2) while loop stops after last line of the map ->
	//does it mean that i can just reach the end of linked list,
	//as i alredau removed all empty lines?
//3) how many lines does the map have
//4)allocate memory for char ** with size of map
t_map *parse_map(t_file *file)
{
	t_file *map_start;
	t_map *map;

	map_start = where_map(file);
	if (!map_start)
		return (NULL);
	map = fill_map(map_start);
	if (!map)
		return (NULL);
	print_map(map);
	return (map);
}

int map_starts(char *str)
{
    int i = 0;

	if (!str)
		return (0);
    while (str[i] && str[i] == ' ')
        i++;
    // The string must contain at least one '1'
    if (str[i] != '1')
        return (0);
    while (str[i])
    {
        // The string must only contain '1' or spaces
        if (str[i] != '1' && str[i] != ' ')
            return (0);
        i++;
    }

    return (1);  // The string is valid as a map start
}
