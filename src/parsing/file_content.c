/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:48:22 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/23 18:34:07 by sabdulki         ###   ########.fr       */
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
	// printf("SPR: '%s'\n", spr_value);
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

int *do_color(char *spr_value)
{
	char **str_nums;
	int* num_arr;
	
	str_nums = NULL;
	num_arr = NULL;
	printf("it's color!\n");
	str_nums = check_str_color_value(spr_value);
	if (!str_nums)
		return (NULL);
	num_arr = check_num_color_value(str_nums);
	if (!num_arr)
		return (NULL);
	//assign field in node to int[3];
	for (int i = 0; i < 3; i++)
		printf("colors: %d\n", num_arr[i]);
	return (num_arr);
}

t_sprite_list *fill_node(char *sprite_name, char *sprite_value)
{
	t_sprite_list *node;
	int name;

	node = init_def_node();
	if (!node)
		return (NULL);
	name = which_name(sprite_name);
	if (name == -1)
		return (perror("invalid texture name"), free(node), NULL);
	printf("name: %d\n", name);
	node->sprite_name = name;
	if (is_color(sprite_value)) //the sprite is NOT color
	{
		// if (access(sprite_value, R_OK) == -1)
		// 	return (perror("sprite path is inaccessible"), free(node), NULL);
		node->texture_path = sprite_value;
	}
	else //the sprite is COLOR
	{
		node->color = do_color(sprite_value);
		if (!node->color)
			return (printf("do_color() failed\n"), free(node), NULL);
	}
	return (node);
}

/* firstly check if the args are valid, after that assign these values to fields in a node */
t_sprite_list *str_content(char *str)
{
	t_sprite_list *node;
	char **sprites;

	sprites = ft_split(str, ' ');
	if (!sprites || !sprites[0] || !sprites[1])
		return (printf("invalid arguments\n"), NULL);
	// for (int i = 0; sprites[i]; i++)
	// 	printf("\tsprites %d: '%s'\n", i, sprites[i]);
	node = fill_node(sprites[0], sprites[1]);
	if (!node)
		return (printf("failed to create node\n"), NULL);
	return (node);
}

int map_starts(char *str)
{
    int i = 0;

	if (!str)
		return (0);
    while (str[i] && is_delimiter(str[i]))
        i++;
    // The string must contain at least one '1'
    if (str[i] != '1')
        return (0);
    while (str[i])
    {
        // The string must only contain '1', spaces, or tabs
        if (str[i] != '1' && !is_delimiter(str[i]))
            return (0);
        i++;
    }

    return (1);  // The string is valid as a map start
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

t_sprite_list *old_file_content(char *file_path)
{
	int fd;
	char *str;
	t_sprite_list *node;
	t_sprite_list *head;

	head = NULL;
	str = NULL;
	fd = open(file_path, O_RDONLY);
	while (!map_starts(str)) // !map starts or all 6 sprites have been filled
	{
		str = get_next_line(fd);
		if (!str) //end of file
			break ;
		str[ft_strlen(str) - 1] = '\0';
		if (empty(str))
			continue ;
		node = str_content(str); //already filled node.
		if (node)
			add_node_to_list(node, &head);
	}
	if (str)
		free(str);
	close(fd);
	printf("reached the map\n");
	return (head); //parsed linked list of info till the map
}

t_file *overwrite_file(char *file_path)
{
	int fd;
	char *str;
	t_file *str_node;
	t_file *head;

	head = NULL;
	str = NULL;
	str_node = init_def_str(); 				//free
	if (!str_node)
		return (NULL);
	fd = open(file_path, O_RDONLY);
	while (1) // !map starts or all 6 sprites have been filled
	{
		str = get_next_line(fd);
		if (!str) //end of file
			break ;
		str[ft_strlen(str) - 1] = '\0';
		str_node = init_def_str(); 				//free
		if (!str_node)
			return (NULL);
		str_node->str = str; 				//free
		if (!empty(str))
			add_node_to_file(str_node, &head);
		// printf("'%s'\n", str_node->str);
	}
	return (head);
}
