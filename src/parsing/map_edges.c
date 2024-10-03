/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_edges.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:08:42 by sabdulki          #+#    #+#             */
/*   Updated: 2024/10/01 13:31:59 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	where_map(t_file *file)
{
	t_file	*tmp;

	tmp = file;
	while (tmp && !tmp->txtr_end) // reach the expected start of the map
		tmp = tmp->next;
	while (tmp && empty(tmp->str))
		tmp = tmp->next;
	if (!map_top_bottom(tmp)) // because this line MUST be map start
		return (printf("invalid map!\n"), 1);
	tmp->map_start = 1;
	printf("map start: '%s'\n", tmp->str);
	while (tmp && !map_end(tmp))
		tmp = tmp->next;
	if (tmp && map_top_bottom(tmp))
		tmp->map_end = 1;
	else
		return (printf("invalid map!\n"), 1);
	printf("map end: '%s'\n", tmp->str);
	if (tmp && tmp->map_start && tmp->map_end)
		return (printf("start and end are at the same line\n"), 1);
	tmp = tmp->next;
	while (tmp) // check if there is smth after map
	{
		if (!empty(tmp->str))
			return (printf("has smth after map\n"), 1);
		tmp = tmp->next;
	}
	return (0);
}

int	map_top_bottom(t_file *node)
{
	int		i;
	char	*str;

	i = 0;
	if (!node)
		return (0);
	str = node->str;
	while (str[i] && str[i] == ' ')
		i++;
	// The string must contain at least one '1'
	if (str[i] != '1')
		return (0);
	while (str[i])
	{
		// The string must only contain '1' or spaces
		// if (str[i] == '0' || nsew(str[i]))
		// 	return (printf("map's first line cannot contain '0'\n"), -1);
		if (str[i] != '1' && str[i] != ' ')
			return (0);
		i++;
	}
	return (1); // The string is valid as a map start
}

int	map_end(t_file *supposed_end)
{
	t_file	*next_line;

	if (!supposed_end)
		return (0);
	next_line = supposed_end->next;
	if (!next_line || empty(next_line->str))
		return (1); // it's last
	return (0);
}

t_file	*get_start(t_file *file)
{
	t_file	*tmp;

	tmp = file;
	while (tmp && !tmp->map_start)
		tmp = tmp->next;
	return (tmp);
}

t_file	*get_end(t_file *file)
{
	t_file	*tmp;

	tmp = file;
	while (tmp && !tmp->map_end)
		tmp = tmp->next;
	return (tmp);
}
