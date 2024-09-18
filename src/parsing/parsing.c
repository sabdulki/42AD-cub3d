/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:43:07 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/18 17:27:28 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int parsing(char *map_path)
{
	if (check_file(map_path))
		return (1);
	if (file_content(map_path))
		return (1);
	return (0);
}
