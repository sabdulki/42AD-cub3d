/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:48:22 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/24 20:29:47 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

t_sprite_list *fill_sprite_node(char *sprite_name, char *sprite_value)
{
	t_sprite_list *node;
	int name;

	node = init_def_node();
	if (!node)
		return (NULL);
	name = which_name(sprite_name);
	if (name == -1)
		return (printf("invalid texture name: %s\n", sprite_name), free(node), NULL);
	node->sprite_name = name;
	if (is_color(sprite_value)) //the sprite is NOT color
	{
		// if (access(sprite_value, R_OK) == -1)
		// 	return (p_error("sprite path is inaccessible"), free(node), NULL);
		node->texture_path = sprite_value;
	}
	else //the sprite is COLOR
	{
		node->color = do_color(sprite_value);
		if (!node->color)
			return (printf("do_color() failed\n"), free(node), NULL);
	}
	return (node);
}

/* firstly check if the args are valid, after that assign these values to fields in a node */
t_sprite_list *str_content(char *str)
{
	t_sprite_list *node;
	char **sprites;

	// printf("the str is: '%s'\n", str);
	sprites = ft_split(str, ' ');
	if (!sprites || !sprites[0] || !sprites[1])
		return (printf("invalid arguments\n"), NULL);
	// for (int i = 0; sprites[i]; i++)
	// 	printf("\tsprites %d: '%s'\n", i, sprites[i]);
	node = fill_sprite_node(sprites[0], sprites[1]);
	if (!node)
		return (printf("failed to create node\n"), NULL);
	return (node);
}

t_sprite_list *fill_sprites(t_file *file)
{
	t_file *tmp;
	t_sprite_list *node;
	t_sprite_list *head;

	head = NULL;
	tmp = file;
	while (tmp && !all_sprites_found(head))
	{
		node = str_content(tmp->str); //already filled node.
		if (!node)
			return (free_sprite_list(head), NULL);
		if (!double_sprites(node, head))
			add_node_to_list(node, &head);
		else
			return (free_sprite_list(head), NULL);
		tmp = tmp->next;
	}
	return (head);
}

/* will return filled list with textures and char** map.
everything will be alreday parsed */
t_cub *file_content(t_file *file)
{
	// go through file linked list. 
	// fill sprite linked list with alreday parsed data
	// parse map
	// fill char **map with alreday parsed data

	t_cub *cub;

	cub = init_cub();
	cub->list = fill_sprites(file);
	if (!cub->list)
		return(free_file_list(file), NULL);
	// cub->map = parse_map(file);
	// if  (!cub->map)
	// 	return(free_file_list(file), NULL);
	return (cub);
}

t_file *overwrite_file(char *file_path)
{
	int fd;
	char *str;
	t_file *str_node;
	t_file *head;

	head = NULL;
	str = NULL;
	fd = open(file_path, O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)                                //end of file
			break ;
		str[ft_strlen(str) - 1] = '\0';          //replace '\n' with '\0'
		if (!empty(str))
		{
			str_node = init_def_str(); 				 //free
			if (!str_node)
				return (free(str), free_file_list(head), NULL);
			str_node->str = str;
			add_node_to_file(str_node, &head);
		}
		else	
			free(str);
	}
	close(fd);
	return (head);
}
