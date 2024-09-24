
#include "./cub.h"

//improve -> there should be not just 1 line, but the whole map
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
	// close(fd);
	printf("reached the map\n");
	return (head); //parsed linked list of info till the map
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