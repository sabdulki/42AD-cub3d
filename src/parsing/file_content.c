/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:48:22 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/19 19:02:33 by sabdulki         ###   ########.fr       */
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
	printf("SPR: '%s'\n", spr_value);
	while (i < len)
	{
		if (!ft_isdigit(spr_value[i]) && spr_value[i] != ',')
			return (1);
		i++;
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
	while (str_nums[len])
		len++;
	if (len != 3)
		return (perror("invalid rgb value"), NULL);
	return (str_nums);
}

int which_value(int name, char *spr_value)
{
	char **str_nums;
	int* num_arr;

	str_nums = NULL;
	num_arr = NULL;
	if (!is_color(spr_value)) //contains only digits and commas
	{
		printf("it's color!\n");
		str_nums = check_str_color_value(spr_value);
		if (!str_nums)
			return (1);
		num_arr = check_num_color_value(str_nums);
		if (!num_arr)
			return (1);
		//assign field in node to int[3];
		for (int i = 0; i < 3; i++)
			printf("colors: %d\n", num_arr[i]);
		return (0);
	}
	if ((name == NO && safe_strncmp("./path_to_the_north_texture", spr_value)) \
	|| (name == SO && safe_strncmp("./path_to_the_south_texture", spr_value)) \
	|| (name == WE && safe_strncmp("./path_to_the_west_texture", spr_value)) \
	|| (name == EA && safe_strncmp("./path_to_the_east_texture", spr_value)))
	{
		// assign char *texture_path;
		printf("found spr_value!!!: %s\n", spr_value);
		return (0);
	}
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
	if (!sprites[0] || !sprites[1])
		return (perror("invalid arguments"), 1);
	for (int i = 0; sprites[i]; i++)
		printf("\tsprites %d: '%s'\n", i, sprites[i]);
	sprite_name = sprites[0];
	sprite_value = sprites[1];
	name = which_name(sprite_name);
	if (name == -1)
		return (perror("invalid texture name"), 1);
	printf("name: %d\n", name);
	// if (access(sprite_value, R_OK) == -1)
	// 	return (perror("file is inaccessible"), 1);
	which_value(name, sprite_value); //assign proper values inside the function
	//assign proper name

	// node->sprite_name = result (enum);
	return (0);
}

int old_map_starts(char *str)
{
	size_t i;
	// size_t j;
	size_t len;
	
	len = ft_strlen(str);
	i = 0;
	// j = 0;
	while (str[i] && i < len)
	{
		if (str[i] != '1' && str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	// printf("j: %ld, i: %ld, len: %ld\n", j, i, len);
	// if (j == ft_strlen(str))
	// 	return (1);
	return (1);
}


#include <ctype.h>  // for isspace()

int map_starts(char *str)
{
    int i = 0;

    // Skip leading whitespace characters (spaces, tabs)
    while (str[i] && is_delimiter(str[i]))
        i++;

    // The string must contain at least one '1'
    if (str[i] != '1')
        return (0);

    // Now check the rest of the line
    while (str[i])
    {
        // The string must only contain '1', spaces, or tabs
        if (str[i] != '1' && !is_delimiter(str[i]))
            return (0);
        i++;
    }

    return (1);  // The string is valid as a map start
}



int file_content(char *map_path)
{
	int fd;
	char *str;

	str = NULL;
	fd = open(map_path, O_RDONLY);
	while(1) // !map starts or all 6 sprites have been filled
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		str[ft_strlen(str) - 1] = '\0';
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
	close(fd);
	printf("reached the map\n");
	return (0);
}