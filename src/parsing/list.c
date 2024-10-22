/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:59:22 by sabdulki          #+#    #+#             */
/*   Updated: 2024/10/01 13:40:50 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	add_node_to_file(t_file *node, t_file **head)
{
	t_file	*current;
	t_file	*new_node;

	// int			i_list;
	// i_list = modify_static_int(SET);
	new_node = node;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (!*head)
	{
		*head = new_node;
		// new_node->head = 1;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		// new_node->head = 0;
		current->next = new_node;
		new_node->prev = current;
	}
	// new_cmd->index = i_list;
	return ;
}

void	add_node_to_list(t_sprite_list *node, t_sprite_list **head)
{
	t_sprite_list	*current;
	t_sprite_list	*new_node;

	// int			i_list;
	// i_list = modify_static_int(SET);
	new_node = node;
	new_node->next = NULL;
	if (!*head)
	{
		*head = new_node;
		new_node->head = 1;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		new_node->head = 0;
		current->next = new_node;
	}
	// new_cmd->index = i_list;
	return ;
}
