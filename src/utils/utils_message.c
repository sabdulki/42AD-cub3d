/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:35:01 by sabdulki          #+#    #+#             */
/*   Updated: 2024/10/01 13:45:06 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	p_error(char *str)
{
	int		i;
	ssize_t	result;

	i = 0;
	while (str[i])
	{
		result = write(2, &str[i], 1);
		if (result == -1)
		{
			// Handle the error if needed
			return ;
		}
		i++;
	}
	result = write(2, "\n", 1);
	if (result == -1)
	{
		// Handle the error if needed
		return ;
	}
	return ;
}

void	print_sprite_list(t_sprite_list *head)
{
	t_sprite_list	*tmp;

	tmp = head;
	printf("\n-----------START OF TEXTURES-----------\n");
	while (tmp)
	{
		printf("----------------------\n");
		// printf("head?: %d\n", tmp->head);
		printf("name: %s\n", sprite_to_string(tmp->sprite_name));
		printf("path: %s\n", tmp->texture_path);
		printf("color: ");
		if (!tmp->color)
			printf("NONE\n");
		else
		{
			for (int i = 0; i < 3; i++)
				printf("%d, ", tmp->color[i]);
			printf("\n");
		}
		tmp = tmp->next;
	}
	printf("\n-----------END OF TEXTURES-----------\n");
}

char	*sprite_to_string(t_sprites sprite)
{
	switch (sprite)
	{
		case NO:
			return ("NO");
		case SO:
			return ("SO");
		case WE:
			return ("WE");
		case EA:
			return ("EA");
		case F:
			return ("F");
		case C:
			return ("C");
		default :
			return ("Unknown sprite");
	}
}

void	print_file_strct(t_file *file)
{
	t_file	*tmp;

	tmp = file;
	printf("\n-----------START OF FILE-----------\n");
	while (tmp)
	{
		if (tmp->str)
			printf("'%s'\n", tmp->str);
		tmp = tmp->next;
	}
	printf("\n-----------END OF FILE-----------\n");
	return ;
}
