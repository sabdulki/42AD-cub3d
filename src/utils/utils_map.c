/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:26:54 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/27 19:35:48 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int calculate_height(t_file *start)
{
	int height;
	t_file *tmp;

	height = 0;
	tmp = start;
	while (tmp)
	{
		height++;
		if (tmp->map_end == 1)
			break ;			
		tmp = tmp->next;
	}
	// printf("height: %d\n", height);
	// printf("the last line of map: %s\n", tmp->str);
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

int invalid_char(int c)
{
	return (c != '1' && c != '0' && c != ' ' \
		&& c != 'N' && c != 'S' && c != 'E' && c != 'W');
}

int nsew(int c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
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
