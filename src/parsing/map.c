/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:16:09 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/23 17:32:04 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"


/*
	do the basic parsing of the map:
	1) no tabs, ONLY spaces, 1, 0, NEWS.
	1) NEWS only 1
	create a node and fill it with content of string
*/

// int map_ends(str)
// {
// 	if 
// }

// t_sprite_list *map_content(char *map_path)
// {
// 	int fd;
// 	char *str;
// 	t_sprite_list *node;
// 	t_sprite_list *head;

// 	head = NULL;
// 	str = NULL;
// 	fd = open(map_path, O_RDONLY);
// 	while (1) // !map end
// 	{
// 		str = get_next_line(fd);
// 		if (!str) //end of file
// 			break ;
// 		str[ft_strlen(str) - 1] = '\0';
// 		if (empty(str))
// 			continue ;
// 		if (map_ends(str))
// 			break ;
// 		node = str_content(str); //already filled node.
// 		if (node)
// 			add_node_to_list(node, &head);
// 	}
// 	if (str)
// 		free(str);
// 	// close(fd);
// 	printf("reached the map\n");
// 	return (head); //parsed linked list of info till the map
// }
