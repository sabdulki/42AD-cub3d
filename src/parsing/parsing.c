/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:43:07 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/25 20:17:01 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

t_cub *parsing(char *file_path)
{
	t_file *file;
	t_cub *cub;

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
	print_sprite_list(cub->list);
	return (cub);
}
