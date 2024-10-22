/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:48:22 by sabdulki          #+#    #+#             */
/*   Updated: 2024/10/22 18:23:15 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

t_sprite_list	*fill_sprite_node(char *s_name, char *sprite_value)
{
	t_sprite_list	*node;
	int				name;

	name = which_name(sprite_name);
	if (name == -1)
		return (printf("invalid texture name: %s\n", sprite_name), NULL);
	free(sprite_name);
	node = init_def_node();
	if (!node)
		return (NULL);
	node->sprite_name = name;
	if (is_color(sprite_value)) // the sprite is NOT color
	{
		if (access(sprite_value, R_OK) == -1)
			return (p_error("sprite path is inaccessible"), free(node), NULL);
		node->texture_path = sprite_value;
	}
	else // the sprite is COLOR
	{
		node->color = do_color(sprite_value);
		free(sprite_value);
		if (!node->color)
			return (printf("do_color() failed\n"), free(node), NULL);
	}
	return (node);
}

<<<<<<< HEAD
/* firstly check if the args are valid, 
after that assign these values to fields in a node */
t_sprite_list *str_content(char *str)
=======
/* firstly check if the args are valid,
	after that assign these values to fields in a node */
t_sprite_list	*str_content(char *str)
>>>>>>> parsing
{
	t_sprite_list	*node;
	char			**sprites;

	// printf("the str is: '%s'\n", str);
	sprites = ft_split(str, ' ');
	if (!sprites || !sprites[0] || !sprites[1])
		return (printf("invalid arguments\n"), free_split(sprites), NULL);
	// for (int i = 0; sprites[i]; i++)
	// 	printf("\tsprites %d: '%s'\n", i, sprites[i]);
	node = fill_sprite_node(sprites[0], sprites[1]);
	free(sprites);
	if (!node)
		return (printf("failed to create node\n"), NULL);
	return (node);
}

t_sprite_list	*fill_sprites(t_file *file)
{
	t_file			*tmp;
	t_sprite_list	*node;
	t_sprite_list	*head;

	head = NULL;
	tmp = file;
	while (tmp && !all_sprites_found(head))
	{
		if (!empty(tmp->str))
		{
			node = str_content(tmp->str); // already filled node.
			if (!node)
				return (free_sprite_list(head), NULL);
			if (!double_sprites(node, head))
				add_node_to_list(node, &head);
			else
				return (free_sprite_list(head), free_sprite_list(node), NULL);
		}
		tmp = tmp->next;
	}
	if (!tmp)
		return (printf("no map!\n"), free_sprite_list(head), NULL);
	tmp->txtr_end = 1;
	return (head);
}
