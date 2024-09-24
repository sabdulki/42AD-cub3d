/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:59:22 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/24 20:57:11 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

t_cub *init_cub()
{
	t_cub *cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (NULL);
	cub->list = NULL;
	cub->list = NULL;
	return (cub);
}

t_file *init_def_str(void)
{
	t_file *str_node;

	str_node = malloc(sizeof(t_file));
	if (!str_node)
		return (NULL);
	str_node->type = MY_FILE;
	str_node->str = NULL;
	str_node->next = NULL;
	// printf("%p\n", str_node);
	return (str_node);
}

t_sprite_list *init_def_node(void)
{
	t_sprite_list *node;
	
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

void free_sprite_list(t_sprite_list *head)
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

void free_file_list(t_file *head)
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

void free_cub(t_cub *cub)
{
	free_sprite_list(cub->list);
	if (cub->map)
		free(cub->map);
	free(cub);
}

