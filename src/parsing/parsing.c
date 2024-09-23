/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:43:07 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/23 18:33:00 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int parsing(char *file_path)
{
	t_sprite_list *sprite_list;
	t_file *file;

	sprite_list = NULL;
	if (check_file(file_path))
		return (1);
	file = overwrite_file(file_path);
	print_file_strct(file);
	// sprite_list = file_content(file);
	// if (!sprite_list)
	// 	return (1);
	// print_sprite_list(sprite_list);
	return (0);
}
