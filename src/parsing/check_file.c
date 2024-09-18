/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:47:27 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/18 17:27:32 by sabdulki         ###   ########.fr       */
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
		return (perror("malloc failed"), 1);
	if (ft_strncmp(format_str, ".cub", 4) != 0)
		return (free(format_str), 1);
	else
		return (free(format_str), 0);
}

int check_file(char *map_path)
{
	if (format(map_path))
		return (perror("invalid format of file"), 1);
	if (access(map_path, R_OK) == -1)
		return (perror("file is inaccessible"), 1);
	printf("the file exists and the file format is correct\n");
	return (0);
}
