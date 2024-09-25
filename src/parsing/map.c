/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:16:09 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/25 21:33:49 by sabdulki         ###   ########.fr       */
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

	height = 0;
	while(start)
	{
		height++;
		start = start->next;
	}
	// printf("height: %d\n", height);
	return (height);
}


//1) find the start of the map ->
	// i can use either map_starts() function or txtr_end flag 	
//2) while loop stops after last line of the map ->
	//does it mean that i can just reach the end of linked list,
	//as i alredau removed all empty lines?
//3) how many lines does the map have
//4)allocate memory for char ** with size of map
char **parse_map(t_file *file)
{
	t_file *tmp;
	int height;
	char **map;

	map = NULL;
	tmp = file;
	while (tmp && !tmp->txtr_end) //reach the expected start of the map
		tmp = tmp->next;
	if (!map_starts(tmp->str)) //cause this line MUST be map start
		return (printf("invalid file!\n"), NULL);
	// printf("map start: '%s'\n", tmp->str);
	height = calculate_height(tmp);
	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
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
