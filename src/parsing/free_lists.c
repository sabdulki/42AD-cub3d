/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:39:19 by sabdulki          #+#    #+#             */
/*   Updated: 2024/10/01 13:39:35 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	free_sprite_list(t_sprite_list *head)
{
	t_sprite_list	*current;
	t_sprite_list	*tmp;

	if (!head)
		return ;
	current = head;
	while (current)
	{
		tmp = current->next;
		if (current->texture_path)
			free(current->texture_path);
		if (current->color)
			free(current->color);
		free(current);
		// printf("%p\n", current);
		current = tmp;
	}
	return ;
}

void	free_file_list(t_file *head)
{
	t_file	*current;
	t_file	*tmp;

	if (!head)
		return ;
	current = head;
	while (current)
	{
		tmp = current->next;
		free(current->str);
		free(current);
		// printf("%p\n", current);
		current = tmp;
	}
	return ;
}

void	free_cub(t_cub *cub)
{
	if (!cub)
		return ;
	if (cub->list)
		free_sprite_list(cub->list);
	if (cub->map)
		free_map(cub->map);
	free(cub);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->map)
		free_split(map->map);
	if (map->player_position)
		free(map->player_position);
	free(map);
	return ;
}
