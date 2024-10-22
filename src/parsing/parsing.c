/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:43:07 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/27 19:34:37 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

t_cub	*parsing(char *file_path)
{
	t_file	*file;
	t_cub	*cub;

	if (check_file(file_path))
		return (NULL);
	file = overwrite_file(file_path);
	if (!file)
		return (NULL);
	// print_file_strct(file);
	cub = file_content(file);
	free_file_list(file);
	if (!cub)
		return (NULL);
	// print_sprite_list(cub->list);
	return (cub);
}

/* will return filled list with textures and char** map.
everything will be alreday parsed */
t_cub	*file_content(t_file *file)
{
	t_cub	*cub;

	// go through file linked list.
	// fill sprite linked list with alreday parsed data
	// parse map
	// fill char **map with alreday parsed data
	cub = init_cub();
	if (!cub)
		return (NULL);
	cub->list = fill_sprites(file);
	if (!cub->list)
		return (free_cub(cub), NULL);
	cub->map = do_map(file);
	if (!cub->map)
		return (free_cub(cub), NULL);
	return (cub);
}

t_file	*overwrite_file(char *file_path)
{
	int		fd;
	char	*str;
	t_file	*str_node;
	t_file	*head;

	head = NULL;
	str = NULL;
	fd = open(file_path, O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (!str) // end of file
			break ;
		if (str[ft_strlen(str) - 1] == '\n')
			str[ft_strlen(str) - 1] = '\0'; // replace '\n' with '\0'
		if (tabs(str))
			return (free(str), free_file_list(head), NULL);
		str_node = init_def_str(); // free
		if (!str_node)
			return (free(str), free_file_list(head), NULL);
		str_node->str = str;
		add_node_to_file(str_node, &head);
	}
	close(fd);
	return (head);
}
