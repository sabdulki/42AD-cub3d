/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:44:42 by vlomakin          #+#    #+#             */
/*   Updated: 2024/06/28 19:55:03 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	do_atoi(const char *str, int i, int flag)
{
	long long	result;

	result = 0;
	while (str[i] && ('0' <= str[i]) && (str[i] <= '9'))
	{
		if (flag == 1 && result * 10 < result)
			return (-1);
		if (flag == -1 && result * 10 < result)
			return (0);
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (flag * result);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (str[i] == ' ' || ((9 <= str[i]) && (str[i] <= 13)))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			flag = -1;
		i++;
	}
	return (do_atoi(str, i, flag));
}
