/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:03:31 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/25 18:27:27 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	is_delimiter(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

int safe_strncmp(char *s1, char *s2)
{
	return (ft_strncmp(s1, s2, ft_strlen(s1)) == 0 && ft_strlen(s1) == ft_strlen(s2));
}

int which_name(char *sprite_name)
{
	if (safe_strncmp("NO", sprite_name))
		return (NO);
	else if (safe_strncmp("SO", sprite_name))
		return (SO);
	else if (safe_strncmp("WE", sprite_name))
		return (WE);
	else if (safe_strncmp("EA", sprite_name))
		return (EA);
	else if (safe_strncmp("F", sprite_name))
		return (F);
	else if (safe_strncmp("C", sprite_name))
		return (C);
	else
		return (-1);
}

int tabs(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' \
		|| str[i] == '\f' || str[i] == '\r')
			return (printf("invalid delimiter\n"), 1);
		i++;
	}
	return (0);
}

int empty(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (is_delimiter(str[i]))
			j++;
		i++;
	}
	if (j == i)
		return (1); // it's empty
		// return (printf("the string '%s' is empty!\n", str), 1); // it's empty
	return (0);
}
