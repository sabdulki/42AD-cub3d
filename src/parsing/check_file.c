/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:47:27 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/25 18:29:39 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int format(char *map_path)
{
	int len;
	char *format_str;

	len = ft_strlen(map_path);
	format_str = ft_substr(map_path, len - 4, 4);
	if (!format_str)
		return (p_error("malloc failed"), 1);
	if (ft_strncmp(format_str, ".cub", 4) != 0)
		return (free(format_str), 1);
	else
		return (free(format_str), 0);
}

int check_file(char *map_path)
{
	if (format(map_path))
		return (p_error("invalid format of file"), 1);
	if (access(map_path, R_OK) == -1)
		return (p_error("file is inaccessible"), 1);
	printf("the file exists and the file format is correct\n");
	return (0);
}

int all_sprites_found(t_sprite_list *head)
{
	t_sprite_list *tmp;
	int i;

	i = 0;
	tmp = head;
	if (!head)
		return (0);
	while(tmp)
	{
		if (tmp->sprite_name != 0)
			i++;
		if (i == 6) //6 sprites in list
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int double_sprites(t_sprite_list *node, t_sprite_list *head)
{
	t_sprite_list *tmp;

	tmp = head;
	if (!head)
		return (0);
	while (tmp)
	{
		if (tmp->sprite_name == node->sprite_name)
			return (printf("double declaration of sprite is forbidden\n"), 1);
		tmp = tmp->next;
	}
	return (0);
}
