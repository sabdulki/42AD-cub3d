/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:38:45 by sabdulki          #+#    #+#             */
/*   Updated: 2024/10/01 13:41:06 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

t_cub	*init_cub(void)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (NULL);
	cub->list = NULL;
	cub->map = NULL;
	return (cub);
}

t_file	*init_def_str(void)
{
	t_file	*str_node;

	str_node = malloc(sizeof(t_file));
	if (!str_node)
		return (NULL);
	str_node->type = MY_FILE;
	str_node->str = NULL;
	str_node->txtr_end = 0;
	str_node->map_start = 0;
	str_node->map_end = 0;
	str_node->next = NULL;
	// printf("%p\n", str_node);
	return (str_node);
}

t_sprite_list	*init_def_node(void)
{
	t_sprite_list	*node;

	node = malloc(sizeof(t_sprite_list));
	if (!node)
		return (NULL);
	node->type = SPRITE;
	node->sprite_name = 0;
	node->texture_path = NULL;
	node->color = NULL;
	node->head = 0;
	node->next = NULL;
	return (node);
}

t_map	*init_def_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->map = NULL;
	map->height = 0;
	map->width = 0;
	map->player_direction = 0;
	map->player_position = NULL; // pos[0] = y, pos[1] = x
	return (map);
}
