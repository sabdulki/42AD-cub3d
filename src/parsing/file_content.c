/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:48:22 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/18 17:55:36 by sabdulki         ###   ########.fr       */
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

int is_color(char *spr_value)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(spr_value);
	while (i < len)
	{
		if (!ft_isdigit(spr_value[i]) && spr_value[i] != ',')
			return (1);
	}
	return (0);
}

int *check_num_color_value(char **str_nums)
{
	int i;
	int len;
	int *int_num;
	int tmp_num;

	int_num = malloc(sizeof(int) * 3);
	if (!int_num)
		return (perror("malloc failed"), NULL);
	i = 0;
	len = 3;
	while (str_nums[i] && i < len)
	{
		tmp_num = ft_atoi(str_nums[i]);
		if (tmp_num < 0 || tmp_num > 255)
			return (perror("invalid rgb value"), free(int_num), NULL);
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
		return (perror("split failed"), NULL);
	len = 0;
	while (!str_nums[len])
		len++;
	if (len != 3)
		return (perror("invalid rgb value"), NULL);
	return (str_nums);
}

int which_value(int name, char *spr_value)
{
	char **str_nums;
	int* num_arr;
	if (!is_color(spr_value)) //contains only digits and commas
	{
		str_nums = check_str_color_value(spr_value);
		if (!str_nums)
			return (1);
		num_arr = check_num_color_value(str_nums);
		if (!num_arr)
			return (1);
		//assign field in node to int[3];
		return (0);
	}
	if ((name == NO && safe_strncmp("./path_to_the_north_texture", spr_value)) \
	|| (name == SO && safe_strncmp("./path_to_the_south_texture", spr_value)) \
	|| (name == WE && safe_strncmp("./path_to_the_west_texture", spr_value)) \
	|| (name == EA && safe_strncmp("./path_to_the_east_texture", spr_value)))
		// assign char *texture_path;
		return (0);
	else
		return (perror("The sprite value does not match the cardinal directions or rgb"), 1);
}


/* firstly check if the args are valid, after that assign these values to fields in a node */
int str_content(char *str)
{
	char *sprite_name;
	char *sprite_value;
	char **sprites;
	int name;

	sprites = ft_split(str, ' ');
	if (!sprites)
		return (1);
	if (!sprites[0] || sprites[1])
		return (perror("invalid arguments"), 1);
	sprite_name = sprites[0];
	sprite_value = sprites[1];
	name = which_name(sprite_name);
	if (name == -1)
		return (perror("invalid texture name"), 1);
	if (access(sprite_value, R_OK) == -1)
		return (perror("file is inaccessible"), 1);
	which_value(name, sprite_value); //assign proper values inside the function
	//assign proper name

	// node->sprite_name = result (enum);
	return (0);
}

int map_starts(char *str)
{
	size_t i;

	i = 0;
	while (str[i] && i < ft_strlen(str))
	{
		if (str[i] != 1 && str[i] != ' ')
			i++;
	}
	if (i == ft_strlen(str))
		return (0);
	return (1);
}

int file_content(char *map_path)
{
	int fd;
	char *str;

	fd = open(map_path, O_RDONLY);
	while(1) // !map starts or all 6 sprites have been filled
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		if (map_starts(str))
		{
			free(str);
			break ;
		}
		str_content(str);
		// check if some content in str
		// parse the content
		// function -> create a node and fill it with content of string
		free(str);
	}
	printf("reached the map\n");
	return (0);
}