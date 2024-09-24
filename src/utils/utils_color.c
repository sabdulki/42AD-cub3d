/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uils_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:27:03 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/24 20:17:23 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int is_color(char *spr_value)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(spr_value);
	while (i < len)
	{
		if (!ft_isdigit(spr_value[i]) && spr_value[i] != ',')
			return (1); //not color
		i++;
	}
	return (0); //is color
}

int *check_num_color_value(char **str_nums)
{
	int i;
	int len;
	int *int_num;
	int tmp_num;

	int_num = malloc(sizeof(int) * 3);
	if (!int_num)
		return (p_error("malloc failed"), NULL);
	i = 0;
	len = 3;
	while (str_nums[i] && i < len)
	{
		tmp_num = ft_atoi(str_nums[i]);
		if (tmp_num < 0 || tmp_num > 255)
			return (p_error("invalid rgb value"), free(int_num), NULL);
		int_num[i] = tmp_num;
		i++;
	}
	return (int_num);
}

char **check_str_color_value(char *spr_value)
{
	char **str_nums;
	int len;

	str_nums = ft_split(spr_value, ',');
	if (!str_nums)
		return (p_error("split failed"), NULL);
	len = 0;
	while (str_nums[len])
		len++;
	if (len != 3)
		return (p_error("invalid rgb value"), NULL);
	return (str_nums);
}

int *do_color(char *spr_value)
{
	char **str_nums;
	int* num_arr;
	
	str_nums = NULL;
	num_arr = NULL;
	// printf("it's color!\n");
	str_nums = check_str_color_value(spr_value);
	if (!str_nums)
		return (NULL);
	num_arr = check_num_color_value(str_nums);
	if (!num_arr)
		return (NULL);
	// for (int i = 0; i < 3; i++)
	// 	printf("colors: %d\n", num_arr[i]);
	return (num_arr);
}
